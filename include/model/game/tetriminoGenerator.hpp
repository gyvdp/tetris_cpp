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
#ifndef ESI_ATLIR5_ATLC_PROJECT2_SRC_MODEL_GAME_TETRIMINOGENERATOR_HPP_
#define ESI_ATLIR5_ATLC_PROJECT2_SRC_MODEL_GAME_TETRIMINOGENERATOR_HPP_

#include <ctime>
#include <model/tetrimino/mino.hpp>
#include <random>
#include <vector>

namespace tetris::mode::game {

/**
 * @brief Generates randomly shuffled bags of minos.
 */
class TetriminoGenerator {
 private:
  std::mt19937_64 gen64_;
  std::vector<tetris::model::tetrimino::Mino> minos_{};

  /**
   * @brief Generates a bag of seven randomly shuffled minos.
   * @return The shuffled bag of minos.
   */
  [[nodiscard]] std::vector<tetris::model::tetrimino::Mino> generateBag() const;

 public:
  /**
   * @brief Default constructor of generator. Seed will be the machines time.
   */
  TetriminoGenerator();

  /**
   * @brief Constructor of generator with a specific seed to be able to sync two
   * or more players.
   * @param seed Seed used to randomize generation of bags.
   */
  explicit TetriminoGenerator(unsigned long int seed);

  /**
   * @brief Retrieves the last mino from the bag. If the bag is empty it will
   * automatically be replenished.
   * @return The next upcoming mino.
   */
  tetris::model::tetrimino::Mino takeMino();
};

/******************************************************************************
 * Definitions of inline methods                                              *
 ******************************************************************************/

inline TetriminoGenerator::TetriminoGenerator(long unsigned int seed)
    : gen64_{seed}, minos_{generateBag()} {}

inline TetriminoGenerator::TetriminoGenerator()
    : TetriminoGenerator(time(nullptr)) {}

inline tetris::model::tetrimino::Mino TetriminoGenerator::takeMino() {
  if (minos_.empty()) {
    minos_ = generateBag();
  }
  auto mino = minos_.at(minos_.size() - 1);
  minos_.pop_back();
  return mino;
}
}  // namespace tetris::mode::game
#endif
