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

#include <model/game/state/stoppedstate.hpp>
#include <model/tetrimino/tetrimino_logic.hpp>

#include "model/game/state/exceptions/illegalstateexception.hpp"
#include "model/game/state/exceptions/startongoinggameexception.hpp"
namespace tetris::model::game::states {

void LockedDownState::start() {
  throw exceptions::StartOnGoingGameException("Cannot move when blocked out",
                                              __FILE__, __LINE__);
}

void LockedDownState::stop() {
  game_->state(std::make_unique<states::StoppedState>(game_));

}

void LockedDownState::move(tetrimino::Direction direction) {
  throw exceptions::IllegalStateException("Cannot move when blocked out",
                                          __FILE__, __LINE__);
}

void LockedDownState::holdFalling() {
  throw exceptions::IllegalStateException("Cannot move when blocked out",
                                          __FILE__, __LINE__);
}

void LockedDownState::softDrop() {
  throw exceptions::IllegalStateException("Cannot move when blocked out",
                                          __FILE__, __LINE__);
}

void LockedDownState::hardDrop() {
  throw exceptions::IllegalStateException("Cannot move when blocked out",
                                          __FILE__, __LINE__);
}

void LockedDownState::rotate(bool clockwise) {
  throw exceptions::IllegalStateException("Cannot move when blocked out",
                                          __FILE__, __LINE__);
}

void LockedDownState::lock() {
  game_->matrix().add(game_->falling());
  hasHold_ = false;
  game_->falling(tetrimino::createTetrimino(game_->next() != std::nullopt
                                                ? game_->next().value()
                                                : tetrimino::S_MINO));
}

}  // namespace tetris::model::game::states