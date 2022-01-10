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

#ifndef ESI_ATLIR5_ATLC_PROJECT2_SRC_MODEL_MATRIX_HPP_
#define ESI_ATLIR5_ATLC_PROJECT2_SRC_MODEL_MATRIX_HPP_

#include <array>
#include <memory>
#include <optional>
#include <stdexcept>
#include <vector>

#include "model/tetrimino/mino.hpp"
#include "model/tetrimino/tetrimino.hpp"
#include "utils/coordinate.hpp"

using OptionalMino = std::optional<tetris::model::tetrimino::Mino>;

namespace tetris::model::game {
/**
 * @brief The matrix class handles all the operations that can be done on the
 * tetris matrix (add a locked tetrimino, get/remove full lines)
 */
class Matrix {
 private:
  /**
   * @brief width of the actual matrix
   */
  const size_t width_;

  /**
   * @brief height of the actual matrix
   */
  const size_t height_;

  /**
   * @brief representation of the Tetrimino in form of a 2D-array of Mino's
   */
  std::vector<std::vector<OptionalMino>> minos_;

 public:
  /**
   * @brief Generates a mask of booleans were all occupied spaces (mino or oob)
   * are true.
   * @return MAsk of booleans.
   */
  [[nodiscard]] std::vector<std::vector<bool>> generateMask() const;

  /**
   * @brief Basic constructor of a Matrix
   *
   * @param width the width of the matrix
   * @param height the height of the matrix
   */
  inline Matrix(size_t width, size_t height);

  inline std::vector<std::vector<OptionalMino>> getMinos();

  /**
   * @brief Getter of the width_ property
   * @return The width of the matrix
   */
  [[nodiscard]] inline size_t width() const;

  /**
   * @brief Getter of the height_ property
   * @return The height of the matrix
   */
  [[nodiscard]] inline size_t height() const;

  /**
   * @brief Get the Mino at the given position
   * @param position Coordinate of the mino to get
   * @return The asked mino if exists (std::optional)
   */
  [[nodiscard]] inline OptionalMino get(utils::Coordinate position) const;

  /**
   * @brief Add a Tetrimino to the Matrix (when locked down for example)
   * @param tetrimino The Tetrimino to place in the Matrix
   */
  void add(const std::shared_ptr<tetrimino::Tetrimino>& tetrimino);

  /**
   * @brief Gets all lines that are completed. Meaning that there is a mino in
   * every case of the row.
   * @return Vector of all rows that are completed.
   */
  std::vector<unsigned int> getCompletedLines();

  /**
   * @brief Gets a specific case in the matrix.
   * @param x Index of x axis.
   * @param y Index of y axis.
   * @return Value at given index.
   */
  inline OptionalMino operator()(utils::Coordinate position) const;

  void removeLine(unsigned long i);

  void setLine(std::vector<OptionalMino> minos, unsigned long line);

  /**
   * @brief Sets a mino at a specific location.
   * @param m Mino to set at location.
   * @param line Line coordinates.
   * @param col Column coordinates.
   */
  void set(tetris::model::tetrimino::Mino m, int line, int col);
};

/******************************************************************************
 * Definitions of inline methods                                              *
 ******************************************************************************/

Matrix::Matrix(size_t width, size_t height)
    : width_{width},
      height_{height},
      minos_{height, std::vector<OptionalMino>{width, std::nullopt}} {
  if (width > 100 || height > 100) {
    throw std::logic_error("coucou");
  }
}

size_t Matrix::width() const { return width_; }

size_t Matrix::height() const { return height_; }

OptionalMino Matrix::get(utils::Coordinate position) const {
  return minos_.at(position.y()).at(position.x());
}

OptionalMino Matrix::operator()(utils::Coordinate position) const {
  return get(position);
}

std::vector<std::vector<OptionalMino>> Matrix::getMinos() { return minos_; }

}  // namespace tetris::model::game

#endif  // ESI_ATLIR5_ATLC_PROJECT2_SRC_MODEL_MATRIX_HPP_
