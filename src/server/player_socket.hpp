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
  const std::string name_;

 public:
  explicit inline Player_Socket(QTcpSocket*& socket, std::string name,
                                QObject* parent);

  [[nodiscard]] inline QTcpSocket* socket() const;

  [[nodiscard]] inline const std::string& name() const;

  inline void write(const QJsonDocument& doc);

  inline void write(const QByteArray& data);

  inline void parent(QObject* parent);
};

Player_Socket::Player_Socket(QTcpSocket*& socket, std::string name,
                             QObject* parent)
    : QObject(parent), socket_{socket}, name_(std::move(name)) {
  this->socket_->disconnect();
}

QTcpSocket* Player_Socket::socket() const { return socket_; }
const std::string& Player_Socket::name() const { return name_; }
void Player_Socket::write(const QByteArray& data) {
  this->socket_->write(data);
  this->socket_->waitForBytesWritten();
}

void Player_Socket::write(const QJsonDocument& doc) {
  this->socket_->write(doc.toJson(QJsonDocument::Compact));
}

void Player_Socket::parent(QObject* parent) { this->setParent(parent); }

}  // namespace tetris::server
#endif  // ESI_ATLIR5_ATLC_PROJECT2_SRC_SERVER_PLAYER_SOCKET_HPP_
