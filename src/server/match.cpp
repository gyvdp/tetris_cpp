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

#include <utility>

#include "model/notification/notification.hpp"

namespace tetris::server {

Match::Match(Player_Socket*& player1, Player_Socket*& player2, unsigned id,
             QObject* parent)
    : QObject(parent), players_({player1, player2}), id_(id) {
  // Connect
  for (const auto& player : players_) {
    player->parent(this);
    connect(player->socket(), &QAbstractSocket::disconnected, this,
            &Match::slot_Disconnected);
    connect(player->socket(), &QAbstractSocket::readyRead, this,
            &Match::slot_Reading);
  }

  // Write STARTING GAME NOTIFICATION
  qDebug() << "Match started : ";

  this->players_[0]->socket()->write(
      tetris::model::notification::Notification::starting_game(
          players_[0]->name(), 78785, players_[1]->name(), 45, 54353)
          .toJson(QJsonDocument::Indented));

  this->players_[1]->socket()->write(
      tetris::model::notification::Notification::starting_game(
          players_[1]->name(), 45, players_[0]->name(), 54353, 54353)
          .toJson(QJsonDocument::Indented));
}

void Match::slot_Disconnected() {
  qDebug() << "Match : disconnected...";
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
}  // namespace tetris::server
