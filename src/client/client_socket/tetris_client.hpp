#ifndef ESI_ATLIR5_ATLC_PROJECT2_SRC_CLIENT_TETRIS_CLIENT_HPP_
#define ESI_ATLIR5_ATLC_PROJECT2_SRC_CLIENT_TETRIS_CLIENT_HPP_

#include <QAbstractSocket>
#include <QDebug>
#include <QException>
#include <QJsonDocument>
#include <QObject>
#include <QTcpSocket>
#include <regex>
#include <stdexcept>

namespace tetris::client {

class Tetris_Client : public QObject {
  Q_OBJECT

 private:
  QTcpSocket *socket_;

 public:
  inline explicit Tetris_Client(QObject *parent = nullptr) : QObject(parent) {
    this->socket_ = new QTcpSocket(this);
  }

  void sendData(const QJsonDocument &);

  void connection(std::string ip, unsigned port);

 signals:

 public slots:
  void slot_Connected();
  void slot_Disconnected();
  void slot_Reading();
};
}  // namespace tetris::client
#endif  // ESI_ATLIR5_ATLC_PROJECT2_SRC_CLIENT_TETRIS_CLIENT_HPP_
