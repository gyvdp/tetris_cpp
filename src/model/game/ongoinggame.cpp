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

#include "model/game/ongoinggame.hpp"

#include <QDebug>
#include <stdexcept>

#include "model/game/states/blockedoutstate.hpp"
#include "model/game/states/exceptions/blockedoutexception.hpp"
#include "model/game/states/lockeddownstate.hpp"
#include "model/game/states/notstartedstate.hpp"
#include "model/tetrimino/exceptions/movenotpossibleexception.hpp"

namespace tetris::model::game {

OngoingGame::OngoingGame(Player* player, std::uint_fast64_t seed)
    : state_{new states::NotStartedState(this)},
      player_{player},
      matrix_{10, 22},
      generator_{seed},
      falling_{},
      next_{},
      hold_{},
      score_{0},
      level_{1},
      lines_{0},
      timer_{new QTimer{this}} {
  if (player == nullptr) {
    throw std::invalid_argument("Player can not be null");
  }

  connect(timer_, &QTimer::timeout, [this]() {
    switch (state_->type()) {
      case StateType::FALLING:
        try {
          moveFalling(tetrimino::DOWN);
          refreshFallingTimer();
        } catch (tetrimino::exceptions::MoveNotPossibleException& ignored) {
          delete state_;
          state(new states::LockedDownState(this));
        }
        return;
      case StateType::LOCKED_DOWN:
        matrix_.add(falling_);
        try {
          falling(tetrimino::createTetrimino(next().value(),
                                             getMatrix().generateMask()));
          next(pickMino());
          clearLines();
          delete state_;
          state(new states::FallingState(this));
        } catch (states::exceptions::BlockedOutException& e) {
          delete state_;
          state(new states::BlockedOutState(this));
        }
        return;
      default:
        qDebug() << "OUPS";
    }
  });
}

int OngoingGame::calculateGravity() const {
  return static_cast<int>(
      (std::pow((0.8 - ((level_ - 1) * 0.007)), level_ - 1)) * 1000.0);
}

void OngoingGame::clearLines() {
  auto lines = matrix_.getCompletedLines();
  generatePoints(lines.size());
}

void OngoingGame::generatePoints(size_t lines) {
  lines_ += static_cast<int>(lines);
  if (lines != 0 && lines % 10 == 0) {
    level_++;
  }
  while (lines != 0) {
    switch (lines) {
      case 1:
        score(1200 * (level_ + 1));
        lines -= 1;
        break;
      case 2:
        score(1200 * (level_ + 1));
        lines -= 2;
        break;
      case 3:
        score(1200 * (level_ + 1));
        lines -= 3;
        break;
      default:
        score(1200 * (level_ + 1));
        lines -= 4;
        break;
    }
  }
}

std::vector<std::vector<OptionalMino>> OngoingGame::fallingInsideMatrix() {
  Matrix matrix = matrix_;
  matrix.add(falling_);
  auto minos = matrix.getMinos();
  return {&minos[2], &minos[22]};
}

void OngoingGame::refreshFallingTimer() {
  timer_->stop();
  timer_->start(calculateGravity());
}

void OngoingGame::refreshLockingTimer() {
  timer_->stop();
  timer_->start(50);
}

void OngoingGame::moveFalling(tetrimino::Direction direction) {
  falling_->move(direction, matrix_.generateMask());
  emit matrixUpdate(fallingInsideMatrix());
}

void OngoingGame::rotateFalling(bool clockwise) {
  falling_->rotate(clockwise, matrix_.generateMask());
  emit matrixUpdate(fallingInsideMatrix());
}

void OngoingGame::state(GameState* state) { state_ = state; }

Matrix& OngoingGame::getMatrix() { return matrix_; }

}  // namespace tetris::model::game