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

//
// Created by Thoma on 30-12-21.
//

#ifndef ESI_ATLIR5_ATLC_PROJECT2_INCLUDE_MESSAGES_NOTIFIER_NOTIFICATION_HPP_
#define ESI_ATLIR5_ATLC_PROJECT2_INCLUDE_MESSAGES_NOTIFIER_NOTIFICATION_HPP_

#include <QByteArray>

#include "QJsonDocument"
#include "QJsonObject"
#include "model/game/ongoinggame.hpp"
#include "model/notification/action.hpp"
#include "model/tetrimino/direction.hpp"
#include "model/tetrimino/tetrimino_logic.hpp"

namespace tetris::model::notification {
class Notification {
 public:
  /**
   * @brief Serialize a Action into a QJsonDocument
   * @param action Action that you serialize
   * @return QJsonDocument of a action
   */
  static QJsonDocument action(Action action);

  /**
   * @brief Serialize a Action into a QJsonDocument
   * @param action Action that you serialize
   * @param direction direction of the action
   * @return QJsonDocument of a action and his additional data
   */
  static QJsonDocument action(Action action, tetrimino::Direction direction);

  /**
   * @brief Serialize a Action into a QJsonDocument
   * @param action Action that you serialize
   * @param username username of the user
   * @return QJsonDocument of a action and his additional data
   */
  static QJsonDocument action(Action action, const std::string& username);

  /**
   * @brief Serialize a Action into a QJsonDocument
   * @param action Action that you serialize
   * @param clockwise if the rotate will be clockwise or not
   * @return QJsonDocument of a action and his additional data
   */
  static QJsonDocument action(Action action, bool clockwise);


  /**
   * @brief Serialize a Action into a QJsonDocument
   * @param action Action that you serialize
   * @param score of the player when he lost or disconnects.
   * @return QJsonDocument of a action and his additional data
   */
  static QJsonDocument action(Action action, int score);


  /**
   * @brief Serialize all the data that a user need for starting his game
   * @param player_name name of the player
   * @param player_score best score of the player
   * @param opponent_name information of his opponent
   * @param opponent_score best score of the opponent
   * @param seed seed of the bag generator
   * @return return QJsonDocument of all the data
   */
  static QJsonDocument starting_game(const std::string& player_name,
                                     int player_score,
                                     const std::string& opponent_name,
                                     int opponent_score, uint_fast64_t seed);

  /**
   * @brief Interpret the message and act on the game accordingly
   * @param message message that the client or server get from the communication
   * @param game game that message will act on
   */
  static void deserialize(QByteArray& message,
                          model::game::OngoingGame& playerGame,
                          model::game::OngoingGame& opponentGame);
};
}  // namespace tetris::model::notification

#endif  // ESI_ATLIR5_ATLC_PROJECT2_INCLUDE_MESSAGES_NOTIFIER_NOTIFICATION_HPP_
