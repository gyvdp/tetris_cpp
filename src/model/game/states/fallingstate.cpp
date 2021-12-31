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

#include <model/game/state/exceptions/illegalstateexception.hpp>

#include "model/game/state/exceptions/startongoinggameexception.hpp"
#include "model/game/state/stoppedstate.hpp"
#include "model/tetrimino/exceptions/movenotpossibleexception.hpp"
#include "model/tetrimino/exceptions/rotationnotpossibleexception.hpp"
#include "model/tetrimino/tetrimino_logic.hpp"

namespace tetris::model::game::states {

void FallingState::start() {
  throw exceptions::StartOnGoingGameException(
      "Cannot start an ongoing "
      "game",
      __FILE__, __LINE__);
}

void FallingState::stop() {
  game_->state(std::make_unique<states::StoppedState>(game_));
}

void FallingState::move(tetrimino::Direction direction) {
  try {
    game_->falling()->move(direction, game_->matrix().generateMask());
  } catch (tetrimino::exceptions::MoveNotPossibleException& ignored) {
  }
}

void FallingState::holdFalling() {
  if (!hasHold_) {
    if (game_->hold() == std::nullopt) {
      game_->hold(game_->falling()->type());
      game_->falling(tetrimino::createTetrimino(game_->next().value()));
    } else {
      auto temp = game_->hold().value();
      game_->hold(game_->falling()->type());
      game_->falling(tetrimino::createTetrimino(temp));
    }
    hasHold_ = true;
  }
}

void FallingState::softDrop() {
  // TODO
}

void FallingState::hardDrop() {
  // TODO
}

void FallingState::rotate(bool clockwise) {
  try {
    game_->falling()->rotate(clockwise, game_->matrix().generateMask());
  } catch (tetrimino::exceptions::RotationNotPossibleException& ignored) {
  }
}

void FallingState::lock() {
  throw exceptions::IllegalStateException("Cannot lock when falling", __FILE__,
                                          __LINE__);
}

}  // namespace tetris::model::game::states