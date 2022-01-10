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
#include <model/game/states/stoppedstate.hpp>
#include <stdexcept>

#include "model/game/states/blockedoutstate.hpp"
#include "model/game/states/exceptions/blockedoutexception.hpp"
#include "model/game/states/lockeddownstate.hpp"
#include "model/game/states/notstartedstate.hpp"
#include "model/tetrimino/exceptions/movenotpossibleexception.hpp"

namespace tetris::model::game {

OngoingGame::OngoingGame(Player* player, std::uint_fast64_t seed, bool managed)
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
      timer_{new QTimer{this}},
      managed_{managed} {
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
          emit lockUpdate();
          delete state_;
          hasHeld(false);
          state(new states::FallingState(this));
        } catch (states::exceptions::BlockedOutException& e) {
          delete state_;
          state(new states::BlockedOutState(this));
        }
        return;
      default:
        timer_->stop();
        delete state_;
        state(new states::StoppedState(this));
    }
  });
}

int OngoingGame::calculateGravity() const {
  return static_cast<int>(
      (std::pow((0.8 - ((level_ - 1) * 0.007)), level_ - 1)) * 1000.0);
}

void OngoingGame::clearLines() {
  auto lines = matrix_.getCompletedLines();
  if (!lines.empty()) {
    generatePoints(lines.size());
    int removed = 0;
    qDebug() << "Lignes: " << lines.size();
    for (long i = static_cast<long>(lines.size()) - 1; i >= 0; --i) {
      auto line = lines.at(i);
      qDebug() << "Ligne supprimée: " << line;

      for (long j = line + removed; j >= 0; --j) {
        for (int k = 0; k < matrix_.getMinos().at(j).size(); ++k) {
          if (j != 0) {
            matrix_.setLine(matrix_.getMinos().at(j - 1), j);
          } else {
            matrix_.removeLine(j);
          }
        }
      }
      removed++;
    }
  }
  emit linesUpdate(lines);
}

void OngoingGame::generatePoints(size_t lines) {
  lines_ += static_cast<int>(lines);
  level_ = (lines_ / 10) + 1;
  switch (lines) {
    case 1:
      score(100 * (level_ + 1));
      break;
    case 2:
      score(300 * (level_ + 1));
      break;
    case 3:
      score(500 * (level_ + 1));
      break;
    case 4:
      score(800 * (level_ + 1));
    default:
      break;
  }
  emit scoreUpdate(score_);
}

std::vector<std::vector<OptionalMino>> OngoingGame::fallingInsideMatrix() {
  Matrix matrix = matrix_;
  matrix.add(falling_);
  auto minos = matrix.getMinos();
  return {&minos[2], &minos[22]};
}

void OngoingGame::refreshFallingTimer() {
  if (isManaged()) {
    timer_->stop();
    timer_->start(calculateGravity());
  }
}

void OngoingGame::refreshLockingTimer() {
  if (isManaged()) {
    timer_->stop();
    timer_->start(50);
  }
}

void OngoingGame::moveFalling(tetrimino::Direction direction) {
  falling_->move(direction, matrix_.generateMask());
  emit matrixUpdate(fallingInsideMatrix());
  emit moveUpdate(direction);
}

void OngoingGame::rotateFalling(bool clockwise) {
  falling_->rotate(clockwise, matrix_.generateMask());
  emit matrixUpdate(fallingInsideMatrix());
  emit rotateUpdate(clockwise);
}

void OngoingGame::lock() {
  getMatrix().add(falling());
  try {
    falling(
        tetrimino::createTetrimino(next().value(), getMatrix().generateMask()));
    next(pickMino());
    clearLines();
    emit lockUpdate();
    refreshFallingTimer();
  } catch (states::exceptions::BlockedOutException& e) {
    state(new states::BlockedOutState(this));
    delete this;
  }
  hasHeld(false);
}

void OngoingGame::state(GameState* state) { state_ = state; }

Matrix& OngoingGame::getMatrix() { return matrix_; }

}  // namespace tetris::model::game