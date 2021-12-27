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

#ifndef ESI_ATLIR5_ATLC_PROJECT2_SRC_MODEL_COORDINATE_HPP_
#define ESI_ATLIR5_ATLC_PROJECT2_SRC_MODEL_COORDINATE_HPP_

namespace tetris::utils {
/**
 * @brief Representation of a 2D Coordinate
 */
class Coordinate {
 private:
  /**
   * @brief x coordinate
   */
  const long x_;

  /**
   * @brief y coordinate
   */
  const long y_;

 public:
  /**
   * @brief Constructor with a x and a y
   * @param x the x coordinate
   * @param y the y coordinate
   */
  constexpr Coordinate(long x, long y);

  /**
   * @brief Constructor to create an origin Coordinate (0,0)
   */
  constexpr Coordinate();

  /**
   * @brief Getter of the x_ property
   * @return The x coordinate
   */
  [[nodiscard]] constexpr long x() const;

  /**
   * @brief Getter of the y_ property
   * @return The y coordinate
   */
  [[nodiscard]] constexpr long y() const;

  /**
   * @brief Sum operator of two Coordinate's
   * @param rhs The Coordinate to add to the current one
   * @return A new Coordinate with the sum of each property
   */
  constexpr Coordinate operator+(Coordinate rhs) const;
};

/******************************************************************************
 * Definitions of constexpr methods                                           *
 ******************************************************************************/

constexpr Coordinate::Coordinate(long x, long y) : x_{x}, y_{y} {}

constexpr Coordinate::Coordinate() : Coordinate{0, 0} {}

constexpr long Coordinate::x() const { return x_; }

constexpr long Coordinate::y() const { return y_; }

constexpr Coordinate Coordinate::operator+(Coordinate rhs) const {
  return {x_ + rhs.x_, y_ + rhs.y_};
}

}  // namespace tetris::utils

#endif  // ESI_ATLIR5_ATLC_PROJECT2_SRC_MODEL_COORDINATE_HPP_
