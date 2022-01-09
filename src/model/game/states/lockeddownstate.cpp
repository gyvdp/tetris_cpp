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

#include "model/game/states/lockeddownstate.hpp"

#include <model/game/states/blockedoutstate.hpp>
#include <model/game/states/fallingstate.hpp>
#include <model/game/states/lockedoutstate.hpp>
#include <model/game/states/stoppedstate.hpp>
#include <model/tetrimino/tetrimino_logic.hpp>

#include "model/game/states/exceptions/blockedoutexception.hpp"
#include "model/game/states/exceptions/illegalstateexception.hpp"
#include "model/game/states/exceptions/lockedoutexception.hpp"
#include "model/game/states/exceptions/startongoinggameexception.hpp"
#include "model/tetrimino/exceptions/movenotpossibleexception.hpp"
#include "model/tetrimino/exceptions/rotationnotpossibleexception.hpp"
namespace tetris::model::game::states {

void LockedDownState::start() {
  throw exceptions::StartOnGoingGameException("Cannot start when locked out",
                                              __FILE__, __LINE__);
}

void LockedDownState::stop() { game_->state(new StoppedState(game_)); }

void LockedDownState::move(tetrimino::Direction direction) {
  try {
    game_->moveFalling(direction);
    game_->state(new FallingState(game_));
  } catch (tetrimino::exceptions::MoveNotPossibleException& ignored) {
  }
}

void LockedDownState::holdFalling() {
  throw exceptions::IllegalStateException("Cannot move when blocked out",
                                          __FILE__, __LINE__);
}

void LockedDownState::softDrop() {
  throw exceptions::IllegalStateException("Cannot soft drop when blocked out",
                                          __FILE__, __LINE__);
}

void LockedDownState::hardDrop() {
  throw exceptions::IllegalStateException("Cannot hard drop when locked down",
                                          __FILE__, __LINE__);
}

void LockedDownState::rotate(bool clockwise) {
  try {
    game_->falling()->rotate(clockwise, game_->matrix().generateMask());
    game_->state(new FallingState(game_));
    delete this;
  } catch (tetrimino::exceptions::RotationNotPossibleException& ignored) {
  }
}

}  // namespace tetris::model::game::states