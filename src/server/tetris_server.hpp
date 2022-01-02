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

class Tetris_Server : public QObject {
  Q_OBJECT

 private:
  QTcpServer *server_;
  std::queue<QTcpSocket *> waitingQueue_;
  std::vector<std::shared_ptr<Match *>> matchVector_;
  unsigned matchID_;

 public:
  explicit Tetris_Server(QObject *parent = nullptr);

 signals:

 public slots:
  void slot_Connected();
  void slot_Disconnected();
};
}  // namespace tetris::server
#endif  // ESI_ATLIR5_ATLC_PROJECT2_SRC_SERVER_SERVER_TETRISSERVER_HPP_
