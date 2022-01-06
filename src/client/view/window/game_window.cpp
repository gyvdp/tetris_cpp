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

#include "game_window.hpp"

#include <QKeyEvent>

namespace tetris::view::window {

GameWindow::GameWindow(QWidget *parent)
    : QGraphicsView(parent), gameScene_{new scene::GameScene{this}} {
  setScene(gameScene_);
  setFrameStyle(QFrame::NoFrame);
  setAlignment(Qt::AlignLeft | Qt::AlignTop);
  setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  scale(0.4, 0.4);

  connect(this, &GameWindow::matrixChanged, gameScene_,
          &scene::GameScene::updateMatrix);
}
void GameWindow::start() {
  auto *player = new model::game::Player{"John", 123};
  onGame_ = new model::game::OngoingGame{player, 1};
  onGame_->connectBoard(
      [this](std::vector<std::vector<std::optional<model::tetrimino::Mino>>>
                 matrix) {
        // moveToThread(QApplication::instance()->thread());
        emit matrixChanged(matrix);
      });
  onGame_->start();
}
void GameWindow::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
    case Qt::Key_Left:
      onGame_->move(model::tetrimino::LEFT);
      break;
    case Qt::Key_Right:
      onGame_->move(model::tetrimino::RIGHT);
      break;
    case Qt::Key_Down:
      onGame_->softDrop();
      break;
    case Qt::Key_Space:
      onGame_->hardDrop();
      break;
    case Qt::Key_Up:
      onGame_->rotate(true);
      break;
    case Qt::Key_Control:
      onGame_->rotate(false);
      break;
  }
}

}  // namespace tetris::view::window
