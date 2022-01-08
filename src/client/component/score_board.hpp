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

#ifndef ESI_ATLIR5_ATLC_PROJECT2_SRC_CLIENT_VIEW_COMPONENT_SCORE_BOARD_HPP_
#define ESI_ATLIR5_ATLC_PROJECT2_SRC_CLIENT_VIEW_COMPONENT_SCORE_BOARD_HPP_

#include <QGraphicsItemGroup>
#include <QGraphicsTextItem>

namespace tetris::client::component {
class ScoreBoard : public QGraphicsItemGroup {
 protected:
  static constexpr qreal PADDING = 64.0;
  QGraphicsPixmapItem *bg_;
  QGraphicsTextItem *highScore_;
  QGraphicsTextItem *highScoreValue_;
  QGraphicsTextItem *score_;
  QGraphicsTextItem *scoreValue_;

 public:
  explicit ScoreBoard(QGraphicsItem *parent = nullptr);
  void setHighScore(unsigned long score);
  void setScore(unsigned long score);
  QRectF boundingRect() const override;
};
}  // namespace tetris::client::component
#endif  // ESI_ATLIR5_ATLC_PROJECT2_SRC_CLIENT_VIEW_COMPONENT_SCORE_BOARD_HPP_
