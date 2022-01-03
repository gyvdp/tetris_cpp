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

#include "model/notifier/notification.hpp"

using namespace tetris::model::notifier;

QJsonDocument Notification::action(Action action, const std::string& username) {
  if (action != CONNECTION && action != LEAVE)
    throw std::invalid_argument("Wrong action");
  QJsonObject object;
  QJsonObject data;
  QJsonObject player;
  object["key"] = "ACTION";
  data["action"] = action;
  player["username"] = QString::fromStdString(username);
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
  if (action != HOLD && action != HARDDROP && action != SOFTDROP)
    throw std::invalid_argument("Wrong action");
  QJsonObject object;
  QJsonObject data;
  object["key"] = "ACTION";
  data["action"] = action;
  object.insert("data", data);
  QJsonDocument doc = QJsonDocument(object);
  return doc;
}

QJsonDocument Notification::starting_game(model::game::Player& player,
                                          model::game::Player& opponent,
                                          long seed) {
  QJsonObject object;
  QJsonObject data;
  QJsonObject playerObject;
  QJsonObject opponentObject;
  object["key"] = "STARTING_GAME";
  playerObject["name"] = QString::fromLatin1(player.name());
  playerObject["highscore"] = static_cast<int>(player.highScore());
  opponentObject["name"] = QString::fromLatin1(opponent.name());
  opponentObject["highscore"] = static_cast<int>(opponent.highScore());
  data.insert("player", playerObject);
  data.insert("opponent", opponentObject);
  data["seed"] = static_cast<int>(seed);
  object.insert("data", data);
  QJsonDocument doc = QJsonDocument(object);
  return doc;
}
void Notification::interpreter(QByteArray& message,
                               model::game::OngoingGame& game) {
  QJsonDocument doc = QJsonDocument::fromJson(message);
  QString key = doc.object()["key"].toString();
  if (key == "ACTION") {
    QJsonObject data = doc.object()["data"].toObject();
    // TODO METHOD A FINI

    //    switch (data["action"].asInt()) {
    //      case CONNECTION:
    //        // A faire via le client
    //        break;
    //      case LEAVE:
    //        // A faire via le client
    //        break;
    //      case MOVE:
    //        game.move(static_cast<tetrimino::Direction>(data["direction"].asInt()));
    //        break;
    //      case SOFTDROP:
    //        game.softDrop();
    //        break;
    //      case HARDDROP:
    //        game.hardDrop();
    //        break;
    //      case HOLD:
    //        game.holdFalling();
    //        break;
    //    }
  } else if (key == "STARTING_GAME") {
    // A Faire une fois que j'ai la classe duel ou autre genre.
  }
}