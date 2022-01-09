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

#include <iostream>

#include "catch2/catch.hpp"
#include "model/game/ongoinggame.hpp"
#include "model/game/player.hpp"
#include "model/game/state/exceptions/blockedoutexception.hpp"
#include "model/tetrimino/tetrimino_logic.hpp"
using namespace tetris::model::tetrimino;
using namespace tetris::model::game::states::exceptions;
TEST_CASE("End of game") {
  tetris::model::game::Player player("John", 123);
  tetris::model::game::OngoingGame game(&player, 1, nullptr);
  game.getMatrix().set(S_MINO, 1, 4);
  REQUIRE_THROWS_AS(createTetrimino(O_MINO, game.getMatrix().generateMask()),
                    BlockedOutException);
}