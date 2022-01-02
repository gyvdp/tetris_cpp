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

#include "model/game/state/fallingstate.hpp"

#include "catch2/catch.hpp"
#include "model/game/ongoinggame.hpp"
#include "model/game/player.hpp"
#include "model/game/state/exceptions/illegalstateexception.hpp"
#include "model/game/state/exceptions/startongoinggameexception.hpp"
#include "model/game/state/notstartedstate.hpp"
#include "model/tetrimino/direction.hpp"
#include "model/tetrimino/tetrimino_logic.hpp"

using namespace tetris::model::game::states;
using namespace tetris::model::tetrimino;
using namespace tetris::model::game;
using line = std::array<std::optional<Mino>, 4>;

TEST_CASE("falling state") {
  Player player("John", 123);
  std::unique_ptr<OngoingGame> game = std::make_unique<OngoingGame>(&player, 1);
  game->start();
  SECTION("Basic errors") {
    REQUIRE_THROWS_AS(game->start(), exceptions::StartOnGoingGameException);
    REQUIRE_THROWS_AS(game->lock(), exceptions::IllegalStateException);
  }
  SECTION("LEFT") {
    SECTION("S_MINO") {
      game->falling(std::make_shared<STetrimino>());
      game->getMatrix().set(S_MINO, 0, 3);
      game->move(LEFT);
      REQUIRE(game->falling()->X() == 3);
      REQUIRE(game->falling()->Y() == 0);
    }
    SECTION("T_MINO") {
      game->falling(std::make_shared<TTetrimino>());
      game->getMatrix().set(T_MINO, 0, 3);
      game->move(LEFT);
      REQUIRE(game->falling()->X() == 3);
      REQUIRE(game->falling()->Y() == 0);
    }
  }
  SECTION("RIGHT") {
    SECTION("I_MINO") {
      game->falling(std::make_shared<ITetrimino>());
      game->getMatrix().set(T_MINO, 1, 7);
      game->move(RIGHT);
      REQUIRE(game->falling()->X() == 3);
      REQUIRE(game->falling()->Y() == 0);
    }
    SECTION("O_MINO") {
      game->falling(std::make_shared<OTetrimino>());
      game->getMatrix().set(T_MINO, 1, 6);
      game->move(RIGHT);
      REQUIRE(game->falling()->X() == 3);
      REQUIRE(game->falling()->Y() == 0);
    }
  }
  SECTION("DOWN") {
    SECTION("I_MINO") {
      game->falling(std::make_shared<JTetrimino>());
      game->getMatrix().set(T_MINO, 2, 3);
      game->move(DOWN);
      REQUIRE(game->falling()->X() == 3);
      REQUIRE(game->falling()->Y() == 0);
    }
    SECTION("O_MINO") {
      game->falling(std::make_shared<LTetrimino>());
      game->getMatrix().set(T_MINO, 2, 3);
      game->move(DOWN);
      REQUIRE(game->falling()->X() == 3);
      REQUIRE(game->falling()->Y() == 0);
    }
  }
  SECTION("HOLD") {
    auto tempNext = game->next();
    auto tempFalling = game->falling()->type();
    game->holdFalling();
    REQUIRE(tempFalling == game->hold());
    REQUIRE(tempNext == game->falling()->type());
  }
  SECTION("CLOCKWISE") {
    game->falling(std::make_shared<LTetrimino>());
    game->getMatrix().set(T_MINO, 3, 1);
    game->rotate(true);
    REQUIRE(game->falling()->orientation() == NORTH);
  }
  SECTION("COUNTERCLOCKWISE") {
    game->falling(std::make_shared<LTetrimino>());
    game->getMatrix().set(T_MINO, 3, 2);
    game->rotate(false);
    REQUIRE(game->falling()->orientation() == NORTH);
  }
}
