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

//
// Created by Thoma on 30-12-21.
//

#ifndef ESI_ATLIR5_ATLC_PROJECT2_INCLUDE_MESSAGES_NOTIFIER_NOTIFICATION_HPP_
#define ESI_ATLIR5_ATLC_PROJECT2_INCLUDE_MESSAGES_NOTIFIER_NOTIFICATION_HPP_

#include <QByteArray>

#include "json/json.h"
#include "model/game/ongoinggame.hpp"
#include "model/tetrimino/tetrimino_logic.hpp"

namespace tetris::model::notifier {
class Notification {
 public:
  static Json::Value hold(model::tetrimino::Mino);
  static Json::Value next(model::tetrimino::Mino);
  static Json::Value actual(const model::tetrimino::Tetrimino&);
  static Json::Value connection(const std::string&);
  static Json::Value starting_game(model::game::Player& player,
                                   model::game::Player& opponent, long seed);
  static Json::Value board(model::game::Matrix&);
  static void interpreter(QByteArray&, model::game::OngoingGame&);
};
}  // namespace tetris::model::notifier

#endif  // ESI_ATLIR5_ATLC_PROJECT2_INCLUDE_MESSAGES_NOTIFIER_NOTIFICATION_HPP_
