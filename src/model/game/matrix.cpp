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

#include "model/game/matrix.hpp"

#include <iostream>

#include "model/game/states/exceptions/lockedoutexception.hpp"

namespace tetris::model::game {

void Matrix::add(const std::shared_ptr<tetrimino::Tetrimino>& tetrimino) {
  auto minoTemplate = tetrimino->minos();
  for (size_t i = 0; i < minoTemplate.size(); i++) {
    for (size_t j = 0;
         j < minoTemplate.at(tetrimino->orientation()).at(i).size(); j++) {
      if (minoTemplate.at(tetrimino->orientation()).at(i).at(j) == std::nullopt)
        continue;
      size_t line = tetrimino->Y() + i;
      size_t col = tetrimino->X() + j;
      if (!(line < 0 || col < 0) && line < minos_.size() &&
          col < minos_.at(line).size()) {
        minos_.at(line).at(col) =
            minoTemplate.at(tetrimino->orientation()).at(i).at(j);
      }
    }
  }
}

void Matrix::removeLine(unsigned long i) {
  for (size_t j = 0; j < width(); j++) {
    minos_.at(i).at(j) = std::nullopt;
  }
}

void Matrix::setLine(std::vector<OptionalMino> minos, unsigned long line) {
  for (size_t col = 0; col < width(); col++)
    minos_.at(line).at(col) = minos.at(col);
}

std::vector<unsigned int> Matrix::getCompletedLines() {
  std::vector<unsigned int> completedLines;
  for (size_t i = 0; i < minos_.size(); i++) {
    bool isComplete = true;
    for (auto& j : minos_.at(i))
      if (j == std::nullopt) isComplete = false;
    if (isComplete) completedLines.push_back(i);
  }
  return completedLines;
}

void Matrix::set(tetris::model::tetrimino::Mino m, int line, int col) {
  minos_.at(line).at(col) = m;
}

std::vector<std::vector<bool>> Matrix::generateMask() const {
  std::vector<std::vector<bool>> mask{};
  mask.reserve(minos_.size());
  for (auto& line : minos_) {
    std::vector<bool> t{};
    t.reserve(line.size());
    for (auto& mino : line) {
      t.push_back(!mino.has_value());
    }
    mask.push_back(t);
  }

  return mask;
}

}  // namespace tetris::model::game
