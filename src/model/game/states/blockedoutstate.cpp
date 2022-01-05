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

#include "model/game/state/blockedoutstate.hpp"

#include <model/game/state/stoppedstate.hpp>

#include "model/game/state/exceptions/startongoinggameexception.hpp"
#include "model/game/state/exceptions/stoppedgameexception.hpp"

namespace tetris::model::game::states {

void BlockedOutState::start() {
  throw exceptions::StoppedGameException("There is already a game started",
                                         __FILE__, __LINE__);
}

void BlockedOutState::stop() {
  game_->stop();
  game_->state(new StoppedState(game_));
}

void BlockedOutState::move(tetrimino::Direction direction) {
  throw exceptions::StoppedGameException("Cannot move when blocked out",
                                         __FILE__, __LINE__);
}

void BlockedOutState::holdFalling() {
  throw exceptions::StoppedGameException("Cannot hold when blocked out",
                                         __FILE__, __LINE__);
}

void BlockedOutState::softDrop() {
  throw exceptions::StoppedGameException("Cannot drop when blocked out",
                                         __FILE__, __LINE__);
}

void BlockedOutState::hardDrop() {
  throw exceptions::StoppedGameException("Cannot drop when blocked out",
                                         __FILE__, __LINE__);
}

void BlockedOutState::rotate(bool clockwise) {
  throw exceptions::StoppedGameException("Cannot rotate when blocked out",
                                         __FILE__, __LINE__);
}

void BlockedOutState::lock() {
  throw exceptions::StoppedGameException("Cannot lock when blocked out",
                                         __FILE__, __LINE__);
}

}  // namespace tetris::model::game::states