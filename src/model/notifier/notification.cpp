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

#include <QByteArray>

using namespace tetris::model::notifier;

Json::Value Notification::action(Action action, const std::string& username) {
  if (action != CONNECTION && action != LEAVE)
    throw std::invalid_argument("Wrong action");
  Json::Value update;
  update["key"] = "ACTION";
  update["data"]["action"] = action;
  update["data"]["player"]["username"] = username;
  return update;
}

Json::Value Notification::action(Action action,
                                 tetrimino::Direction direction) {
  if (action != MOVE) throw std::invalid_argument("Wrong action");
  Json::Value update;
  update["key"] = "ACTION";
  update["data"]["action"] = action;
  update["data"]["direction"] = direction;
  return update;
}

Json::Value Notification::action(Action action) {
  if (action != HOLD && action != HARDDROP && action != SOFTDROP)
    throw std::invalid_argument("Wrong action");
  Json::Value update;
  update["key"] = "ACTION";
  update["data"]["action"] = action;
  return update;
}

Json::Value Notification::starting_game(model::game::Player& player,
                                        model::game::Player& opponent,
                                        long seed) {
  Json::Value update;
  update["key"] = "STARTING_GAME";
  update["data"]["player"]["name"] = static_cast<std::string>(player.name());
  update["data"]["player"]["highScore"] =
      static_cast<unsigned>(player.highScore());
  update["data"]["opponent"]["name"] =
      static_cast<std::string>(opponent.name());
  update["data"]["opponent"]["highScore"] =
      static_cast<unsigned>(opponent.highScore());
  update["data"]["bag"]["seed"] = static_cast<int>(seed);
  return update;
}

Json::Value Notification::board(model::game::Matrix& matrix) {
  Json::Value update;
  update["key"] = "BOARD";
  for (int height = 0; height < matrix.height(); height++)
    for (int width = 0; width < matrix.width(); width++) {
      update["data"]["board"]["case"]["coordinate"]["x"] = height;
      update["data"]["board"]["case"]["coordinate"]["y"] = width;
      update["data"]["board"]["case"]["mino"] =
          matrix.get(utils::Coordinate(height, width)).value();
    }
  return update;
}

void Notification::interpreter(QByteArray& message,
                               model::game::OngoingGame& game) {
  Json::Value data = message.toStdString();
  std::string key = data["key"].asString();
  if (key == "ACTION") {
    switch (data["action"].asInt()) {
      case CONNECTION:
        // A faire via le client
        break;
      case LEAVE:
        // A faire via le client
        break;
      case MOVE:
        game.move(static_cast<tetrimino::Direction>(data["direction"].asInt()));
        break;
      case SOFTDROP:
        game.softDrop();
        break;
      case HARDDROP:
        game.hardDrop();
        break;
      case HOLD:
        game.holdFalling();
        break;
    }
  } else if (key == "STARTING_GAME") {
    // A Faire une fois que j'ai la classe duel ou autre genre.
  }
}