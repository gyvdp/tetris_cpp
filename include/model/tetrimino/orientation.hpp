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

#ifndef ESI_ATLIR5_ATLC_PROJECT2_SRC_MODEL_ORIENTATION_HPP_
#define ESI_ATLIR5_ATLC_PROJECT2_SRC_MODEL_ORIENTATION_HPP_

#include <array>
namespace tetris::model::tetrimino {

/**
 * @brief Enumeration of different Orientations of a Tetrimino (for rotations)
 */
enum Orientation { NORTH, EAST, SOUTH, WEST };

/**
 * @brief Array with all the possible Orientations
 */
static constexpr std::array ORIENTATIONS{NORTH, EAST, SOUTH, WEST};

/**
 * Computes the next orientation after the rotation
 * @param start The start Orientation
 * @param clockwise true if clockwise, false if counter-clockwise
 * @return The Orientation after the rotation
 */
static constexpr Orientation next(Orientation orientation, bool clockwise) {
  switch (orientation) {
    case NORTH:
      return clockwise ? EAST : WEST;
    case EAST:
      return clockwise ? SOUTH : NORTH;
    case SOUTH:
      return clockwise ? WEST : EAST;
    case WEST:
      return clockwise ? NORTH : SOUTH;
  }
}

}  // namespace tetris::model::tetrimino

#endif  // ESI_ATLIR5_ATLC_PROJECT2_SRC_MODEL_ORIENTATION_HPP_
