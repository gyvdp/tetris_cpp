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

#ifndef ESI_ATLIR5_ATLC_PROJECT2_SRC_MODEL_GAME_ONGOINGGAME_HPP_
#define ESI_ATLIR5_ATLC_PROJECT2_SRC_MODEL_GAME_ONGOINGGAME_HPP_

#include <QObject>
#include <QTimer>
#include <memory>
#include <optional>
#include <utility>

#include "gamestate.hpp"
#include "model/game/matrix.hpp"
#include "model/game/player.hpp"
#include "model/game/tetriminoGenerator.hpp"
#include "model/tetrimino/mino.hpp"
#include "model/tetrimino/tetrimino.hpp"
#include "utils/coordinate.hpp"

namespace tetris::model::game {

using MatrixArray = std::vector<std::vector<OptionalMino>>;

/**
 * @brief This class represents an ongoing game for a particular player
 */
class OngoingGame : public QObject {
  Q_OBJECT
 private:
  /**
   * @brief The state of the game (Not started, Falling, ...)
   */
  GameState* state_;

  /**
   * @brief The player of the OngoingGame
   */
  Player* player_;

  /**
   * @brief The matrix of the game with all placed minos
   */
  Matrix matrix_;

  /**
   * @brief If player has held or not.
   */
  bool hasHeld_ = false;

  /**
   * @brief The Tetrimino bag generator
   */
  TetriminoGenerator generator_;

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

  /**
   * @brief Score of the game.
   */
  unsigned score_;

  /**
   * @brief Level of the game.
   */
  unsigned level_;

  /**
   * @brief True if the player is managed
   */
  bool managed_;

  /**
   * @brief Number of lines deleted in the game.
   */
  unsigned lines_;

  /**
   * @brief Timer of the game.
   */
  QTimer* timer_;

 public:
  /**
   * @brief The default constructor of an Ongoing Game
   *
   * @param player Pointer to the player of this game
   * @param state The initial state of the game
   */
  explicit OngoingGame(Player* player, std::uint_fast64_t seed,
                       bool managed = true);

  /**
   * @brief Getter for the level.
   * @return The level of the current game.
   */
  [[nodiscard]] inline unsigned level() const;

  /**
   * @brief This method is used to change the state of the actual game
   *
   * @param state Pointer to the new state
   */
  void state(GameState* state);

  /**
   * @brief This method returns the username of the playing player
   *
   * @return The name of the Player
   */
  [[nodiscard]] inline std::string_view name() const;

  /**
   * @brief This method returns the high-score of the player
   *
   * @return The high-score of the player
   */
  [[nodiscard]] inline unsigned long highScore() const;

  /**
   * @brief Getter of the Matrix
   *
   * @return The matrix
   */
  [[nodiscard]] inline Matrix matrix() const;

  /**
   * @brief Getter for is managed.
   * @return True if it's a managed player.
   */
  [[nodiscard]] inline bool isManaged() const;

  /**
   * @brief Setter for the score.
   * @param score Score to set.
   */
  inline void score(unsigned score);

  /**
   * @brief Getter for the score.
   * @return Score of the current game.
   */
  [[nodiscard]] inline unsigned score() const;

  /**
   * @brief Getter of the falling Tetrimino
   *
   * @return The falling Tetrimino
   */
  [[nodiscard]] inline std::shared_ptr<tetrimino::Tetrimino> falling() const;

  std::vector<std::vector<OptionalMino>> fallingInsideMatrix();

  /**
   * @brief Setter for the falling tetrimino.
   * @param tetrimino Tetrimino to set as the falling one.
   */
  inline void falling(std::shared_ptr<tetrimino::Tetrimino> tetrimino);

  /**
   * @brief Getter of the next Mino
   *
   * @return The next Mino (Tetrimino)
   */
  [[nodiscard]] inline OptionalMino next() const;

  /**
   * @brief Check if player has held.
   * @return True if the player has already held.
   */
  [[nodiscard]] inline bool hasHeld() const;

  /**
   * Sets if the player has held or not.
   * @param held True if the player has held.
   */
  inline void hasHeld(bool held);

  /**
   * Setter for the next tetrimino.
   * @param mino Mino to set as next
   */
  inline void next(tetrimino::Mino mino);

