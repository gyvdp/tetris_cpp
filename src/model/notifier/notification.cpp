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

Json::Value Notification::actual(const model::tetrimino::Tetrimino& tetrimino) {
  Json::Value update;
  update["key"] = "ACTUAL";
  update["data"]["mino"] = tetrimino.type();
  update["data"]["coordinate"]["x"] = static_cast<int>(tetrimino.X());
  update["data"]["coordinate"]["y"] = static_cast<int>(tetrimino.Y());
  return update;
}
Json::Value Notification::connection(const std::string& username) {
  Json::Value update;
  update["key"] = "CONNECTION";
  update["data"]["player"]["username"] = username;
  return update;
}

Json::Value Notification::hold(model::tetrimino::Mino mino) {
  Json::Value update;
  update["key"] = "HOLD";
  update["data"]["mino"] = mino;
  return update;
}

Json::Value Notification::next(model::tetrimino::Mino mino) {
  Json::Value update;
  update["key"] = "NEXT";
  update["data"]["mino"] = mino;
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

/**
 * Le but de ces method est de comprendre la logic et pas de faire comme cela.
 */
void Notification::interpreter(QByteArray& message,
                               model::game::OngoingGame& game) {
  Json::Value data = message.toStdString();
  std::string key = data["key"].asString();
  if (key == "HOLD") {
    game.hold(
        static_cast<model::tetrimino::Mino>(data["data"]["mino"].asInt()));
  } else if (key == "NEXT") {
    game.next(
        static_cast<model::tetrimino::Mino>(data["data"]["mino"].asInt()));
  } else if (key == "ACTUAL") {
    if (game.falling()->type() != data["data"]["mino"].asInt()) {
      game.falling(tetris::model::tetrimino::createTetrimino(
          static_cast<model::tetrimino::Mino>(data["data"]["mino"].asInt())));
    } else {
      //      game.falling()->coordinate_(
      //          utils::Coordinate{data["data"]["coordinate"]["x"].asInt(),
      //                            data["data"]["coordinate"]["y"].asInt()});
    }
  } else if (key == "STARTING_GAME") {
    // game.setPlayerName(data["data"]["player"]["name"]);
    // game.setPlayerHighScore(data["data"]["player"]["highscore"]);
    // game.setOpponentName(data["data"]["opponent"]["name"]);
    // game.setOpponentHighScore(data["data"]["opponent"]["highscore"]);
    // game.setSeed(data["data"]["bag"]["seed"]);
  }
}