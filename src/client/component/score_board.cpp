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

#include "score_board.hpp"

#include <QFontDatabase>
#include <QString>
#include <string>

namespace tetris::client::component {

ScoreBoard::ScoreBoard(QGraphicsItem *parent)
    : QGraphicsItemGroup(parent),
      bg_{new QGraphicsPixmapItem{QString{":/bg/score.png"}, this}},
      highScore_{new QGraphicsTextItem{QString{"TOP"}, this}},
      highScoreValue_{new QGraphicsTextItem{QString{"00000"}, this}},
      score_{new QGraphicsTextItem{QString{"SCORE"}, this}},
      scoreValue_{new QGraphicsTextItem{QString{"00000"}, this}} {
  qreal ratio = 64.0 / 7.0;

  for (auto &text : {highScore_, highScoreValue_, score_, scoreValue_}) {
    text->setFont({QFontDatabase::applicationFontFamilies(0).at(0),
                   static_cast<int>(7.0 * ratio)});
    text->setDefaultTextColor(QColor{255, 255, 255});
  }

  qreal x_text = 8.0 * ratio;

  highScore_->setPos({x_text, 16.0 * ratio});
  highScoreValue_->setPos({x_text, 24.0 * ratio});
  score_->setPos({x_text, 40.0 * ratio});
  scoreValue_->setPos({x_text, 48.0 * ratio});
}

QRectF ScoreBoard::boundingRect() const { return bg_->boundingRect(); }

void ScoreBoard::setHighScore(unsigned long score) {
  highScoreValue_->setPlainText(QString::fromStdString(std::to_string(score)));
}

void ScoreBoard::setScore(unsigned long score) {
  scoreValue_->setPlainText(QString::fromStdString(std::to_string(score)));
}

}  // namespace tetris::client::component