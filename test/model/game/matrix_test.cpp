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
#include "model/game/matrix.hpp"

#include "catch2/catch.hpp"
#include "model/tetrimino/tetrimino_logic.hpp"

using namespace tetris::model::game;
using namespace tetris::model::tetrimino;
using namespace tetris::utils;

TEST_CASE("Matrix tests") {
  Matrix matrix{20, 20};
  SECTION("Adding tetrimino") {
    matrix.add(std::make_shared<STetrimino>());
    REQUIRE(matrix({4, 0}) == S_MINO);
    REQUIRE(matrix({5, 0}) == S_MINO);
    REQUIRE(matrix({3, 1}) == S_MINO);
    REQUIRE(matrix({4, 1}) == S_MINO);
  }

  SECTION("Get completed lines") {
    for (size_t i = 0; i < matrix.width(); i++) {
      matrix.set(S_MINO, 0, static_cast<int>(i));
    }
    auto lines = matrix.getCompletedLines();
    REQUIRE(lines.at(0) == 0);
  }
}