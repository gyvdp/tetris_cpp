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

#ifndef ESI_ATLIR5_ATLC_PROJECT2_SRC_CLIENT_VIEW_COMPONENT_GAME_HPP_
#define ESI_ATLIR5_ATLC_PROJECT2_SRC_CLIENT_VIEW_COMPONENT_GAME_HPP_

#include <QGraphicsItemGroup>

#include "client/component/matrix.hpp"
#include "client/component/score_board.hpp"
#include "client/component/tetri_holder.hpp"
#include "model/tetrimino/mino.hpp"

namespace tetris::client::component {
class Game : public QGraphicsItemGroup {
 protected:
  /**
   * @brief The matrix of the game
   */
  component::Matrix *matrix_;
  component::ScoreBoard *scoreBoard_;
  component::TetriHolder *next_;
  component::TetriHolder *hold_;

 public:
  explicit Game(QGraphicsItem *parent = nullptr);

  inline void updateMatrix(MatrixArray array);

  inline void updateNext(model::tetrimino::Mino mino);

  inline void updateHold(model::tetrimino::Mino mino);

  inline void setHighScore(unsigned long score);

  inline void setScore(unsigned long score);

  [[nodiscard]] QRectF boundingRect() const override;
};

void Game::updateMatrix(MatrixArray array) { matrix_->set(std::move(array)); }

void Game::updateNext(model::tetrimino::Mino mino) { next_->set(mino); }

void Game::updateHold(model::tetrimino::Mino mino) { hold_->set(mino); }

void Game::setHighScore(unsigned long score) {
  scoreBoard_->setHighScore(score);
}

void Game::setScore(unsigned long score) { scoreBoard_->setScore(score); }

}  // namespace tetris::client::component
#endif  // ESI_ATLIR5_ATLC_PROJECT2_SRC_CLIENT_VIEW_COMPONENT_GAME_HPP_
