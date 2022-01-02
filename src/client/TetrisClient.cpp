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

// namespace tetris::client {

// TetrisClient::TetrisClient(QObject *parent) : QObject(parent) {}

// void TetrisClient::doConnect() {
//   socket = new QTcpSocket(this);

//  connect(socket, SIGNAL(connected()), this, SLOT(connected()));
//  connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
//  connect(socket, SIGNAL(bytesWritten(qint64)), this,
//          SLOT(bytesWritten(qint64)));
//  connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

//  qDebug() << "connecting...";

//  // this is not blocking call
//  socket->connectToHost("127.0.0.1", 1234);

//  // we need to wait...
//  if (!socket->waitForConnected(5000)) {
//    qDebug() << "Error: " << socket->errorString();
//  }
//}

// void TetrisClient::connected() {
//   qDebug() << "connected...";

//  // Hey server, tell me about you.
//  socket->write("HEAD / HTTP/1.0\r\n\r\n\r\n\r\n");
//}

// void TetrisClient::disconnected() { qDebug() << "disconnected..."; }

// void TetrisClient::bytesWritten(qint64 bytes) {
//   qDebug() << bytes << " bytes written...";
// }

// void TetrisClient::readyRead() {
//   qDebug() << "reading...";

//  // read the data from the socket
//  qDebug() << socket->readAll();
//}

//}  // namespace tetris::client
#include "TetrisClient.hpp"

namespace tetris::client {
TetrisClient::TetrisClient(QObject *parent) : QObject(parent) {}

void TetrisClient::doConnect() {
  socket = new QTcpSocket(this);

  connect(socket, SIGNAL(connected()), this, SLOT(connected()));
  connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
  connect(socket, SIGNAL(bytesWritten(qint64)), this,
          SLOT(bytesWritten(qint64)));
  connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

  qDebug() << "connecting...";

  // this is not blocking call
  socket->connectToHost("127.0.0.1", 9999);

  // we need to wait...
  if (!socket->waitForConnected(5000)) {
    qDebug() << "Error: " << socket->errorString();
  }
}

void TetrisClient::connected() {
  qDebug() << "connected...";

  // Hey server, tell me about you.
  socket->write("HEAD / HTTP/1.0\r\n\r\n\r\n\r\n");
}

void TetrisClient::disconnected() { qDebug() << "disconnected..."; }

void TetrisClient::bytesWritten(qint64 bytes) {
  qDebug() << bytes << " bytes written...";
}

void TetrisClient::readyRead() {
  qDebug() << "reading...";

  // read the data from the socket
  qDebug() << socket->readAll();
}

}  // namespace tetris::client