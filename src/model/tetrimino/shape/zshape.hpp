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

#ifndef ESI_ATLIR5_ATLC_PROJECT2_INCLUDE_MODEL_TETRIMINO_SHAPE_ZSHAPE_HPP_
#define ESI_ATLIR5_ATLC_PROJECT2_INCLUDE_MODEL_TETRIMINO_SHAPE_ZSHAPE_HPP_

#include <array>
#include <map>
#include <optional>

#include "model/tetrimino/mino.hpp"
#include "model/tetrimino/orientation.hpp"

namespace tetris::model::tetrimino::shape {

using line = std::array<std::optional<Mino>, 4>;

/**
 * @brief Map with all the shapes for ZTetrimino based on his orientation
 */
static std::map<Orientation, std::array<line, 4>> zShapes{
    {NORTH,
     {line{Z_MINO, Z_MINO, std::nullopt, std::nullopt},
      line{std::nullopt, Z_MINO, Z_MINO, std::nullopt},
      line{std::nullopt, std::nullopt, std::nullopt, std::nullopt},
      line{std::nullopt, std::nullopt, std::nullopt, std::nullopt}}},
    {EAST,
     {line{std::nullopt, std::nullopt, Z_MINO, std::nullopt},
      line{std::nullopt, Z_MINO, Z_MINO, std::nullopt},
      line{std::nullopt, Z_MINO, std::nullopt, std::nullopt},
      line{std::nullopt, std::nullopt, std::nullopt, std::nullopt}}},
    {SOUTH,
     {line{std::nullopt, std::nullopt, std::nullopt, std::nullopt},
      line{Z_MINO, Z_MINO, std::nullopt, std::nullopt},
      line{std::nullopt, Z_MINO, Z_MINO, std::nullopt},
      line{std::nullopt, std::nullopt, std::nullopt, std::nullopt}}},
    {WEST,
     {line{std::nullopt, Z_MINO, std::nullopt, std::nullopt},
      line{Z_MINO, Z_MINO, std::nullopt, std::nullopt},
      line{Z_MINO, std::nullopt, std::nullopt, std::nullopt},
      line{std::nullopt, std::nullopt, std::nullopt, std::nullopt}}}};
}  // namespace tetris::model::tetrimino::shape
#endif  // ESI_ATLIR5_ATLC_PROJECT2_INCLUDE_MODEL_TETRIMINO_SHAPE_ZSHAPE_HPP_
