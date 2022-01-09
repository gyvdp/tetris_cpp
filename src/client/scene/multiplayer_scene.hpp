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
#ifndef ESI_ATLIR5_ATLC_PROJECT2_SRC_CLIENT_VIEW_GAME_HPP_
#define ESI_ATLIR5_ATLC_PROJECT2_SRC_CLIENT_VIEW_GAME_HPP_
#include <QGraphicsScene>

#include "client/component/game.hpp"
#include "client/component/matrix.hpp"
#include "client/component/mino.hpp"
#include "client/socket_client.hpp"
#include "model/game/ongoinggame.hpp"

namespace tetris::client::scene {
/**
 * @brief This class represents a GameScene
 */
class MultiplayerScene : public QGraphicsScene {
  Q_OBJECT
 protected:
  component::Game *player1_;

  model::game::OngoingGame *player1Game_;
  model::game::OngoingGame *player2Game_;

  component::Game *player2_;

  void keyPressEvent(QKeyEvent *event) override;

 public:
  /**
   * @brief Default constructor fot a GameScene
   * @param parent Parent QObject (for memory)
   */
  explicit MultiplayerScene(model::game::Player *player1,
                            model::game::Player *player2, uint_fast64_t seed,
                            Socket_Client *socket, QObject *parent = nullptr);

  /**
   * @brief Destructor of a GameScene
   */
  ~MultiplayerScene() override;
};
}  // namespace tetris::client::scene
#endif  // ESI_ATLIR5_ATLC_PROJECT2_SRC_CLIENT_VIEW_GAME_HPP_
