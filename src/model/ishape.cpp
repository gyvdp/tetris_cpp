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

#include "model/ishape.hpp"
namespace tetris::model::shapes {
tetris::model::shapes::IShape::IShape() {
  // NORTH Orientation
  this->iShapes_.insert(
      std::pair<tetris::model::tetrimino::Orientation,
                std::array<std::array<tetris::model::tetrimino::Mino, 4>, 4>>{
          tetris::model::tetrimino::Orientation::NORTH,
          std::array<std::array<tetris::model::tetrimino::Mino, 4>, 4>{
              std::array<tetris::model::tetrimino::Mino, 4>{
                  tetris::model::tetrimino::Mino::EMPTY,
                  tetris::model::tetrimino::Mino::EMPTY,
                  tetris::model::tetrimino::Mino::EMPTY,
                  tetris::model::tetrimino::Mino::EMPTY},
              std::array<tetris::model::tetrimino::Mino, 4>{
                  tetris::model::tetrimino::Mino::I_MINO,
                  tetris::model::tetrimino::Mino::I_MINO,
                  tetris::model::tetrimino::Mino::I_MINO,
                  tetris::model::tetrimino::Mino::I_MINO},
              std::array<tetris::model::tetrimino::Mino, 4>{
                  tetris::model::tetrimino::Mino::EMPTY,
                  tetris::model::tetrimino::Mino::EMPTY,
                  tetris::model::tetrimino::Mino::EMPTY,
                  tetris::model::tetrimino::Mino::EMPTY},
              std::array<tetris::model::tetrimino::Mino, 4>{
                  tetris::model::tetrimino::Mino::EMPTY,
                  tetris::model::tetrimino::Mino::EMPTY,
                  tetris::model::tetrimino::Mino::EMPTY,
                  tetris::model::tetrimino::Mino::EMPTY},
          }});

  // SOUTH Orientation
  this->iShapes_.insert(
      std::pair<tetris::model::tetrimino::Orientation,
                std::array<std::array<tetris::model::tetrimino::Mino, 4>, 4>>{
          tetris::model::tetrimino::Orientation::SOUTH,
          std::array<std::array<tetris::model::tetrimino::Mino, 4>, 4>{
              std::array<tetris::model::tetrimino::Mino, 4>{
                  tetris::model::tetrimino::Mino::EMPTY,
                  tetris::model::tetrimino::Mino::EMPTY,
                  tetris::model::tetrimino::Mino::EMPTY,
                  tetris::model::tetrimino::Mino::EMPTY},
              std::array<tetris::model::tetrimino::Mino, 4>{
                  tetris::model::tetrimino::Mino::EMPTY,
                  tetris::model::tetrimino::Mino::EMPTY,
                  tetris::model::tetrimino::Mino::EMPTY,
                  tetris::model::tetrimino::Mino::EMPTY},
              std::array<tetris::model::tetrimino::Mino, 4>{
                  tetris::model::tetrimino::Mino::I_MINO,
                  tetris::model::tetrimino::Mino::I_MINO,
                  tetris::model::tetrimino::Mino::I_MINO,
                  tetris::model::tetrimino::Mino::I_MINO},
              std::array<tetris::model::tetrimino::Mino, 4>{
                  tetris::model::tetrimino::Mino::EMPTY,
                  tetris::model::tetrimino::Mino::EMPTY,
                  tetris::model::tetrimino::Mino::EMPTY,
                  tetris::model::tetrimino::Mino::EMPTY},
          }});

  // EAST Orientation
  this->iShapes_.insert(
      std::pair<tetris::model::tetrimino::Orientation,
                std::array<std::array<tetris::model::tetrimino::Mino, 4>, 4>>{
          tetris::model::tetrimino::Orientation::EAST,
          std::array<std::array<tetris::model::tetrimino::Mino, 4>, 4>{
              std::array<tetris::model::tetrimino::Mino, 4>{
                  tetris::model::tetrimino::Mino::EMPTY,
                  tetris::model::tetrimino::Mino::EMPTY,
                  tetris::model::tetrimino::Mino::I_MINO,
                  tetris::model::tetrimino::Mino::EMPTY},
              std::array<tetris::model::tetrimino::Mino, 4>{
                  tetris::model::tetrimino::Mino::EMPTY,
                  tetris::model::tetrimino::Mino::EMPTY,
                  tetris::model::tetrimino::Mino::I_MINO,
                  tetris::model::tetrimino::Mino::EMPTY},
              std::array<tetris::model::tetrimino::Mino, 4>{
                  tetris::model::tetrimino::Mino::EMPTY,
                  tetris::model::tetrimino::Mino::EMPTY,
                  tetris::model::tetrimino::Mino::I_MINO,
                  tetris::model::tetrimino::Mino::EMPTY},
              std::array<tetris::model::tetrimino::Mino, 4>{
                  tetris::model::tetrimino::Mino::EMPTY,
                  tetris::model::tetrimino::Mino::EMPTY,
                  tetris::model::tetrimino::Mino::I_MINO,
                  tetris::model::tetrimino::Mino::EMPTY},
          }});

  // WEST Orientation
  this->iShapes_.insert(
      std::pair<tetris::model::tetrimino::Orientation,
                std::array<std::array<tetris::model::tetrimino::Mino, 4>, 4>>{
          tetris::model::tetrimino::Orientation::WEST,
          std::array<std::array<tetris::model::tetrimino::Mino, 4>, 4>{
              std::array<tetris::model::tetrimino::Mino, 4>{
                  tetris::model::tetrimino::Mino::EMPTY,
                  tetris::model::tetrimino::Mino::I_MINO,
                  tetris::model::tetrimino::Mino::EMPTY,
                  tetris::model::tetrimino::Mino::EMPTY},
              std::array<tetris::model::tetrimino::Mino, 4>{
                  tetris::model::tetrimino::Mino::EMPTY,
                  tetris::model::tetrimino::Mino::I_MINO,
                  tetris::model::tetrimino::Mino::EMPTY,
                  tetris::model::tetrimino::Mino::EMPTY},
              std::array<tetris::model::tetrimino::Mino, 4>{
                  tetris::model::tetrimino::Mino::EMPTY,
                  tetris::model::tetrimino::Mino::I_MINO,
                  tetris::model::tetrimino::Mino::EMPTY,
                  tetris::model::tetrimino::Mino::EMPTY},
              std::array<tetris::model::tetrimino::Mino, 4>{
                  tetris::model::tetrimino::Mino::EMPTY,
                  tetris::model::tetrimino::Mino::I_MINO,
                  tetris::model::tetrimino::Mino::EMPTY,
                  tetris::model::tetrimino::Mino::EMPTY},
          }});
}
}  // namespace tetris::model::shapes
