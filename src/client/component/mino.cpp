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

#include "mino.hpp"

namespace tetris::client::component {

Mino::Mino(const OptionalMino type, QGraphicsItem *parent)
    : QGraphicsPixmapItem{resource(type), parent}, type_{type} {}

QPixmap Mino::resource(const OptionalMino type) {
  if (!type.has_value()) {
    return QPixmap{64, 64};
  }

  switch (type.value()) {
    case tetris::model::tetrimino::Mino::T_MINO:
    case tetris::model::tetrimino::Mino::O_MINO:
    case tetris::model::tetrimino::Mino::I_MINO:
      return QPixmap{":/mino/A0.png"};
    case tetris::model::tetrimino::Mino::L_MINO:
    case tetris::model::tetrimino::Mino::Z_MINO:
      return QPixmap{":/mino/B0.png"};
    case tetris::model::tetrimino::Mino::J_MINO:
    case tetris::model::tetrimino::Mino::S_MINO:
    default:
      return QPixmap{":/mino/C0.png"};
  }
}

}  // namespace tetris::client::component