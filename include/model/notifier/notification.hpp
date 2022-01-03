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

#include "QJsonDocument"
#include "QJsonObject"
#include "model/game/ongoinggame.hpp"
#include "model/notifier/action.hpp"
#include "model/tetrimino/direction.hpp"
#include "model/tetrimino/tetrimino_logic.hpp"

namespace tetris::model::notifier {
class Notification {
 public:
  /**
   * @brief Serialize a Action into a Json::Value
   * @param action Action that you serialize
   * @return Json::Value of a action
   */
  static QJsonDocument action(Action action);

  /**
   * @brief Serialize a Action into a Json::Value
   * @param action Action that you serialize
   * @param direction direction of the action
   * @return Json::Value of a action and his additional data
   */
  static QJsonDocument action(Action action, tetrimino::Direction direction);

  /**
   * @brief Serialize a Action into a Json::Value
   * @param action Action that you serialize
   * @param username username of the user
   * @return Json::Value of a action and his additional data
   */
  static QJsonDocument action(Action action, const std::string& username);

  /**
   * @brief Serialize all the data that a user need for starting his game
   * @param player information of the user
   * @param opponent information of his opponent
   * @param seed seed of the bag generator
   * @return return Json::Value of all the data
   */
  static QJsonDocument starting_game(model::game::Player& player,
                                     model::game::Player& opponent, long seed);

  /**
   * @brief Interpret the message and act on the game accordingly
   * @param message message that the client or server get from the communication
   * @param game game that message will act on
   */
  static void interpreter(QByteArray& message, model::game::OngoingGame& game);
};
}  // namespace tetris::model::notifier

#endif  // ESI_ATLIR5_ATLC_PROJECT2_INCLUDE_MESSAGES_NOTIFIER_NOTIFICATION_HPP_
