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
#ifndef ESI_ATLIR5_ATLC_PROJECT2_SRC_CLIENT_SOCKET_CLIENT_HPP_
#define ESI_ATLIR5_ATLC_PROJECT2_SRC_CLIENT_SOCKET_CLIENT_HPP_

#include <QAbstractSocket>
#include <QDebug>
#include <QException>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QTcpSocket>
#include <regex>
#include <stdexcept>

#include "model/game/ongoinggame.hpp"
#include "model/notification/notification.hpp"

namespace tetris::client {

class Socket_Client : public QObject {
  Q_OBJECT

 private:
  QTcpSocket* socket_;
  std::string username_;

 public:
  inline explicit Socket_Client(QObject* parent = nullptr) : QObject(parent) {
    this->socket_ = new QTcpSocket(this);
  }

  void sendData(const QJsonDocument&);

  void connection(const QString& ip, unsigned port, const std::string&);

  void deserialize(QByteArray& message);

 signals:
  void leave(unsigned long score);
  void lost(unsigned long score);
  void move(tetris::model::tetrimino::Direction direction);
  void softdrop();
  void starting_game(std::string playerName, unsigned long highScore,
                     std::string opponentName, unsigned long opponentHighScore,
                     uint_fast64_t seed);
  void harddrop();
  void rotate(bool clockwise);
  void hold();
  void lock();

 public slots:
  void slot_Connected();
  void slot_Disconnected();
  void slot_Reading();
  void slot_Rotate(bool clockwise);
  void slot_Lock();
  void slot_Hold(model::tetrimino::Mino m);
  void slot_Move(model::tetrimino::Direction direction);
  void slot_HardDrop();
};
}  // namespace tetris::client
#endif  // ESI_ATLIR5_ATLC_PROJECT2_SRC_CLIENT_SOCKET_CLIENT_HPP_
