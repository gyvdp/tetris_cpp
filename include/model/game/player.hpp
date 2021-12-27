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

#ifndef ESI_ATLIR5_ATLC_PROJECT2_SRC_MODEL_GAME_PLAYER_HPP_
#define ESI_ATLIR5_ATLC_PROJECT2_SRC_MODEL_GAME_PLAYER_HPP_

#include <string>
#include <utility>

namespace tetris::model::game {
/**
 * @brief The Player class handles all the attributes of a Player (name,
 * high-score)
 */
class Player {
 private:
  /**
   * @brief The name of the Player
   */
  const std::string name_;

  /**
   * @brief The high-score of the Player
   */
  unsigned long highScore_;

 public:
  /**
   * @brief Constructor of a Player
   *
   * @param name The name of the player
   * @param highScore High-score of the player (optional)
   */
  inline explicit Player(std::string name, unsigned long highScore = 0);

  /**
   * @brief Getter of the name_ property
   *
   * @return The name of the Player
   */
  [[nodiscard]] inline std::string_view name() const;

  /**
   * @brief Getter of the highScore_ property
   *
   * @return The high-score of the Player
   */
  [[nodiscard]] inline unsigned long highScore() const;

  /**
   * @brief Setter of the highScore_ property
   *
   * @param score The new high-score of the Player
   */
  inline void highScore(unsigned long score);
};

/******************************************************************************
 * Definitions of inline methods                                              *
 ******************************************************************************/

Player::Player(std::string name, unsigned long highScore)
    : name_{std::move(name)}, highScore_{highScore} {}

std::string_view Player::name() const { return name_; }

unsigned long Player::highScore() const { return highScore_; }

void Player::highScore(unsigned long score) { highScore_ = score; }

}  // namespace tetris::model::game

#endif  // ESI_ATLIR5_ATLC_PROJECT2_SRC_MODEL_GAME_PLAYER_HPP_
