// MIT License
//
// Copyright (c) 2021 Andrew SASSOYE, Constantin GUNDUZ, Gregory VAN DER PLUIJM,
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

#include "model/game/state/fallingstate.hpp"

#include "model/tetrimino/tetrimino_logic.hpp"

namespace tetris::model::game::states {

void FallingState::start() {
  // TODO
}

void FallingState::stop() {
  // TODO
}

void FallingState::move(tetrimino::Direction direction) {
  game_->falling()->move(direction);
}

void FallingState::holdFalling() {
  if (!hasAlreadyHolded_) {
    if (game_->hold() == std::nullopt) {
      game_->setHold(game_->falling()->getType());
      game_->setFalling(game_->next().value());
    } else {
      auto temp = game_->hold().value();
      game_->setHold(game_->falling()->getType());
      game_->setFalling(temp);
    }
    hasAlreadyHolded_ = true;
  }
}
void FallingState::softDrop() {
  // TODO
}

void FallingState::hardDrop() {
  // TODO
}

void FallingState::rotate(bool clockwise) {
  game_->falling()->rotate(clockwise);
}

void FallingState::lock() {
  // TODO
}

}  // namespace tetris::model::game::states