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

#ifndef ESI_ATLIR5_ATLC_PROJECT2_SRC_SERVER_SERVER_TETRISSERVER_HPP_
#define ESI_ATLIR5_ATLC_PROJECT2_SRC_SERVER_SERVER_TETRISSERVER_HPP_
#include <QDebug>
#include <QHostAddress>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <memory>
#include <queue>
#include <string>
#include <vector>

#include "match.hpp"
#include "player_socket.hpp"

namespace tetris::server {

class Tetris_Server : public QObject {
 private:
  Q_OBJECT
  QTcpServer *server_;
  std::queue<QTcpSocket *> waitingQueueConnection_;
  std::queue<Player_Socket *> waitingQueuePlayer_;
  std::vector<Match *> matchVector_;
  unsigned matchID_;
  QHostAddress IP_;
  int port_;

 public:
  explicit Tetris_Server(QObject *parent = nullptr,
                         QHostAddress IP = QHostAddress::Any, int port = 9999);

 signals:

 public slots:
  void slot_Connected();
  void slot_Disconnected();
  void slot_PlayerDisconnected();
  void slot_Match_Ended(Match *match);
  void slot_Reading();
};
}  // namespace tetris::server
#endif  // ESI_ATLIR5_ATLC_PROJECT2_SRC_SERVER_SERVER_TETRISSERVER_HPP_
