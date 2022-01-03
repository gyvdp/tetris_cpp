#include "server/match.hpp"

namespace tetris::server {

Match::Match(QTcpSocket* player1, QTcpSocket* player2, unsigned id)
    : players_({player1, player2}), id_(id) {
  // Connect
  for (auto& player : players_) {
    connect(player, &QAbstractSocket::disconnected, this,
            &Match::slot_Disconnected);
    connect(player, &QAbstractSocket::readyRead, this, &Match::slot_Reading);
  }
  qDebug() << "lancement d'un match";
}

void Match::slot_Disconnected() {
  // GESTION DE LA DECONNECTION D UN JOUEUR
  qDebug() << "disconnected...";
}

void Match::slot_Reading() {
  for (auto& sender : this->players_) {
    auto data = sender->readAll();
    for (auto& receiver : this->players_) {
      if (&(*sender) != &(*receiver)) receiver->write(data);
      receiver->waitForBytesWritten();
    }
    qDebug() << "data : " << data;
  }
}
}  // namespace tetris::server
