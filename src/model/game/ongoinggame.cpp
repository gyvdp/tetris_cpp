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

#include "model/game/ongoinggame.hpp"

#include <iostream>
#include <stdexcept>

#include "model/game/state/notstartedstate.hpp"

namespace tetris::model::game {

OngoingGame::OngoingGame(Player *player)
    : state_{std::make_unique<states::NotStartedState>(this)},
      player_{player},
      matrix_{10, 22},
      falling_{},
      next_{},
      hold_{} {
  if (player == nullptr) {
    throw std::invalid_argument("Player can not be null");
  }
}
void OngoingGame::state(std::unique_ptr<GameState> state) {
  state_.swap(state);
}

}  // namespace tetris::model::game