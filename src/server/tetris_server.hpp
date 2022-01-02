#ifndef ESI_ATLIR5_ATLC_PROJECT2_SRC_SERVER_SERVER_TETRISSERVER_HPP_
#define ESI_ATLIR5_ATLC_PROJECT2_SRC_SERVER_SERVER_TETRISSERVER_HPP_

#include <QDebug>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <memory>
#include <queue>

#include "match.hpp"

namespace tetris::server {

class tetris_server : public QObject {
  Q_OBJECT

 private:
  QTcpServer *server_;
  std::queue<std::shared_ptr<QTcpSocket>> waitingQueue_;
  std::vector<std::shared_ptr<Match>> matchVector_;
  unsigned matchID_;

 public:
  explicit tetris_server(QObject *parent = nullptr);

 signals:

 public slots:
  void newConnection();
};
}  // namespace tetris::server
#endif  // ESI_ATLIR5_ATLC_PROJECT2_SRC_SERVER_SERVER_TETRISSERVER_HPP_
