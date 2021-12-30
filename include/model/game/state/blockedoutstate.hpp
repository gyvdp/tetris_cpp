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

#ifndef ESI_ATLIR5_ATLC_PROJECT2_INCLUDE_MODEL_GAME_STATE_BLOCKEDOUTSTATE_HPP_
#define ESI_ATLIR5_ATLC_PROJECT2_INCLUDE_MODEL_GAME_STATE_BLOCKEDOUTSTATE_HPP_

#include "model/game/gamestate.hpp"
#include "model/game/ongoinggame.hpp"

namespace tetris::model::game::states {
/**
 * @brief This class represents the state when the nextTetrimino have no place
 * to spawn
 */
class BlockedOutState : public GameState {
 public:
  /**
   * @brief Default constructor
   *
   * @param game The game that have this state
   */
  inline explicit BlockedOutState(OngoingGame *game);

  /**
   * @inherit
   */
  void start() override;

  /**
   * @inherit
   */
  void stop() override;

  /**
   * @inherit
   */
  void move(tetrimino::Direction direction) override;

  /**
   * @inherit
   */
  void holdFalling() override;

  /**
   * @inherit
   */
  void softDrop() override;

  /**
   * @inherit
   */
  void hardDrop() override;

  /**
   * @inherit
   */
  void rotate(bool clockwise) override;

  /**
   * @inherit
   */
  void lock() override;
};

/******************************************************************************
 * Definitions of inline methods                                              *
 ******************************************************************************/
BlockedOutState::BlockedOutState(OngoingGame *game) : GameState{game} {}
}  // namespace tetris::model::game::states

#endif  // ESI_ATLIR5_ATLC_PROJECT2_INCLUDE_MODEL_GAME_STATE_BLOCKEDOUTSTATE_HPP_
