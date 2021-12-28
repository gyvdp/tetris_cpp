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

#ifndef ESI_ATLIR5_ATLC_PROJECT2_SRC_MODEL_DIRECTION_HPP_
#define ESI_ATLIR5_ATLC_PROJECT2_SRC_MODEL_DIRECTION_HPP_

#include <array>

#include "utils/coordinate.hpp"

namespace tetris::model::tetrimino {

/**
 * @brief enum of different directions of a move on a Tetrimino
 */
enum Direction { DOWN, RIGHT, LEFT };

/**
 * @brief Array of different directions
 */
static constexpr std::array DIRECTIONS{DOWN, RIGHT, LEFT};

/**
 * @brief Get the delta coordinate for a particular direction
 *
 * @param direction The direction to get the delta
 * @return A coordinate with the delta of x and y for the given direction
 */
static constexpr utils::Coordinate delta(Direction direction) {
  switch (direction) {
    case DOWN:
      return utils::Coordinate{0, 1};
    case RIGHT:
      return utils::Coordinate{1, 0};
    case LEFT:
      return utils::Coordinate{-1, 0};
    default:
      return utils::Coordinate{};
  }
}

/**
 * @brief The plus operator apply a direction on a Coordinate
 *
 * @param start The start position
 * @param direction The direction to apply to the Coordinate
 * @return The moved Coordinate
 */
static utils::Coordinate operator+(utils::Coordinate start,
                                   Direction direction) {
  return start + delta(direction);
}

}  // namespace tetris::model::tetrimino

#endif  // ESI_ATLIR5_ATLC_PROJECT2_SRC_MODEL_DIRECTION_HPP_
