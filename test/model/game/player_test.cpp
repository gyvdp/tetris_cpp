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
#include "model/game/player.hpp"

#include "catch2/catch.hpp"

using namespace tetris::model::game;

TEST_CASE("class Player") {
  SECTION("Constructor") {
    SECTION("Only name sets") {
      auto player = Player("Thomas");
      REQUIRE(player.name() == "Thomas");
      REQUIRE(player.highScore() == 0);
    }
    SECTION("Name and HighScore sets") {
      auto player = Player("Andrew", 10);
      REQUIRE(player.name() == "Andrew");
      REQUIRE(player.highScore() == 10);
    }
    SECTION("Exceptions") {
      SECTION("Exception message") {
        try {
          CHECK_THROWS(new Player("aaaaaaaaaaaaa"));
        } catch (std::invalid_argument& e) {
          REQUIRE(std::string(e.what()) == "Player name is not valid");
        }
      }
      SECTION("Exception throws when empty") {
        try {
          CHECK_THROWS(new Player(""));
        } catch (std::invalid_argument& e) {
          REQUIRE(std::string(e.what()) == "Player name is not valid");
        }
      }
      SECTION("Exception bigger than 13 characters") {
        CHECK_THROWS(new Player("aaaaaaaaaaaaa"));
      }
      SECTION("Exception equals 12 characters") {
        CHECK_NOTHROW(new Player("aaaaaaaaaaaa"));
      }
      SECTION("Exception smaller than 4 characters") {
        CHECK_THROWS(new Player("aaa"));
      }
      SECTION("Exception equals 4 characters") {
        CHECK_NOTHROW(new Player("aaaa"));
      }
      SECTION("Name contains only blanks") {
        CHECK_THROWS(new Player("        a"));
      }
    }
  }
}