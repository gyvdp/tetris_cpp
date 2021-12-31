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

#include "model/game/state/exceptions/ongoinggame.hpp"
#include "model/game/state/exceptions/movenotpossibleexception.hpp"
#include "model/game/state/exceptions/rotationnotpossibleexception.hpp"

namespace tetris::model::game::states {

#define gameNotStarted(arg)                                       \
  throw exceptions::onGoingGameException(arg, __FILE__, __LINE__); \
  ;
#define moveNotAllowed(arg)                                       \
  throw exceptions::moveNotPossibleException(arg, __FILE__, __LINE__); \
  ;                                                               \

#define rotationNotAllowed(arg)                                       \
  throw exceptions::rotationNotPossibleException(arg, __FILE__, __LINE__); \
  ;

void BlockedOutState::start() {
  gameNotStarted("There is already a game started");
}

void BlockedOutState::stop() {
  // TODO
}

void BlockedOutState::move(tetrimino::Direction direction) {
  moveNotAllowed("Cannot move when blocked out");
}

void BlockedOutState::holdFalling() {
  // TODO
}

void BlockedOutState::softDrop() {
  // TODO
}

void BlockedOutState::hardDrop() {
  // TODO
}

void BlockedOutState::rotate(bool clockwise) {
  rotationNotAllowed("Rotation is not allowed when locked out");
}

void BlockedOutState::lock() {
  // TODO
}

}  // namespace tetris::model::game::states