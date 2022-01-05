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

#include "model/tetrimino/direction.hpp"

#include "catch2/catch.hpp"

using namespace tetris::model::tetrimino;
using namespace tetris::utils;

TEST_CASE("") {
  SECTION("delta") {
    SECTION("RIGHT") {
      Coordinate coordinate = delta(RIGHT);
      REQUIRE(coordinate.x() == 1);
      REQUIRE(coordinate.y() == 0);
    }
    SECTION("DOWN") {
      Coordinate coordinate = delta(DOWN);
      REQUIRE(coordinate.x() == 0);
      REQUIRE(coordinate.y() == 1);
    }
    SECTION("LEFT") {
      Coordinate coordinate = delta(LEFT);
      REQUIRE(coordinate.x() == -1);
      REQUIRE(coordinate.y() == 0);
    }
  }

  SECTION("operator") {
    SECTION("RIGHT") {
      tetris::utils::Coordinate baseCoordinate = {4, 4};
      tetris::utils::Coordinate newCoordinate = baseCoordinate + RIGHT;
      REQUIRE(newCoordinate.x() == 5);
      REQUIRE(newCoordinate.y() == 4);
    }
    SECTION("DOWN") {
      tetris::utils::Coordinate baseCoordinate = {4, 4};
      tetris::utils::Coordinate newCoordinate = baseCoordinate + DOWN;
      REQUIRE(newCoordinate.x() == 4);
      REQUIRE(newCoordinate.y() == 5);
    }
    SECTION("LEFT") {
      tetris::utils::Coordinate baseCoordinate = {4, 4};
      tetris::utils::Coordinate newCoordinate = baseCoordinate + LEFT;
      REQUIRE(newCoordinate.x() == 3);
      REQUIRE(newCoordinate.y() == 4);
    }
  }
}