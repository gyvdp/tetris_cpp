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

#include "tetri_holder.hpp"

#include <QFontDatabase>

namespace tetris::client::component {

TetriHolder::TetriHolder(QString type, QGraphicsItem *parent)
    : QGraphicsItemGroup(parent),
      bg_{new QGraphicsPixmapItem{QString{":/bg/tetriminoholder.png"}, this}},
      title_{new QGraphicsTextItem{type, this}},
      tetrimino_{nullptr} {
  qreal ratio = 64.0 / 7.0;

  title_->setFont({QFontDatabase::applicationFontFamilies(0).at(0),
                   static_cast<int>(7.0 * ratio)});
  title_->setPos({7 * ratio, 7 * ratio});
}

QRectF TetriHolder::boundingRect() const { return bg_->boundingRect(); }

QPixmap TetriHolder::resource(model::tetrimino::Mino type) {
  switch (type) {
    case tetris::model::tetrimino::Mino::T_MINO:
      return QPixmap{":/tetrimino/T0.png"};
    case tetris::model::tetrimino::Mino::O_MINO:
      return QPixmap{":/tetrimino/O0.png"};
    case tetris::model::tetrimino::Mino::I_MINO:
      return QPixmap{":/tetrimino/I0.png"};
    case tetris::model::tetrimino::Mino::L_MINO:
      return QPixmap{":/tetrimino/L0.png"};
    case tetris::model::tetrimino::Mino::Z_MINO:
      return QPixmap{":/tetrimino/Z0.png"};
    case tetris::model::tetrimino::Mino::J_MINO:
      return QPixmap{":/tetrimino/J0.png"};
    case tetris::model::tetrimino::Mino::S_MINO:
    default:
      return QPixmap{":/tetrimino/S0.png"};
  }
}

}  // namespace tetris::client::component