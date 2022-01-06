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

#include <iostream>
#include <model/game/state/blockedoutstate.hpp>
#include <model/game/state/lockedoutstate.hpp>

#include "model/game/state/exceptions/blockedoutexception.hpp"
#include "model/game/state/exceptions/lockedoutexception.hpp"
#include "model/game/state/exceptions/startongoinggameexception.hpp"
#include "model/game/state/lockeddownstate.hpp"
#include "model/game/state/stoppedstate.hpp"
#include "model/tetrimino/exceptions/movenotpossibleexception.hpp"
#include "model/tetrimino/exceptions/rotationnotpossibleexception.hpp"
#include "model/tetrimino/tetrimino_logic.hpp"

namespace tetris::model::game::states {

void FallingState::start() {
  throw exceptions::StartOnGoingGameException("Cannot start when falling",
                                              __FILE__, __LINE__);
}

void FallingState::stop() { game_->state(new StoppedState(game_)); }

void FallingState::move(tetrimino::Direction direction) {
  try {
    game_->falling()->move(direction, game_->matrix().generateMask());
    game_->updateGame(game_->fallingInsideMatrix());
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
  try {
    game_->falling()->move(tetrimino::DOWN, game_->matrix().generateMask());
    // refresh timer
  } catch (tetrimino::exceptions::MoveNotPossibleException& ignored) {
    game_->score(1);
    game_->state(new LockedDownState(game_));
  }
}

void FallingState::refreshTimer() {
  game_->timer_.expires_at(
      std::chrono::steady_clock::now() +
      boost::asio::chrono::milliseconds(game_->calculateGravity()));
  game_->timer_.async_wait(boost::bind(&FallingState::applyGravity, this));
}

void FallingState::hardDrop() {
  int linesDropped = 0;
  bool drop = true;
  while (drop) {
    try {
      game_->falling()->move(tetrimino::DOWN, game_->matrix().generateMask());
      linesDropped++;
    } catch (tetrimino::exceptions::MoveNotPossibleException& e) {
      drop = false;
      game_->score(linesDropped * 2);
      lock();
    }
  }
}

void FallingState::applyGravity() {
  try {
    game_->signalFalling();
    game_->updateGame(game_->fallingInsideMatrix());
    game_->falling()->move(tetrimino::DOWN, game_->matrix().generateMask());
    refreshTimer();
  } catch (tetrimino::exceptions::MoveNotPossibleException& ignored) {
    game_->state(new LockedDownState(game_));
  }
}

void FallingState::rotate(bool clockwise) {
  try {
    game_->falling()->rotate(clockwise, game_->matrix().generateMask());
    game_->updateGame(game_->fallingInsideMatrix());
  } catch (tetrimino::exceptions::RotationNotPossibleException& ignored) {
  }
}

void FallingState::lock() {
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