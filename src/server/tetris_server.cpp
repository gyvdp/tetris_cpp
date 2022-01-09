// MIT License
//
// Copyright (c) 2022 Andrew SASSOYE, Constantin GUNDUZ, Gregory VAN DER PLUIJM,
// Thomas LEUTSCHER
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "server/tetris_server.hpp"

#include <QFile>

namespace tetris::server {

Tetris_Server::Tetris_Server(QObject *parent) : QObject(parent), matchID_{0} {
  server_ = new QTcpServer(this);

  if (!server_->listen(QHostAddress::Any, 9999))
    throw exceptions::ServerStartFailException(
        "The server can't start with this ip or this port", __FILE__, __LINE__);

  std::cout << "Server active on : IP :"
            << server_->serverAddress().toString().toStdString()
            << " , Port : " << server_->serverPort() << std::endl;

  connect(server_, &QTcpServer::newConnection, this,
          &Tetris_Server::slot_Connected);
}

void Tetris_Server::slot_Connected() {
  QTcpSocket *socket = server_->nextPendingConnection();
  this->waitingQueueConnection_.push(socket);
  socket->waitForConnected();
  socket->open(QIODevice::ReadWrite);
  connect(socket, &QAbstractSocket::readyRead, this,
          &Tetris_Server::slot_Reading);
  connect(socket, &QAbstractSocket::disconnected, this,
          &Tetris_Server::slot_Disconnected);
  if (!socket->waitForReadyRead(3000)) slot_Disconnected();
}

void Tetris_Server::slot_Disconnected() {
  delete (this->waitingQueueConnection_.front());
  this->waitingQueueConnection_.pop();
}

void Tetris_Server::slot_PlayerDisconnected() {
  delete (this->waitingQueuePlayer_.front());
  this->waitingQueuePlayer_.pop();
}

void Tetris_Server::slot_Match_Ended(Match *match) {
  unsigned index = 0;
  for (const auto &games : this->matchVector_) {
    if (match->id() == games->id())
      this->matchVector_.erase(this->matchVector_.begin() + index);
    index++;
  }
  delete (match);
}

void Tetris_Server::slot_Reading() {
  auto socket = this->waitingQueueConnection_.front();
  QJsonDocument doc = QJsonDocument::fromJson(socket->readAll());
  if (doc.object()["key"].toString().toStdString() == "ACTION") {
    this->waitingQueueConnection_.pop();
    if (doc.object()["data"].toObject()["action"].toInt() == 0) {
      Player_Socket *player_socket = createPlayer(doc, socket);
      if (!this->waitingQueuePlayer_.empty() &&
          this->waitingQueuePlayer_.front()->name() != player_socket->name()) {
        joinMatch(player_socket);
      } else {
        joinQueue(player_socket);
      }
    }
  }
}

Player_Socket *Tetris_Server::createPlayer(QJsonDocument &doc,
                                           QTcpSocket *socket) {
  QString name = doc.object()["data"]
                     .toObject()["player"]
                     .toObject()["username"]
                     .toString();
  auto *player_socket =
      new Player_Socket(socket, name, findScoreInJson(name).toULong(), this);
  return player_socket;
}

QString Tetris_Server::findScoreInJson(const QString &name) {
  QFile file("playerdata.json");
  QString score;
  if (file.exists()) {
    file.open(QIODevice::ReadOnly);
    auto data = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();
    score = obj["players"].toObject()[name].toObject()["highscore"].toString();
  }
  if (score.isEmpty()) {
    score = "0";
  }
  return score;
}

void Tetris_Server::joinQueue(Player_Socket *&player_socket) {
  this->waitingQueuePlayer_.push(player_socket);
  connect(player_socket->socket(), &QAbstractSocket::disconnected, this,
          &Tetris_Server::slot_PlayerDisconnected);
}

void Tetris_Server::joinMatch(Player_Socket *&player_socket) {
  this->waitingQueuePlayer_.front()->socket()->disconnect();
  this->matchVector_.push_back(new Match(this->waitingQueuePlayer_.front(),
                                         player_socket, ++matchID_, this));
  connect(this->matchVector_.back(), &Match::matchEnded, this,
          &Tetris_Server::slot_Match_Ended);
  this->waitingQueuePlayer_.pop();
}

}  // namespace tetris::server
