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

#ifndef ESI_ATLIR5_ATLC_PROJECT2_SRC_MODEL_TETRIMINO_HPP_
#define ESI_ATLIR5_ATLC_PROJECT2_SRC_MODEL_TETRIMINO_HPP_

#include <array>
#include <map>
#include <optional>
#include <vector>

#include "model/tetrimino/direction.hpp"
#include "model/tetrimino/mino.hpp"
#include "model/tetrimino/orientation.hpp"
#include "utils/coordinate.hpp"

using OptionalMino = std::optional<tetris::model::tetrimino::Mino>;

namespace tetris::model::tetrimino {
/**
 * @brief Class that represent a Tetrimino in general
 */
class Tetrimino {
 protected:
  /**
   * @brief The actual Orientation of the Tetrimino
   */
  Orientation orientation_;

  /**
   * @brief Type of mino
   */
  Mino type_;

  /**
   * @brief The top-left Coordinate of the Tetrimino
   */
  std::optional<utils::Coordinate> coordinate_;

  /**
   * @brief The abstract representation of the Tetrimino in an 2D array of minos
   */
  std::map<Orientation, std::array<std::array<std::optional<Mino>, 4>, 4>>
      &minos_;

 public:

  /**
   * @brief Default constructor of a Tetrimino
   */
  inline explicit Tetrimino(
      std::map<Orientation, std::array<std::array<std::optional<Mino>, 4>, 4>>
          &minos,
      Mino type);

  /**
   * @brief Destructor of the Tetrimino
   */
  virtual ~Tetrimino() = default;

  /**
   * @brief Getter of the Mino 2D array representation of the Tetrimino
   * @return 2D array of Mino's
   */
  [[nodiscard]] inline std::map<
      Orientation, std::array<std::array<std::optional<Mino>, 4>, 4>>
  minos() const;

  /**
   * @brief Move a Tetrimino in a given direction
   * @param direction The direction of the move
   */
  void move(Direction direction);

  /**
   * @brief Getter for the current orientation of the mino.
   * @return Current orientation of the mino.
   */
  inline Orientation orientation();

  /**
   * @brief Move a Tetrimino if possible
   * @param direction the direction of the move
   * @param matrixMask The mask of the matrix
   */
  void move(Direction direction, std::vector<std::vector<bool>> matrixMask);

  /**
   * @brief Rotate a Tetrimino (if possible)
   * @param clockwise true if clockwise, false if anticlockwise
   * @param matrixMask The mask of the matrix
   */
  void rotate(bool clockwise, const std::vector<std::vector<bool>> &matrixMask);

  /**
   * @brief Rotate a Tetrimino
   * @param clockwise true if clockwise, false if anticlockwise
   */
  void rotate(bool clockwise);

  /**
   * @brief Gets the coordinates of the tetrimino.
   * @return Coordinates parameter of the tetrimino.
   */
  [[nodiscard]] inline utils::Coordinate getCoordinates() const;

  /**
   * Gets the X coordinate of the tetrimino.
   * @return X coordinate value.
   */
  [[nodiscard]] inline long X() const;

  /**
   * @brief Gets the Y coordinate of the tetrimino.
   * @return Y coordinate value.
   */
  [[nodiscard]] inline long Y() const;

  /**
   * @brief Gets the type of tetrimino from a mino.
   * @return The type of mino
   */
  inline Mino type();
};

/******************************************************************************
 * Definitions of inline methods                                              *
 ******************************************************************************/
Tetrimino::Tetrimino(
    std::map<Orientation, std::array<std::array<std::optional<Mino>, 4>, 4>>
        &minos,
    Mino type)
    : orientation_{NORTH}, type_{type}, coordinate_{{3, 0}}, minos_{minos} {}

std::map<Orientation, std::array<std::array<std::optional<Mino>, 4>, 4>>
Tetrimino::minos() const {
  return minos_;
}

Mino Tetrimino::type() { return type_; }

long Tetrimino::X() const { return coordinate_->x(); }

utils::Coordinate Tetrimino::getCoordinates() const {
  return coordinate_.value();
}

long Tetrimino::Y() const { return coordinate_->y(); }

Orientation Tetrimino::orientation() { return orientation_; }
}  // namespace tetris::model::tetrimino

#endif  // ESI_ATLIR5_ATLC_PROJECT2_SRC_MODEL_TETRIMINO_HPP_
