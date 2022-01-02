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
#include "tetris_client.hpp"

namespace tetris::client {
tetris_client::tetris_client(QObject *parent) : QObject(parent) {}

void tetris_client::doConnect() {
  socket = new QTcpSocket(this);

  connect(socket, SIGNAL(connected()), this, SLOT(connected()));
  connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
  connect(socket, SIGNAL(bytesWritten(qint64)), this,
          SLOT(bytesWritten(qint64)));
  connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

  qDebug() << "connecting...";

  socket->connectToHost("127.0.0.1", 9999);

  if (!socket->waitForConnected(5000)) {
    qDebug() << "Error: " << socket->errorString();
  }
}

void tetris_client::connected() {
  qDebug() << "connected...";

  // Hey server, tell me about you.
  socket->write("HEAD / HTTP/1.0\r\n\r\n\r\n\r\n");
}

void tetris_client::disconnected() { qDebug() << "disconnected..."; }

void tetris_client::bytesWritten(qint64 bytes) {
  qDebug() << bytes << " bytes written...";
}

void tetris_client::readyRead() {
  qDebug() << "reading...";

  // read the data from the socket
  qDebug() << socket->readAll();
}

}  // namespace tetris::client