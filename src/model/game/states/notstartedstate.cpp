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

#include "model/game/state/notstartedstate.hpp"

#include <stdexcept>

#include "model/game/state/exceptions/notstartedexception.hpp"
#include "model/game/state/fallingstate.hpp"
#include "model/tetrimino/tetrimino_logic.hpp"

namespace tetris::model::game::states {

void NotStartedState::start() {
  game_->falling(tetrimino::createTetrimino(game_->pickMino()));
  game_->next(game_->pickMino());
  game_->state(std::make_unique<FallingState>(game_));
}

void NotStartedState::stop() {
  throw exceptions::NotStartedException("Cannot stop an unstarted game",
                                        __FILE__, __LINE__);
}

void NotStartedState::move(tetrimino::Direction direction) {
  throw exceptions::NotStartedException("Cannot  move if game is not started",
                                        __FILE__, __LINE__);
}

void NotStartedState::holdFalling() {
  throw exceptions::NotStartedException("Cannot hold if game is not started",
                                        __FILE__, __LINE__);
}

void NotStartedState::softDrop() {
  throw exceptions::NotStartedException(
      "Cannot soft drop if game is not started", __FILE__, __LINE__);
}

void NotStartedState::hardDrop() {
  throw exceptions::NotStartedException(
      "Cannot hard drop if game is not started", __FILE__, __LINE__);
}

void NotStartedState::rotate(bool clockwise) {
  throw exceptions::NotStartedException("Cannot rotate if game is not started",
                                        __FILE__, __LINE__);
}

void NotStartedState::lock() {
  throw exceptions::NotStartedException("Cannot lock if a game is not started",
                                        __FILE__, __LINE__);
}

}  // namespace tetris::model::game::states