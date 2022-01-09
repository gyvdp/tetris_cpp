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

#ifndef ESI_ATLIR5_ATLC_PROJECT2_SRC_SERVER_PLAYER_SOCKET_HPP_
#define ESI_ATLIR5_ATLC_PROJECT2_SRC_SERVER_PLAYER_SOCKET_HPP_

#include <QJsonDocument>
#include <QJsonObject>
#include <QTcpSocket>
#include <utility>

namespace tetris::server {
class Player_Socket : QObject {
  Q_OBJECT
 private:
  QTcpSocket* socket_;
  const QString name_;
  unsigned long highScore_;

 public:
  /**
   * @brief Constructor of Player_Socket
   * @param socket Socket to communicate with the player
   * @param name Name of the player
   * @param parent Where the player is in
   */
  explicit inline Player_Socket(QTcpSocket*& socket, QString name,
                                unsigned long highscore, QObject* parent);

  /**
   * @brief Getter of socket
   * @return pointer of socket
   */
  [[nodiscard]] inline QTcpSocket* socket();

  /**
   * @brief  Getter of Name
   * @return Name
   */
  [[nodiscard]] inline QString name();

  /**
   * @brief Write on the socket from a QJsonDocument
   * @param doc QJsonDocument with information
   */
  [[maybe_unused]] [[maybe_unused]] inline void write(const QJsonDocument& doc);

  /**
   * @brief Write on the socket from a QByteArray
   * @param data QBytesArray with information
   */
  inline void write(const QByteArray& data);

  /**
   * @brief Setter of Parent
   * @param parent new Parent to link with
   */
  inline void parent(QObject* parent);

  /**
   * @brief Getter of HighScore
   * @return HighScore of the player
   */
  [[nodiscard]] inline unsigned long highScore() const;
};

Player_Socket::Player_Socket(QTcpSocket*& socket, QString name,
                             unsigned long highscore, QObject* parent)
    : QObject(parent),
      socket_{socket},
      name_(std::move(name)),
      highScore_(highscore) {
  this->socket_->disconnect();
}

QTcpSocket* Player_Socket::socket() { return this->socket_; }

QString Player_Socket::name() { return this->name_; }

[[maybe_unused]] void Player_Socket::write(const QJsonDocument& doc) {
  this->socket_->write(doc.toJson(QJsonDocument::Indented));
  this->socket_->waitForBytesWritten();
}

void Player_Socket::write(const QByteArray& data) {
  this->socket_->write(data);
  this->socket_->waitForBytesWritten();
}

void Player_Socket::parent(QObject* parent) { this->setParent(parent); }

unsigned long Player_Socket::highScore() const { return this->highScore_; }
}  // namespace tetris::server
#endif  // ESI_ATLIR5_ATLC_PROJECT2_SRC_SERVER_PLAYER_SOCKET_HPP_
