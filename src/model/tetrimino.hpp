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
#include <memory>

#include "model/mino.hpp"

namespace tetris::model::tetrimino {
enum Orientation { NORTH = 0, EAST, SOUTH, WEST };
class Tetrimino {
 protected:
  /**
   * @brief x coordinate of the tetrimino on the board
   */
  int x_;
  /**
   * @brief y coordinate of the tetrimino on the board
   */
  int y_;

  /**
   * @brief minos_ matrix that composed
   */
  std::array<std::array<Mino, 4>, 4> minos_;
  Orientation orientation_;
  Mino type_;

  /**
   * @brief Initiates default values of all Tetrimino
   */
  Tetrimino() : y_(0), x_(3), orientation_(NORTH) {}

  virtual std::array<std::array<Mino, 4>, 4> rotatedShape(bool clockwise) = 0;

 public:
  /**
   * @brief Create a tetrimino from a mino
   *
   * @param mino Mino to create into tetrimino
   * @return New tetrimino created from mino
   */
  static std::unique_ptr<tetris::model::tetrimino::Tetrimino> createTetrimino(
      Mino mino);

  /**
   * @brief Rotate the Tetrimino
   *
   * @param clockwise       true if clockwise
   * @param surroundingArea Area of surrounding blocks.
   * @throws IllegalArgumentException if non valid parameters.
   */
  //  bool rotate(bool clockwise, bool[][] freeMask);

  /**
   * @brief Moves the tetrimino in a direction
   *
   * @param direction Direction to move tetrimino in.
   */
  //  bool move(Direction direction, boolean[][] freeMask);

  /**
   * @brief Get the x position
   *
   * @return the x position
   */
  inline int getX() const { return x_; }

  /**
   * @brief Get the y position
   *
   * @return the y position
   */
  inline int getY() const { return y_; }

  /**
   * @brief Get the minos_ wich the matrix is made of
   *
   * @return the mino contains in the matrix of minos_
   */
  inline Mino getType() const { return type_; }

  /**
   * @brief Get a matrix of the minos_ in the tetrimino
   *
   * @return the tetrimino as minos_ matrix
   */
  inline const std::array<std::array<Mino, 4>, 4> getMinos() const {
    return this->minos_;
  }

  std::string toString();
};
}  // namespace tetris::model::tetrimino

#endif  // ESI_ATLIR5_ATLC_PROJECT2_SRC_MODEL_TETRIMINO_HPP_
