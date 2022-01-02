#include "server/tetris_server.hpp"

#include <memory>

namespace tetris::server {

tetris_server::tetris_server(QObject *parent) : QObject(parent), matchID_{0} {
  server_ = new QTcpServer(this);

  connect(server_, SIGNAL(newConnection()), this, SLOT(newConnection()));

  if (!server_->listen(QHostAddress::Any, 9999)) {
    qDebug() << "Server could not start";
  } else {
    qDebug() << "Server started!";
  }
}

void tetris_server::newConnection() {
  std::shared_ptr<QTcpSocket> socket =
      std::make_shared<QTcpSocket>(server_->nextPendingConnection());
  if (this->waitingQueue_.empty()) {
    this->waitingQueue_.push(socket);
    qDebug() << "first Player";
  } else {
    matchID_++;
    this->matchVector_.push_back(
        std::make_shared<Match>(this->waitingQueue_.front(), socket, matchID_));

    this->waitingQueue_.pop();
    qDebug() << "second Player";
  }
}
}  // namespace tetris::server
