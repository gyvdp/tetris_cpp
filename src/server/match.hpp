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

#include <QDebug>
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

 public:
  explicit Match(Player_Socket*& player1, Player_Socket*& player2, unsigned id,
                 QObject* parent);

  [[nodiscard]] inline unsigned id() const { return this->id_; }

 signals:
  void matchEnded(tetris::server::Match*);

 public slots:
  void slot_Disconnected();
  void slot_Reading();
};
}  // namespace tetris::server
#endif  // ESI_ATLIR5_ATLC_PROJECT2_INCLUDE_SERVER_MATCH_HPP_
