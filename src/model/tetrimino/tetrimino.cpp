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

#include "model/tetrimino/tetrimino.hpp"

#include <stdexcept>
#include <vector>

#include "model/tetrimino/exceptions/movenotpossibleexception.hpp"
#include "model/tetrimino/exceptions/rotationnotpossibleexception.hpp"

namespace tetris::model::tetrimino {

void Tetrimino::move(Direction direction) {
  tetris::utils::Coordinate newCoordinate = coordinate_.value() + direction;
  coordinate_.emplace(newCoordinate);
}
void Tetrimino::rotate(bool clockwise) {
  orientation_ = tetrimino::next(orientation_, clockwise);
}

void Tetrimino::rotate(bool clockwise,
                       const std::vector<std::vector<bool>>& matrixMask) {
  Orientation tempOrientation = tetrimino::next(orientation_, clockwise);
  auto tempMinos = minos_.at(tempOrientation);
  for (int i = 0; i < tempMinos.size(); i++) {
    for (int j = 0; j < tempMinos.at(i).size(); j++) {
      if ((matrixMask.at(i).at(j)) && (tempMinos.at(i).at(j) != std::nullopt))
        throw exceptions::RotationNotPossibleException("Rotation not possible",
                                                       __FILE__, __LINE__);
    }
  }
  orientation_ = tempOrientation;
}

void Tetrimino::move(Direction direction,
                     std::vector<std::vector<bool>> matrixMask) {
  tetris::utils::Coordinate newCoordinate = coordinate_.value() + direction;
  for (size_t line = 0; line < minos_.size(); ++line) {
    for (size_t col = 0; col < minos_.at(orientation_)[line].size(); ++col) {
      if (minos_.at(orientation_)[line][col].has_value()) {
        auto x = newCoordinate.x() + col;
        auto y = newCoordinate.y() + line;
        if (y >= 0 && y < matrixMask.size() && x >= 0 &&
            x < matrixMask.at(y).size()) {
          if (!matrixMask.at(y).at(x)) {
            throw exceptions::MoveNotPossibleException(
                "This move places the Tetrimino out of bound", __FILE__,
                __LINE__);
          }
        } else {
          throw exceptions::MoveNotPossibleException(
              "This move is impossible because there is a Mino in the way",
              __FILE__, __LINE__);
        }
      }
    }
  }
  coordinate_.emplace(newCoordinate);
}
}  // namespace tetris::model::tetrimino
