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

#include "catch2/catch.hpp"
#include "model/game/ongoinggame.hpp"
#include "model/game/player.hpp"
#include "model/game/state/exceptions/notstartedexception.hpp"
#include "model/game/state/notstartedstate.hpp"
#include "model/tetrimino/direction.hpp"
#include "model/tetrimino/tetrimino_logic.hpp"
using namespace tetris::model::game::states;
using namespace tetris::model::tetrimino;
using namespace tetris::model::game;

TEST_CASE("stopped state") {
  Player player("John", 123);
  std::unique_ptr<OngoingGame> game =
      std::make_unique<OngoingGame>(OngoingGame(&player, 1));
  std::unique_ptr<GameState> gameState =
      std::make_unique<states::NotStartedState>(
          states::NotStartedState(game.get()));
  game->state(std::move(gameState));
  REQUIRE_THROWS_AS(game->stop(), exceptions::NotStartedException);
  REQUIRE_THROWS_AS(game->holdFalling(), exceptions::NotStartedException);
  REQUIRE_THROWS_AS(game->softDrop(), exceptions::NotStartedException);
  REQUIRE_THROWS_AS(game->hardDrop(), exceptions::NotStartedException);
  REQUIRE_THROWS_AS(game->rotate(true), exceptions::NotStartedException);
  REQUIRE_THROWS_AS(game->lock(), exceptions::NotStartedException);
  REQUIRE_THROWS_AS(game->move(LEFT), exceptions::NotStartedException);
}
