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

#include <chrono>
#include <ctime>
#include <model/tetrimino/mino.hpp>
#include <random>
#include <vector>

namespace tetris::model::game {

/**
 * @brief Generates randomly shuffled bags of minos.
 */
class TetriminoGenerator {
 private:
  /**
   * @brief Mersenne Twister Engine
   */
  std::mt19937_64 gen64_;

  /**
   * @brief Bag of Minos
   */
  std::vector<tetrimino::Mino> minos_{};

  /**
   * @brief Generates a bag of seven randomly shuffled minos.
   * @return The shuffled bag of minos.
   */
  [[nodiscard]] std::vector<tetrimino::Mino> generateBag();

 public:
  /**
   * @brief Default constructor of generator. Seed will be the machines time.
   */
  explicit TetriminoGenerator();

  /**
   * @brief Constructor of generator with a specific seed to be able to sync two
   * or more players.
   * @param seed Seed used to randomize generation of bags.
   */
  explicit TetriminoGenerator(std::uint_fast64_t seed);

  /**
   * @brief Retrieves the last mino from the bag. If the bag is empty it will
   * automatically be replenished.
   * @return The next upcoming mino.
   */
  tetrimino::Mino takeMino();
};

/******************************************************************************
 * Definitions of inline methods                                              *
 ******************************************************************************/

inline TetriminoGenerator::TetriminoGenerator(std::uint_fast64_t seed)
    : gen64_{seed} {
  minos_ = generateBag();
}

inline TetriminoGenerator::TetriminoGenerator()
    : TetriminoGenerator{static_cast<std::uint_fast64_t>(
          std::chrono::system_clock::now().time_since_epoch().count())} {}

}  // namespace tetris::model::game
#endif
