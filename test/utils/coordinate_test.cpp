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
#include "utils/coordinate.hpp"

#include "catch2/catch.hpp"

using namespace tetris::utils;

TEST_CASE("class Coordinate") {
  SECTION("Constructor") {
    SECTION("No parameters") {
      auto coordinate = Coordinate{};
      REQUIRE(coordinate.x() == 0);
      REQUIRE(coordinate.y() == 0);
    }
    SECTION("With parameters 1") {
      auto coordinate = Coordinate{5, 6};
      REQUIRE(coordinate.x() == 5);
      REQUIRE(coordinate.y() == 6);
    }
    SECTION("With parameters 2") {
      auto coordinate = Coordinate{-5, -77};
      REQUIRE(coordinate.x() == -5);
      REQUIRE(coordinate.y() == -77);
    }
  }
  SECTION("Operator+") {
    auto coordinate = Coordinate{};
    auto coordinate2 = Coordinate{5, 6};
    auto result = coordinate.operator+(coordinate2);
    REQUIRE(result.x() == 5);
    REQUIRE(result.y() == 6);
  }
}