#include "server/tetris_server.hpp"

namespace tetris::server {

Tetris_Server::Tetris_Server(QObject *parent) : QObject(parent), matchID_{0} {
  // Creating server application
  server_ = new QTcpServer(this);

  // Add Settings to serv ? Catch if can't
  if (!server_->listen(QHostAddress::Any, 9999))
    throw 1;  // TODO @Gregory need Exception style UwU
  qDebug() << "Server active on : IP :" << server_->serverAddress()
           << " , Port : " << server_->serverPort();

  // Connect
  connect(server_, &QTcpServer::newConnection, this,
          &Tetris_Server::slot_Connected);
}

void Tetris_Server::slot_Connected() {
  // Crée un nouveau socket sur la demande du client.
  QTcpSocket *socket = server_->nextPendingConnection();
  socket->waitForConnected();
  socket->open(QIODevice::ReadWrite);

  if (this->waitingQueue_.empty()) {
    // Ajout dans la waiting list
    connect(socket, &QAbstractSocket::disconnected, this,
            &Tetris_Server::slot_Disconnected);
    this->waitingQueue_.push(socket);
  } else {
    // Création d'un match
    // TO DO PRESENCE SEG FAULT LORS DE LA CREATION D UN MATCH
    this->waitingQueue_.front()->disconnect();
    this->matchVector_.push_back(std::make_shared<Match *>(
        new Match(this->waitingQueue_.front(), socket, ++matchID_)));
    this->waitingQueue_.pop();
  }
}

void Tetris_Server::slot_Disconnected() {
  this->waitingQueue_.pop();
  qDebug() << "Suppresion de la liste d'attente";
}
}  // namespace tetris::server
