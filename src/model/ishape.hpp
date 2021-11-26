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

#ifndef ESI_ATLIR5_ATLC_PROJECT2_SRC_MODEL_ISHAPE_HPP_
#define ESI_ATLIR5_ATLC_PROJECT2_SRC_MODEL_ISHAPE_HPP_

#include <unordered_map>

#include "tetrimino.hpp"
namespace tetris::model::tetrimino {
class ITetrimino;
}  // namespace tetris::model::tetrimino

namespace tetris::model::shapes {
class IShape {
  friend tetris::model::tetrimino::ITetrimino;

 private:
  static std::unordered_map<
      tetris::model::tetrimino::Orientation,
      std::array<std::array<tetris::model::tetrimino::Mino, 4>, 4>>
      iShapes;
};
}  // namespace tetris::model::shapes

#endif  // ESI_ATLIR5_ATLC_PROJECT2_SRC_MODEL_ISHAPE_HPP_
