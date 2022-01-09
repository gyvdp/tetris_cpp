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

#ifndef ESI_ATLIR5_ATLC_PROJECT2_INCLUDE_SERVER_MATCH_HPP_
#define ESI_ATLIR5_ATLC_PROJECT2_INCLUDE_SERVER_MATCH_HPP_

#include <QString>
#include <QTcpSocket>
#include <array>
#include <memory>

#include "player_socket.hpp"

namespace tetris::server {

class Match : public QObject {
  Q_OBJECT
 private:
  std::array<Player_Socket*, 2> players_;

  unsigned id_;
  /**
   * @brief Send to both player the inormation to start a game.
   */
  void sendStarting();

  void playerLost(Player_Socket*& p_socket, QByteArray data);

 public:
  /**
   * @brief Constructor of Match.
   * @param player1 Player_socket of the first player
   * @param player2 Player_socket of the second player
   * @param id id of the game.
   * @param parent parent of the match
   */
  explicit Match(Player_Socket*& player1, Player_Socket*& player2, unsigned id,
                 QObject* parent);

  /**
   * @brief Getter of id
   * @return id
   */
  [[nodiscard]] inline unsigned id() const { return this->id_; }

  void launchMatch();

 signals:
  /**
   * @brief Signal that is emited when the match is finished
   */
  void matchEnded(tetris::server::Match*);

 public slots:
  /**
   * @brief Action when a player disconnect
   */
  void slot_Disconnected();
  /**
   * @brief Action when a player write to the match
   */
  void slot_Reading();
};
}  // namespace tetris::server
#endif  // ESI_ATLIR5_ATLC_PROJECT2_INCLUDE_SERVER_MATCH_HPP_
