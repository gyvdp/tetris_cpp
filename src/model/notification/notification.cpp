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

#include "model/notification/notification.hpp"

namespace tetris::model::notification {

QJsonDocument Notification::action(Action action, const QString& username) {
  if (action != CONNECTION) throw std::invalid_argument("Wrong action");
  QJsonObject object;
  QJsonObject data;
  QJsonObject player;
  object["key"] = "ACTION";
  data["action"] = action;
  player["username"] = username;
  data.insert("player", player);
  object.insert("data", data);
  QJsonDocument doc = QJsonDocument(object);
  return doc;
}

QJsonDocument Notification::action(Action action,
                                   tetrimino::Direction direction) {
  if (action != MOVE) throw std::invalid_argument("Wrong action");
  QJsonObject object;
  QJsonObject data;
  QJsonObject move;
  object["key"] = "ACTION";
  data["action"] = action;
  move["direction"] = direction;
  data.insert("direction", move);
  object.insert("data", data);
  QJsonDocument doc = QJsonDocument(object);
  return doc;
}

QJsonDocument Notification::action(Action action) {
  if (action != HOLD && action != HARDDROP && action != SOFTDROP &&
      action != LEAVE)
    throw std::invalid_argument("Wrong action");
  QJsonObject object;
  QJsonObject data;
  object["key"] = "ACTION";
  data["action"] = action;
  object.insert("data", data);
  QJsonDocument doc = QJsonDocument(object);
  return doc;
}

QJsonDocument Notification::action(Action action, unsigned long score) {
  if (action != LOST) throw std::invalid_argument("Wrong action");
  QJsonObject object;
  QJsonObject data;
  object["key"] = "ACTION";
  data["action"] = action;
  data["score"] = QString::fromStdString(std::to_string(score));
  object.insert("data", data);
  QJsonDocument doc = QJsonDocument(object);
  return doc;
}

QJsonDocument Notification::action(Action action, bool clockwise) {
  if (action != ROTATE) throw std::invalid_argument("Wrong action");
  QJsonObject object;
  QJsonObject data;
  object["key"] = "ACTION";
  data["action"] = action;
  data["clockwise"] = clockwise;
  object.insert("data", data);
  QJsonDocument doc = QJsonDocument(object);
  return doc;
}

QJsonDocument Notification::starting_game(const QString& player_name,
                                          unsigned long player_score,
                                          const QString& opponent_name,
                                          unsigned long opponent_score,
                                          uint_fast64_t seed) {
  QJsonObject object;
  QJsonObject data;
  QJsonObject playerObject;
  QJsonObject opponentObject;
  object["key"] = "STARTING_GAME";
  playerObject["name"] = player_name;
  playerObject["highscore"] =
      QString::fromStdString(std::to_string(player_score));
  opponentObject["name"] = opponent_name;
  opponentObject["highscore"] =
      QString::fromStdString(std::to_string(opponent_score));
  data.insert("player", playerObject);
  data.insert("opponent", opponentObject);
  data["seed"] = QString::fromStdString(std::to_string(seed));
  object.insert("data", data);
  QJsonDocument doc = QJsonDocument(object);
  return doc;
}

}  // namespace tetris::model::notification