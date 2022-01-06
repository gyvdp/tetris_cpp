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

#include <boost/signals2.hpp>
#include <iostream>

#include "model/game/ongoinggame.hpp"
#include "model/game/player.hpp"
#include "model/game/state/notstartedstate.hpp"
#include "model/tetrimino/tetrimino_logic.hpp"
using namespace tetris::model::game::states;
using namespace tetris::model::tetrimino;
using namespace tetris::model::game;

class TextView {
 public:
  explicit TextView(OngoingGame& game) : game(game) {
    game.connectFalling(boost::bind(&TextView::refresh, this));
    game.connectScore(boost::bind(&TextView::score, this));
  }

  void refresh() const {
    std::cout << "Y: " << game.falling()->Y() << std::endl;
  }

  void score() const { std::cout << "Score: " << game.score() << std::endl; }

 private:
  OngoingGame& game;
};

void print() {}

int main() {
  Player player("John", 123);
  OngoingGame game = OngoingGame(&player, 1);
  TextView v1(game);
  game.start();
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::cout << "Hello, World!" << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(15));
  return 0;
}
