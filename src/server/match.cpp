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
  players_[0]->parent(this);
  connect(players_[0]->socket(), &QAbstractSocket::disconnected, this,
          &Match::slot_Disconnected);
  connect(players_[0]->socket(), &QAbstractSocket::readyRead, this,
          &Match::slot_Reading1);
  players_[1]->parent(this);
  connect(players_[1]->socket(), &QAbstractSocket::disconnected, this,
          &Match::slot_Disconnected);
  connect(players_[1]->socket(), &QAbstractSocket::readyRead, this,
          &Match::slot_Reading2);

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

void Match::slot_Reading1() {
  if (players_[1]->socket()->state() != QAbstractSocket::UnconnectedState) {
    this->players_[1]->socket()->write(this->players_[0]->socket()->readAll());
    this->players_[1]->socket()->waitForBytesWritten();
  }
}

void Match::slot_Reading2() {
  if (players_[0]->socket()->state() != QAbstractSocket::UnconnectedState) {
    this->players_[0]->socket()->write(this->players_[1]->socket()->readAll());
    this->players_[0]->socket()->waitForBytesWritten();
  }
}

void Match::sendStarting() {
  auto seed = time(nullptr);
  this->players_[0]->socket()->write(
      tetris::model::notification::Notification::starting_game(
          players_[0]->name(), players_[0]->highScore(), players_[1]->name(),
          players_[1]->highScore(), seed)
          .toJson(QJsonDocument::Compact));

  this->players_[1]->socket()->write(
      tetris::model::notification::Notification::starting_game(
          players_[1]->name(), players_[1]->highScore(), players_[0]->name(),
          players_[0]->highScore(), seed)
          .toJson(QJsonDocument::Compact));
}

}  // namespace tetris::server
