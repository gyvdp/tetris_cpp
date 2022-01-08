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

#ifndef ESI_ATLIR5_ATLC_PROJECT2_SRC_CLIENT_VIEW_COMPONENT_TETRI_HOLDER_HPP_
#define ESI_ATLIR5_ATLC_PROJECT2_SRC_CLIENT_VIEW_COMPONENT_TETRI_HOLDER_HPP_

#include <QGraphicsItemGroup>
#include <QPixmap>
#include <optional>

#include "model/tetrimino/mino.hpp"

namespace tetris::client::component {

class TetriHolder : public QGraphicsItemGroup {
 protected:
  static constexpr qreal PADDING = 64.0;
  QGraphicsPixmapItem *bg_;
  QGraphicsTextItem *title_;
  QGraphicsPixmapItem *tetrimino_;

 public:
  explicit TetriHolder(QString type, QGraphicsItem *parent = nullptr);
  QPixmap resource(model::tetrimino::Mino type);
  inline void set(model::tetrimino::Mino type);
  QRectF boundingRect() const override;
};

void TetriHolder::set(model::tetrimino::Mino type) {
  qreal ratio = 64.0 / 7.0;
  if (tetrimino_ == nullptr) {
    tetrimino_ = new QGraphicsPixmapItem{resource(type), this};
    tetrimino_->setPos({7 * ratio, title_->y() + (7 * ratio)});
  }
}

}  // namespace tetris::client::component
#endif  // ESI_ATLIR5_ATLC_PROJECT2_SRC_CLIENT_VIEW_COMPONENT_TETRI_HOLDER_HPP_
