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

#include "stoppedstate.hpp"

#include "model/game/state/exceptions/stoppedgameexception.hpp"

namespace tetris::model::game::states {

#define stoppedGame(arg)                                           \
  throw exceptions::StoppedGameException(arg, __FILE__, __LINE__); \
  ;

void StoppedState::start() { stoppedGame("game cannot start if stopped"); }

void StoppedState::stop() { stoppedGame("game cannot stop if stopped"); }

void StoppedState::move(tetrimino::Direction direction) {
  stoppedGame("game cannot move if stopped");
}

void StoppedState::holdFalling() { stoppedGame("game cannot hold if stopped"); }

void StoppedState::softDrop() { stoppedGame("game cannot drop if stopped"); }

void StoppedState::hardDrop() { stoppedGame("game cannot drop if stopped"); }

void StoppedState::rotate(bool clockwise) {
  stoppedGame("game cannot rotate if stopped");
}

void StoppedState::lock() { stoppedGame("game cannot start if stopped"); }

}  // namespace tetris::model::game::states