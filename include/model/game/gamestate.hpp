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

#ifndef ESI_ATLIR5_ATLC_PROJECT2_INCLUDE_MODEL_GAME_GAMESTATE_HPP_
#define ESI_ATLIR5_ATLC_PROJECT2_INCLUDE_MODEL_GAME_GAMESTATE_HPP_

namespace tetris::model::game {

class OngoingGame;

/**
 * @brief Abstraction of a State in a Ongoing Game
 */
class GameState {
 protected:
  /**
   * @brief Pointer to the Ongoing Game
   */
  OngoingGame *game_;

 public:
  inline explicit GameState(OngoingGame *game);

  /**
   * @brief Default destructor
   */
  virtual ~GameState() = default;

  /**
   * @brief This method is used to start a game
   */
  virtual void start() = 0;
};

/******************************************************************************
 * Definitions of inline methods                                              *
 ******************************************************************************/
GameState::GameState(OngoingGame *game) : game_{game} {}

}  // namespace tetris::model::game

#endif  // ESI_ATLIR5_ATLC_PROJECT2_INCLUDE_MODEL_GAME_GAMESTATE_HPP_