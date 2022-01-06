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

#include "view.hpp"

#include <QApplication>

#include "model/game/ongoinggame.hpp"
#include "model/game/player.hpp"

using namespace tetris::model;

namespace tetris::view {

View::View() : game_{new window::GameWindow{}} { game_->show(); }
View::~View() {
  if (game_ != nullptr) {
    delete game_;
    game_ = nullptr;
  }
}

void View::start() {
  auto *player = new game::Player{"John", 123};
  auto *game = new game::OngoingGame{player, 1};
  game->connectBoard(
      [this](std::vector<std::vector<std::optional<tetrimino::Mino>>> matrix) {
        // moveToThread(QApplication::instance()->thread());
        emit game_->matrixChanged(matrix);
      });
  game->start();
}

}  // namespace tetris::view
