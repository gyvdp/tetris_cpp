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

#include "model/game/state/lockeddownstate.hpp"

#include <model/game/state/blockedoutstate.hpp>
#include <model/game/state/fallingstate.hpp>
#include <model/game/state/lockedoutstate.hpp>
#include <model/game/state/stoppedstate.hpp>
#include <model/tetrimino/tetrimino_logic.hpp>

#include "model/game/state/exceptions/blockedoutexception.hpp"
#include "model/game/state/exceptions/illegalstateexception.hpp"
#include "model/game/state/exceptions/lockedoutexception.hpp"
#include "model/game/state/exceptions/startongoinggameexception.hpp"
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
    game_->falling()->move(direction, game_->matrix().generateMask());
    game_->timer_.expires_at(std::chrono::steady_clock::now() +
                             boost::asio::chrono::milliseconds(500));
    game_->timer_.async_wait(boost::bind(&LockedDownState::lock, this));
  } catch (tetrimino::exceptions::MoveNotPossibleException& ignored) {
  }
}

void LockedDownState::holdFalling() {
  throw exceptions::IllegalStateException("Cannot move when blocked out",
                                          __FILE__, __LINE__);
}

void LockedDownState::softDrop() {
  throw exceptions::IllegalStateException("Cannot soft drop when locked down",
                                          __FILE__, __LINE__);
}

void LockedDownState::hardDrop() {
  throw exceptions::IllegalStateException("Cannot hard drop when locked down",
                                          __FILE__, __LINE__);
}

void LockedDownState::rotate(bool clockwise) {
  try {
    game_->falling()->rotate(clockwise, game_->matrix().generateMask());
    game_->timer_.expires_at(std::chrono::steady_clock::now() +
                             boost::asio::chrono::milliseconds(500));
    game_->timer_.async_wait(boost::bind(&LockedDownState::lock, this));
  } catch (tetrimino::exceptions::RotationNotPossibleException& ignored) {
  }
}

void LockedDownState::lock() {
  game_->getMatrix().add(game_->falling());
  try {
    game_->falling(tetrimino::createTetrimino(
        game_->next().value(), game_->getMatrix().generateMask()));
    game_->next(game_->pickMino());
    game_->clearLines();
    game_->state(new FallingState(game_));
  } catch (exceptions::BlockedOutException& e) {
    game_->state(new BlockedOutState(game_));
  }
}
}  // namespace tetris::model::game::states