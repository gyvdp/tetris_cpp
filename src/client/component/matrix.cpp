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

#include "matrix.hpp"

#include <QString>

namespace tetris::client::component {
Matrix::Matrix(QGraphicsItem *parent)
    : QGraphicsItemGroup{parent},
      bg_{new QGraphicsPixmapItem{QString{":/bg/board.png"}, this}},
      minos_{20, {10, nullptr}} {}

QRectF Matrix::boundingRect() const { return bg_->boundingRect(); }

void Matrix::set(MatrixArray matrix) {
  if (matrix.size() != 20) {
    throw std::invalid_argument("MatrixArray's height is not 20");
  }

  for (qsizetype i = 0; i < matrix.size(); ++i) {
    if (matrix[i].size() != 10) {
      throw std::invalid_argument("MatrixArray's width is not 10");
    }

    for (qsizetype j = 0; j < matrix[i].size(); ++j) {
      if (minos_[i][j] == nullptr) {
        if (matrix[i][j].has_value()) {
          auto mino = new Mino{matrix[i][j], this};
          qreal y = (mino->boundingRect().height() +
                     (mino->boundingRect().height() / 7.0)) *
                        static_cast<double>(i) +
                    PADDING;
          qreal x = (mino->boundingRect().width() +
                     (mino->boundingRect().width() / 7.0)) *
                        static_cast<double>(j) +
                    PADDING;
          mino->setPos({x, y});
          minos_[i][j] = mino;
        }
      } else {
        if (matrix[i][j].has_value()) {
          minos_[i][j]->set(matrix[i][j]);
        } else {
          delete minos_[i][j];
          minos_[i][j] = nullptr;
        }
      }
    }
  }
}
}  // namespace tetris::client::component