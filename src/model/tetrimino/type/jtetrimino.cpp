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

#include "model/tetrimino/type/jtetrimino.hpp"

#include <stdexcept>

#include "model/tetrimino/orientation.hpp"

namespace tetris::model::tetrimino {

JTetrimino::JTetrimino() : Tetrimino{shape::jShapes.at(NORTH)} {}

void JTetrimino::rotate(bool clockwise) {
  this->minos_ =
      shape::jShapes.at(tetrimino::rotate(this->orientation_, clockwise));
}

std::array<std::array<OptionalMino, 4>, 4> JTetrimino::rotateCheck(
    bool clockwise) {
  rotate(clockwise);
  return this->minos_;  // Make sure this shit returns a copy lol.
}

}  // namespace tetris::model::tetrimino