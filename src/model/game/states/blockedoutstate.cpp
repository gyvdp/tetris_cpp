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

#include "model/game/states/blockedoutstate.hpp"

#include <model/game/states/exceptions/blockedoutexception.hpp>
#include <model/game/states/stoppedstate.hpp>

namespace tetris::model::game::states {

void BlockedOutState::start() {
  throw exceptions::BlockedOutException("There is already a game started",
                                        __FILE__, __LINE__);
}

void BlockedOutState::stop() { game_->state(new StoppedState(game_)); }

void BlockedOutState::move(tetrimino::Direction direction) {
  throw exceptions::BlockedOutException("Cannot move when blocked out",
                                        __FILE__, __LINE__);
}

void BlockedOutState::holdFalling() {
  throw exceptions::BlockedOutException("Cannot hold when blocked out",
                                        __FILE__, __LINE__);
}

void BlockedOutState::softDrop() {
  throw exceptions::BlockedOutException("Cannot drop when blocked out",
                                        __FILE__, __LINE__);
}

void BlockedOutState::hardDrop() {
  throw exceptions::BlockedOutException("Cannot drop when blocked out",
                                        __FILE__, __LINE__);
}

void BlockedOutState::rotate(bool clockwise) {
  throw exceptions::BlockedOutException("Cannot rotate when blocked out",
                                        __FILE__, __LINE__);
}

void BlockedOutState::lock() {
  throw exceptions::BlockedOutException("Cannot lock when blocked out",
                                        __FILE__, __LINE__);
}

}  // namespace tetris::model::game::states