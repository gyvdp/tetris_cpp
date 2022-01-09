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
#include "client/socket_client.hpp"

#include <regex>

#include "client/component/matrix.hpp"
#include "client/exceptions/connexion_not_possible_exception.hpp"

namespace tetris::client {

void Socket_Client::connection(const QString& ip, unsigned port,
                               const std::string& username) {
  // Verify ip
  std::string regex = "^(?:[0-9]{1,3}.){3}[0-9]{1,3}$";
  if (!std::regex_match(ip.toStdString(), std::regex(regex)))
    throw std::invalid_argument("ip address is not valid");

  // Open socket
  socket_->open(QIODevice::ReadWrite);

  // Connect
  connect(socket_, &QAbstractSocket::connected, this,
          &Socket_Client::slot_Connected);
  connect(socket_, &QAbstractSocket::disconnected, this,
          &Socket_Client::slot_Disconnected);
  connect(socket_, &QAbstractSocket::readyRead, this,
          &Socket_Client::slot_Reading);

  this->username_ = username;

  // Connection to the server with ip and port
  socket_->connectToHost(QHostAddress(ip), port);

  // Waiting for connection
  if (!socket_->waitForConnected(5000)) {
    throw exceptions::ConnexionNotPossibleException("Connexion impossible",
                                                    __FILE__, __LINE__);
  }
}

void Socket_Client::sendData(const QJsonDocument& data) {
  QByteArray arrayData = QByteArray(data.toJson(QJsonDocument::Indented));
  this->socket_->write(arrayData);
  this->socket_->waitForBytesWritten();
}

void Socket_Client::slot_Connected() {
  qDebug() << "connected...";

  socket_->write(tetris::model::notification::Notification::action(
                     model::notification::CONNECTION,
                     QString::fromStdString(this->username_))
                     .toJson(QJsonDocument::Indented));
  this->socket_->waitForBytesWritten();
}

void Socket_Client::slot_Disconnected() { qDebug() << "disconnected..."; }

void Socket_Client::slot_Reading() {
  this->socket_->waitForConnected();
  auto data = this->socket_->readAll();
  deserialize(data);
}

void Socket_Client::deserialize(QByteArray& message) {
  QJsonDocument doc = QJsonDocument::fromJson(message);
  QString key = doc.object()["key"].toString();
  QJsonObject data = doc.object()["data"].toObject();
  if (key == "ACTION") {
    switch (data["action"].toInt()) {
      case model::notification::LEAVE:
        emit leave(data["score"].toString().toULong());
      case model::notification::LOST:
        emit lost(data["score"].toString().toULong());
      case model::notification::MOVE:
        emit move(model::tetrimino::Direction(
            data["direction"].toObject()["direction"].toInt()));
        break;
      case model::notification::SOFTDROP:
        emit softdrop();
        break;
      case model::notification::HARDDROP:
        emit harddrop();
        break;
      case model::notification::HOLD:
        emit hold();
        break;
      case model::notification::ROTATE:
        emit rotate((data["clockwise"].toBool()));
        break;
      default:
        throw std::invalid_argument("Unknown action");
    }
  } else if (key == "STARTING_GAME") {
    std::string name =
        data["player"].toObject()["name"].toString().toStdString();
    unsigned long highscore =
        data["player"].toObject()["highscore"].toString().toULong();
    std::string opponentName =
        data["opponent"].toObject()["name"].toString().toStdString();
    unsigned long opponentHighScore =
        data["opponent"].toObject()["highscore"].toString().toULong();
    uint_fast64_t seed = data["seed"].toString().toULongLong();
    emit starting_game(name, highscore, opponentName, opponentHighScore, seed);
  }
}

void Socket_Client::slot_Rotate(bool clockwise) {
  this->sendData(model::notification::Notification::action(
      model::notification::ROTATE, clockwise));
}

void Socket_Client::slot_Hold(model::tetrimino::Mino m) {
  this->sendData(
      model::notification::Notification::action(model::notification::HOLD));
}

void Socket_Client::slot_Move(model::tetrimino::Direction direction) {
  this->sendData(model::notification::Notification::action(
      model::notification::MOVE, direction));
}

void Socket_Client::slot_Lock() {
  this->sendData(
      model::notification::Notification::action(model::notification::LOCK));
}

void Socket_Client::slot_HardDrop() {
  this->sendData(
      model::notification::Notification::action(model::notification::HARDDROP));
}
// void Tetris_Client::linesUpdate(unsigned int lines) {}

}  // namespace tetris::client