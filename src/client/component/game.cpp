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

#include "game.hpp"
namespace tetris::client::component {

Game::Game(QGraphicsItem *parent)
    : QGraphicsItemGroup(parent),
      matrix_{new component::Matrix{this}},
      scoreBoard_{new component::ScoreBoard{this}},
      next_{new component::TetriHolder{this}},
      hold_{new component::TetriHolder{this}} {
  scoreBoard_->setPos({0, 0});
  matrix_->setPos({scoreBoard_->boundingRect().width(), 0});
  next_->setPos({matrix_->x() - next_->boundingRect().width(),
                 scoreBoard_->boundingRect().height()});
  hold_->setPos({next_->x(), next_->y() + next_->boundingRect().height()});
}

void Game::updateMatrix(MatrixArray array) { matrix_->set(std::move(array)); }

QRectF Game::boundingRect() const {
  return QRect{0, 0,
               static_cast<int>(scoreBoard_->boundingRect().width() +
                                matrix_->boundingRect().width()),
               static_cast<int>(matrix_->boundingRect().height())};
}

}  // namespace tetris::client::component