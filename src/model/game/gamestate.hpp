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

#ifndef ESI_ATLIR5_ATLC_PROJECT2_INCLUDE_MODEL_GAME_GAMESTATE_HPP_
#define ESI_ATLIR5_ATLC_PROJECT2_INCLUDE_MODEL_GAME_GAMESTATE_HPP_

#include "model/game/states.hpp"
#include "model/tetrimino/direction.hpp"
namespace tetris::model::game {

class OngoingGame;

/**
 * @brief Abstraction of a state in a Ongoing Game
 */
class GameState {
 protected:
  StateType type_;

  /**
   * @brief Pointer to the Ongoing Game
   */
  OngoingGame *game_;

 public:
  inline explicit GameState(StateType type, OngoingGame *game);

  /**
   * @brief Default destructor
   */
  virtual ~GameState() = default;

  inline StateType type() const;

  /**
   * @brief This method is used to start a game
   */
  virtual void start() = 0;

  /**
   * @brief This method stops the game (by quitting or error)
   */
  virtual void stop() = 0;

  /**
   * @brief This method moves the falling Tetrimino in the asked direction
   *
   * @param direction
   */
  virtual void move(tetrimino::Direction direction) = 0;

  /**
   * @brief This method hold the falling Tetrimino (if possible)
   */
  virtual void holdFalling() = 0;

  /**
   * @brief This method soft-drops the falling Tetrimino
   */
  virtual void softDrop() = 0;

  /**
   * @brief This method hard-drops the falling Tetrimino
   */
  virtual void hardDrop() = 0;

  /**
   * @brief This method rotates the falling Tetrimino
   * @param clockwise true if clockwise, false if anti-clockwise
   */
  virtual void rotate(bool clockwise) = 0;

  /**
   * @brief This method locks the locked-down falling Tetrimino
   */
  virtual void lock() = 0;
};

/******************************************************************************
 * Definitions of inline methods                                              *
 ******************************************************************************/
GameState::GameState(StateType type, OngoingGame *game)
    : type_{type}, game_{game} {}

StateType GameState::type() const { return type_; }

}  // namespace tetris::model::game

#endif  // ESI_ATLIR5_ATLC_PROJECT2_INCLUDE_MODEL_GAME_GAMESTATE_HPP_
