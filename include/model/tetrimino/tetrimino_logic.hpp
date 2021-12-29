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

#ifndef ESI_ATLIR5_ATLC_PROJECT2_INCLUDE_MODEL_TETRIMINO_TYPE_CREATETETRIMINO_H_
#define ESI_ATLIR5_ATLC_PROJECT2_INCLUDE_MODEL_TETRIMINO_TYPE_CREATETETRIMINO_H_

#include <memory>

#include "mino.hpp"
#include "model/tetrimino/type/itetrimino.hpp"
#include "model/tetrimino/type/jtetrimino.hpp"
#include "model/tetrimino/type/ltetrimino.hpp"
#include "model/tetrimino/type/otetrimino.hpp"
#include "model/tetrimino/type/stetrimino.hpp"
#include "model/tetrimino/type/ttetrimino.hpp"
#include "model/tetrimino/type/ztetrimino.hpp"

class Tetrimino;
namespace tetris::model::tetriminotetris::model::tetrimino {
/**
 * @brief Create a tetrimino from a mino
 *
 * @param mino Mino to create into tetrimino
 * @return New tetrimino created from mino
 */
static std::shared_ptr<Tetrimino> createTetrimino(Mino mino) {
  switch (mino) {
    case L_MINO:
      return std::make_shared<LTetrimino>(LTetrimino());
    case J_MINO:
      return std::make_shared<JTetrimino>(JTetrimino());
    case Z_MINO:
      return std::make_shared<ZTetrimino>(ZTetrimino());
    case S_MINO:
      return std::make_shared<STetrimino>(STetrimino());
    case O_MINO:
      return std::make_shared<OTetrimino>(OTetrimino());
    case I_MINO:
      return std::make_shared<ITetrimino>(ITetrimino());
    case T_MINO:
      return std::make_shared<TTetrimino>(TTetrimino());
    default:
      return nullptr;
  }
}
}  // namespace tetris::model::tetriminotetris::model::tetrimino
#endif  // ESI_ATLIR5_ATLC_PROJECT2_INCLUDE_MODEL_TETRIMINO_TYPE_CREATETETRIMINO_H_
