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

#include "model/tetrimino.hpp"

#include "model/itetrimino.hpp"
#include "model/jtetrimino.hpp"
#include "model/ltetrimino.hpp"

// TODO @Andrew Method move()

//  bool tetris::model::tetrimino::Tetrimino::move(Direction direction,
//                                                 boolean[][] freeMask) {
//    Mino[][] minos_ = this.getMinos();
//    boolean movable = true;
//    for (int i = 0; i < minos_.length; i++) {
//      for (int j = 0; j < minos_[i].length; j++) {
//        int x = j + 1 + direction.getDeltaX();
//        int y = i + 1 + direction.getDeltaY();
//
//        if (!freeMask[y][x] && minos_[i][j] != null) {
//          movable = false;
//        }
//      }
//    }
//
//    if (movable) {
//      this.x += direction.getDeltaX();
//      this.y += direction.getDeltaY();
//      return true;
//    }
//    return false;
//      }

// TODO @Andrew Method Rotate()

//  bool tetris::model::tetrimino::Tetrimino::rotate(bool clockwise, bool[][]
//  freeMask) {
//    Orientation nextOrientation = Orientation.next(orientation, clockwise);
//    Mino[][] rotated = rotatedShape(clockwise);
//
//    for (int i = 0; i < minos_.length; i++) {
//      for (int j = 0; j < minos_[1].length; j++) {
//        if (!freeMask[i][j] && rotated[i][j] != null) {
//          return false;
//        }
//      }
//    }
//
//    minos_ = rotated;
//    orientation = nextOrientation;
//    return true;
//  };

std::unique_ptr<tetris::model::tetrimino::Tetrimino>
tetris::model::tetrimino::Tetrimino::createTetrimino(Mino mino) {
  switch (static_cast<int>(mino)) {
    case 0:  // L_MINO
      return std::make_unique<tetris::model::tetrimino::LTetrimino>(
          tetris::model::tetrimino::LTetrimino());
      break;
    case 1:  // J_MINO
      return std::make_unique<tetris::model::tetrimino::JTetrimino>(
          tetris::model::tetrimino::JTetrimino());
      break;
    case 2:  // Z_MINO

      break;
    case 3:  // S_MINO

      break;
    case 4:  // O_MINO

      break;
    case 5:  // I_MINO
      return std::make_unique<tetris::model::tetrimino::ITetrimino>(
          tetris::model::tetrimino::ITetrimino());
      break;
    case 6:  // T_MINO

      break;
  }
  throw std::invalid_argument("This Mino doesn't exists");
}

std::string tetris::model::tetrimino::Tetrimino::toString() {
  std::string result;

  for (auto line : this->minos_) {
    for (auto mino : line) {
      if (mino == Mino::EMPTY) {
        result.append("o");
      } else {
        result.append("x");
      }
    }
    result.append("\n");
  }

  return result;
}
