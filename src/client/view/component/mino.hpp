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

#ifndef ESI_ATLIR5_ATLC_PROJECT2_SRC_CLIENT_VIEW_MINO_HPP_
#define ESI_ATLIR5_ATLC_PROJECT2_SRC_CLIENT_VIEW_MINO_HPP_
#include <QGraphicsPixmapItem>
#include <optional>

#include "model/tetrimino/mino.hpp"

using OptionalMino = std::optional<tetris::model::tetrimino::Mino>;

namespace tetris::view::component {
/**
 * @brief This class represent a QGraphicsPixmapItem of a Mino
 */
class Mino : public QGraphicsPixmapItem {
 protected:
  /**
   * @brief The type of the actual mino shown
   */
  OptionalMino type_;

 public:
  /**
   * @brief Default constructor of a Mino
   *
   * @param type Type of the Mino (optional)
   * @param parent Parent QGraphicsItem (for memory)
   */
  explicit Mino(OptionalMino type, QGraphicsItem *parent = nullptr);

  /**
   * @brief Generates a QString of the URI of the resource in function of the
   * asked Mino
   *
   * @param type Type of the Mino (optional)
   * @return THe URI of the Mino image
   */
  static QString resource(OptionalMino type);

  /**
   * @brief Set the Mino to a new type. If the type is the same, does nothing
   *
   * @param type Type of the new Mino (optional)
   */
  inline void set(OptionalMino type);
};

void Mino::set(OptionalMino type) {
  if (type != type_) setPixmap({resource(type)});
}
}  // namespace tetris::view::component
#endif  // ESI_ATLIR5_ATLC_PROJECT2_SRC_CLIENT_VIEW_MINO_HPP_
