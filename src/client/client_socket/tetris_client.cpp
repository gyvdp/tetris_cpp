#include "tetris_client.hpp"

#include <iostream>

namespace tetris::client {

void Tetris_Client::connection(std::string ip, unsigned port) {
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

  // Connection to the server with ip and port
  socket_->connectToHost(QHostAddress(QString::fromStdString(ip)), port);

  // Waiting for connection
  if (!socket_->waitForConnected(5000)) {
    // Todo exception @Gregory UwU
  }
}

void Tetris_Client::sendData(const QJsonDocument& data) {
  QByteArray arrayData = QByteArray(data.toJson(QJsonDocument::Indented));
  this->socket_->write(arrayData);
  this->socket_->waitForBytesWritten();
}

void Tetris_Client::slot_Connected() {
  qDebug() << "connected...";

  // Writing on connection (ACTION CONNECTION)
  //  socket_->write("Hello server");
  //  this->socket_->waitForBytesWritten();
}

void Tetris_Client::slot_Disconnected() { qDebug() << "disconnected..."; }

void Tetris_Client::slot_Reading() {
  this->socket_->waitForConnected();
  qDebug() << "reading..." << socket_->readAll();
}

}  // namespace tetris::client