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
#include <QHostAddress>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <iostream>
#include <memory>
#include <queue>
#include <vector>

#include "match.hpp"
#include "player_socket.hpp"
#include "server/exceptions/server_start_exception.hpp"

namespace tetris::server {

class Tetris_Server : public QObject {
  Q_OBJECT

 private:
  QTcpServer *server_;
  std::queue<QTcpSocket *> waitingQueueConnection_;
  std::queue<Player_Socket *> waitingQueuePlayer_;
  std::vector<Match *> matchVector_;
  unsigned matchID_;
  QHostAddress ip_;
  int port_;

  /**
   * @brief Create a Player_socket
   * @param doc QJsonDocument with his name
   * @param socket socket of the player
   * @return Player_socket created
   */
  Player_Socket *createPlayer(QJsonDocument &doc, QTcpSocket *socket);
  /**
   * @brief Put the player_socket in the queue
   * @param player_socket player_socket that we move
   */
  void joinQueue(Player_Socket *&player_socket);
  /**
   * @brief Put the player_socket in a match with le first one in the queue;
   * @param player_socket player_socket that we move
   */
  void joinMatch(Player_Socket *&player_socket);

  /**
   * @brief will open a json file and will research for the best score of the
   * player.
   * @param name name of the player.
   * @return player's best score in String.
   */
  static QString findScoreInJson(const QString &name);

 public:
  /**
   * @brief Constructor of Tetris_Server
   * @param parent Parent of this class
   * @param ip adress ip of the Tetris_Server
   * @param port port of the application
   */
  explicit Tetris_Server(QObject *parent = nullptr,
                         const QHostAddress &ip = QHostAddress::Any,
                         int port = 9999);

 signals:

 public slots:
  /**
   * @brief Action when a user is connecting
   */
  void slot_Connected();
  /**
   * @brief Action when a user is disconnecting
   */
  void slot_Disconnected();
  /**
   * @brief Action when a player is disconnecting
   */
  void slot_PlayerDisconnected();
  /**
   * @brief Action when a match ends
   */
  void slot_Match_Ended(Match *match);
  /**
   * @brief Action when a user send something
   */
  void slot_Reading();
};
}  // namespace tetris::server
#endif  // ESI_ATLIR5_ATLC_PROJECT2_SRC_SERVER_SERVER_TETRISSERVER_HPP_
