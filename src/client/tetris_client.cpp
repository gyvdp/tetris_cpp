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
#include "client/tetris_client.hpp"

#include <iostream>
#include <utility>

#include "client/exceptions/connexion_not_possible_exception.hpp"

namespace tetris::client {

void Tetris_Client::connection(std::string ip, unsigned port,
                               std::string username) {
  // Verify ip
  std::string regex = "^(?:[0-9]{1,3}.){3}[0-9]{1,3}$";
  if (!std::regex_match(ip, std::regex(regex)))
    throw std::invalid_argument("ip address is not valid");

  // Open socket
  socket_->open(QIODevice::ReadWrite);

  // Connect
  connect(socket_, &QAbstractSocket::connected, this,
          &Tetris_Client::slot_Connected);
  connect(socket_, &QAbstractSocket::disconnected, this,
          &Tetris_Client::slot_Disconnected);
  connect(socket_, &QAbstractSocket::readyRead, this,
          &Tetris_Client::slot_Reading);

  this->username_ = username;

  // Connection to the server with ip and port
  socket_->connectToHost(QHostAddress(QString::fromStdString(ip)), port);

  // Waiting for connection
  if (!socket_->waitForConnected(5000)) {
    throw exceptions::ConnexionNotPossibleException("Connexion impossible",
                                                    __FILE__, __LINE__);
  }
}

void Tetris_Client::sendData(const QJsonDocument& data) {
  QByteArray arrayData = QByteArray(data.toJson(QJsonDocument::Indented));
  this->socket_->write(arrayData);
  this->socket_->waitForBytesWritten();
}

void Tetris_Client::slot_Connected() {
  qDebug() << "connected...";

  socket_->write(tetris::model::notification::Notification::action(
                     model::notification::CONNECTION, this->username_)
                     .toJson(QJsonDocument::Indented));
  this->socket_->waitForBytesWritten();
}

void Tetris_Client::slot_Disconnected() { qDebug() << "disconnected..."; }

void Tetris_Client::slot_Reading() {
  this->socket_->waitForConnected();
  QJsonDocument doc = QJsonDocument::fromJson(socket_->readAll());
  qDebug() << "reading..." << doc.object()["key"].toString();
  qDebug() << doc.toJson(QJsonDocument::Indented);
}

}  // namespace tetris::client