  /**
   * @brief Getter of the held Tetrimino
   *
   * @return The held Tetrimino
   */
  [[nodiscard]] inline OptionalMino hold() const;

  /**
   * @brief Setter for the hold mino.
   * @param mino Mino to set as hold.
   */
  inline void hold(tetrimino::Mino mino);

  /**
   * @brief Picks a mino from the bag generator.
   * @return Mino picked from the bag generator.
   */
  inline tetrimino::Mino pickMino();

  /**
   * @brief This method start the game
   */
  inline void start();
  /**
   * Calculate the number of G to place on the tetrimino.
   * @return Number of G's tetrimino should feel.
   */
  [[nodiscard]] int calculateGravity() const;

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
  void lock();

  /**
   * @brief Clears all the completed lines from the matrix.
   */
  void clearLines();

  /**
   * @brief Generates points for number of lines destroyed.
   * @param lines Number of lines that have been destroyed.
   */
  void generatePoints(size_t lines);

  /**
   * Stops and resets the locking timer.
   */
  void refreshFallingTimer();

  /**
   * @brief Stops and resets the timer.
   */
  void refreshLockingTimer();

  /**
   * @brief Moves the falling piece in.
   * @param direction Direction to move the piece in.
   */
  void moveFalling(tetrimino::Direction direction);

  /**
   * @brief Rotates the falling piece
   * @param clockwise
   */
  void rotateFalling(bool clockwise);

  /**
   * @brief Getter of the matrix by reference.
   * @return The reference of the matrix.
   */
  Matrix& getMatrix();

 signals:

  void matrixUpdate(MatrixArray array);

  void scoreUpdate(unsigned score);

  void rotateUpdate(bool clockwise);

  void nextUpdate(tetrimino::Mino m);

  void holdUpdate(tetrimino::Mino m);

  void moveUpdate(tetrimino::Direction direction);

  void linesUpdate(std::vector<unsigned int> completedLines);

  void hardDropUpdate();

  void lockUpdate();
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

unsigned OngoingGame::score() const { return score_; }

void OngoingGame::falling(std::shared_ptr<tetrimino::Tetrimino> tetrimino) {
  falling_ = std::move(tetrimino);
}

void OngoingGame::score(unsigned score) {
  score_ += score;
  emit scoreUpdate(score_);
}

unsigned OngoingGame::level() const { return level_; }

OptionalMino OngoingGame::next() const { return next_; }

void OngoingGame::next(tetrimino::Mino mino) {
  next_ = mino;
  emit nextUpdate(next_.value());
}

OptionalMino OngoingGame::hold() const { return hold_; }

void OngoingGame::hold(tetrimino::Mino mino) {
  hold_ = mino;
  emit holdUpdate(hold_.value());
}

void OngoingGame::start() {
  try {
    state_->start();
  } catch (std::logic_error& ignored) {
  }
}

void OngoingGame::stop() {
  try {
    state_->stop();
  } catch (std::logic_error& ignored) {
  }
}

void OngoingGame::move(tetrimino::Direction direction) {
  try {
    state_->move(direction);
  } catch (std::logic_error& ignored) {
  }
}
void OngoingGame::holdFalling() {
  try {
    state_->holdFalling();
  } catch (std::logic_error& ignored) {
  }
}

void OngoingGame::softDrop() {
  try {
    state_->softDrop();
  } catch (std::logic_error& ignored) {
  }
}

void OngoingGame::hardDrop() {
  try {
    state_->hardDrop();
    emit hardDropUpdate();
  } catch (std::logic_error& ignored) {
  }
}
void OngoingGame::rotate(bool clockwise) {
  try {
    state_->rotate(clockwise);
  } catch (std::logic_error& ignored) {
  }
}

void OngoingGame::hasHeld(bool held) { hasHeld_ = held; }

bool OngoingGame::hasHeld() const { return hasHeld_; }

bool OngoingGame::isManaged() const { return managed_; }

tetrimino::Mino OngoingGame::pickMino() { return generator_.takeMino(); }

}  // namespace tetris::model::game

#endif  // ESI_ATLIR5_ATLC_PROJECT2_SRC_MODEL_GAME_ONGOINGGAME_HPP_
