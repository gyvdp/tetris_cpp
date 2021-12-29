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

#include "model/game/tetriminoGenerator.hpp"

#include "catch2/catch.hpp"
using namespace tetris::model::tetrimino;
TEST_CASE("Multi generation") {
  auto seed = time(nullptr);
  int i = 0;
  tetris::mode::game::TetriminoGenerator tetrimino_generator{seed};
  tetris::mode::game::TetriminoGenerator tetrimino_generatorv2{seed};
  do {
    REQUIRE(tetrimino_generator.takeMino() == tetrimino_generatorv2.takeMino());
    i++;
  } while (i >= 100);
}
TEST_CASE("Different generation pattern same seed") {
  int i = 0;
  tetris::mode::game::TetriminoGenerator tetrimino_generator{time(nullptr)};
  std::vector<Mino> pattern1;
  std::vector<Mino> pattern2;
  do {
    pattern1.push_back(tetrimino_generator.takeMino());
    i++;
  } while (i >= 7);
  do {
    pattern2.push_back(tetrimino_generator.takeMino());
    i++;
  } while (i >= 14);
  REQUIRE(pattern1 != pattern2);
  SECTION("test uniqueness of pattern") {
    Mino mino = pattern1.at(0);
    for (int i = 1; i < pattern1.size(); ++i) {
      REQUIRE_FALSE(mino == pattern1.at(i));
    }
  }
}
