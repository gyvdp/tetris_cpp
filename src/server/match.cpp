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

#include "server/match.hpp"

#include <QFile>

#include "model/notification/notification.hpp"

namespace tetris::server {

Match::Match(Player_Socket*& player1, Player_Socket*& player2, unsigned id,
             QObject* parent)
    : QObject(parent), players_({player1, player2}), id_(id) {
  for (const auto& player : players_) {
    player->parent(this);
    connect(player->socket(), &QAbstractSocket::disconnected, this,
            &Match::slot_Disconnected);
    connect(player->socket(), &QAbstractSocket::readyRead, this,
            &Match::slot_Reading);
  }

  sendStarting();
}

void Match::slot_Disconnected() {
  bool finish = true;
  for (auto& player : players_) {
    if (player->socket()->state() != QAbstractSocket::UnconnectedState) {
      player->socket()->write(tetris::model::notification::Notification::action(
                                  model::notification::LEAVE)
                                  .toJson(QJsonDocument::Compact));
      finish = false;
    }
  }
  if (finish) emit matchEnded(this);
}

void Match::slot_Reading() {
  for (auto& sender : this->players_) {
    if (sender->socket()->state() != QAbstractSocket::UnconnectedState) {
      auto data = sender->socket()->readAll();
      if (QJsonDocument::fromJson(data)
              .object()["data"]
              .toObject()["action"]
              .toInt() == model::notification::LOST)
        playerLost(sender, data);
      for (auto& receiver : this->players_) {
        if (sender->name() != receiver->name() &&
            receiver->socket()->state() != QAbstractSocket::UnconnectedState) {
          receiver->write(data);
          receiver->socket()->waitForBytesWritten();
        }
      }
    }
  }
}

void Match::sendStarting() {
  auto seed = time(nullptr);
  this->players_[0]->socket()->write(
      tetris::model::notification::Notification::starting_game(
          players_[0]->name(), players_[0]->highScore(), players_[1]->name(),
          players_[1]->highScore(), seed)
          .toJson(QJsonDocument::Indented));

  this->players_[1]->socket()->write(
      tetris::model::notification::Notification::starting_game(
          players_[1]->name(), players_[1]->highScore(), players_[0]->name(),
          players_[0]->highScore(), seed)
          .toJson(QJsonDocument::Indented));
}

void Match::playerLost(Player_Socket*& p_socket, QByteArray data) {
  // TODO Faire l'écriture du json.

  //  QJsonDocument doc = QJsonDocument::fromJson(data);
  //  QString score = doc.object()["data"].toObject()["score"].toString();
  //  if (p_socket->highScore() < score.toULong()) {
  //    QFile file("playerdata.json");
  //    QJsonDocument file_doc;
  //    if (file.exists()) {
  //      std::cout << "1";
  //      file.open(QIODevice::ReadWrite);
  //      file_doc = QJsonDocument::fromJson(file.readAll());
  //      if (p_socket->highScore() != 0) {
  //        file_doc.object()["players"]
  //            .toObject()[p_socket->name()]
  //            .toObject()["highscore"] = score;
  //      } else {
  //        std::cout << "2";
  //        QJsonObject player;
  //        player.insert("highscore", score);
  //        file_doc.object()["players"].toObject().insert(p_socket->name(),
  //                                                       player);
  //      }
  //    } else {
  //      std::cout << "3";
  //      QJsonObject players;
  //      QJsonObject player;
  //      player.insert("highscore", score);
  //      players.insert(p_socket->name(), player);
  //      file_doc.setObject(players);
  //    }
  //    file.seek(0);
  //    file.write(file_doc.toJson(QJsonDocument::Indented));
  //    file.flush();
  //    file.close();
  //  }
}

}  // namespace tetris::server
