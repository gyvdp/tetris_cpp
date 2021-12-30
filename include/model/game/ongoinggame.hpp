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

#ifndef ESI_ATLIR5_ATLC_PROJECT2_SRC_MODEL_GAME_ONGOINGGAME_HPP_
#define ESI_ATLIR5_ATLC_PROJECT2_SRC_MODEL_GAME_ONGOINGGAME_HPP_

#include <memory>
#include <optional>

#include "gamestate.hpp"
#include "model/game/matrix.hpp"
#include "model/game/player.hpp"
#include "model/tetrimino/mino.hpp"
#include "model/tetrimino/tetrimino.hpp"

namespace tetris::model::game {
/**
 * @brief This class represents an ongoing game for a particular player
 */
class OngoingGame {
 private:
  /**
   * @brief The state of the game (Not started, Falling, ...)
   */
  std::unique_ptr<GameState> state_;

  /**
   * @brief The player of the OngoingGame
   */
  Player *player_;

  Matrix matrix_;

  /**
   * @brief The falling Tetrimino
   */
  std::shared_ptr<tetrimino::Tetrimino> falling_;

  /**
   * @brief The next Mino
   */
  OptionalMino next_;

  /**
   * @brief The held Mino
   */
  OptionalMino hold_;

 public:
  /**
   * @brief The default constructor of an Ongoing Game
   *
   * @param player Pointer to the player of this game
   * @param state The initial state of the game
   */
  explicit OngoingGame(Player *player);

  /**
   * @brief This method is used to change the state of the actual game
   *
   * @param state Pointer to the new state
   */
  void state(std::unique_ptr<GameState> state);

  /**
   * @brief This method returns the username of the playing player
   *
   * @return The name of the Player
   */
  inline std::string_view name() const;

  /**
   * @brief This method returns the high-score of the player
   *
   * @return The high-score of the player
   */
  inline unsigned long highScore() const;

  /**
   * @brief Getter of the Matrix
   *
   * @return The matrix
   */
  inline Matrix matrix() const;

  /**
   * @brief Getter of the falling Tetrimino
   *
   * @return The falling Tetrimino
   */
  inline std::shared_ptr<tetrimino::Tetrimino> falling() const;

  /**
   * @brief Getter of the next Mino
   *
   * @return The next Mino (Tetrimino)
   */
  inline OptionalMino next() const;

  /**
   * @brief Getter of the held Tetrimino
   *
   * @return The held Tetrimino
   */
  inline OptionalMino hold() const;

  /**
   * @brief This method start the game
   */
  inline void start();

  /**
   * @brief This method stops the game (by quitting or error)
   */
  inline void stop();

  /**
   * @brief This method moves the falling Tetrimino in the asked direction
   *
   * @param direction
   */
  inline void move(tetrimino::Direction direction);

  /**
   * @brief This method hold the falling Tetrimino (if possible)
   */
  inline void holdFalling();

  /**
   * @brief This method soft-drops the falling Tetrimino
   */
  inline void softDrop();

  /**
   * @brief This method hard-drops the falling Tetrimino
   */
  inline void hardDrop();

  /**
   * @brief This method rotates the falling Tetrimino
   * @param clockwise true if clockwise, false if anti-clockwise
   */
  inline void rotate(bool clockwise);

  /**
   * @brief This method locks the locked-down falling Tetrimino
   */
  inline void lock();
};

/******************************************************************************
 * Definitions of inline methods                                              *
 ******************************************************************************/

std::string_view OngoingGame::name() const { return player_->name(); }

unsigned long OngoingGame::highScore() const { return player_->highScore(); }

Matrix OngoingGame::matrix() const { return matrix_; }

std::shared_ptr<tetrimino::Tetrimino> OngoingGame::falling() const {
  return falling_;
}

OptionalMino OngoingGame::next() const { return next_; }

OptionalMino OngoingGame::hold() const { return hold_; }

void OngoingGame::start() { state_->start(); }

void OngoingGame::stop() { state_->stop(); }

void OngoingGame::move(tetrimino::Direction direction) {
  state_->move(direction);
}

void OngoingGame::holdFalling() { state_->holdFalling(); }

void OngoingGame::softDrop() { state_->softDrop(); }

void OngoingGame::hardDrop() { state_->hardDrop(); }

void OngoingGame::rotate(bool clockwise) { state_->rotate(clockwise); }

void OngoingGame::lock() { state_->lock(); }

}  // namespace tetris::model::game

#endif  // ESI_ATLIR5_ATLC_PROJECT2_SRC_MODEL_GAME_ONGOINGGAME_HPP_
