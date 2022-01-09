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

#include "client.hpp"

namespace tetris::client {

Client::Client(const QHostAddress& ip, int port, std::string name)
    : socket_client_{new Socket_Client(this)}, game_{new window::GameWindow{}} {
  this->socket_client_->connection(ip.toString(), port, name);
  connect(socket_client_, &Socket_Client::starting_game, this, &Client::start);
}

Client::~Client() {
  if (game_ != nullptr) {
    delete game_;
    game_ = nullptr;
  }

  if (game_ != nullptr) {
    delete game_;
    game_ = nullptr;
  }
}

void Client::start(std::string playerName, unsigned long highScore,
                   std::string opponentName, unsigned long opponentHighScore,
                   unsigned long seed) {
  game_->start(playerName, highScore, opponentName, opponentHighScore, seed,
               this->socket_client_);
  game_->show();
}

}  // namespace tetris::client
