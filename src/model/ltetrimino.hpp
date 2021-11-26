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

//
// Created by Thoma on 26-11-21.
//

#ifndef ESI_ATLIR5_ATLC_PROJECT2_SRC_MODEL_LTETRIMINO_HPP_
#define ESI_ATLIR5_ATLC_PROJECT2_SRC_MODEL_LTETRIMINO_HPP_

#include "model/lshape.hpp"

namespace tetris::model::tetrimino {

class LTetrimino : public tetris::model::tetrimino::Tetrimino {
 private:
 public:
  LTetrimino() {
    this->minos_ =
        tetris::model::shapes::LShape::lShapes.at(this->orientation_);
    this->type_ = Mino::L_MINO;
  }

  // TODO Apres avoir fait Orientation

  std::array<std::array<Mino, 4>, 4> rotatedShape(bool clockwise) override {
    // return LShapes_.get(Orientation.next(orientation_, clockwise));
    throw std::invalid_argument("A faire apres Orientation");
  }
};
}  // namespace tetris::model::tetrimino
#endif  // ESI_ATLIR5_ATLC_PROJECT2_SRC_MODEL_LTETRIMINO_HPP_
