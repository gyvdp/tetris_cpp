#ifndef ESI_ATLIR5_ATLC_PROJECT2_SRC_CLIENT_TETRIS_CLIENT_HPP_
#define ESI_ATLIR5_ATLC_PROJECT2_SRC_CLIENT_TETRIS_CLIENT_HPP_

#include <QAbstractSocket>
#include <QDebug>
#include <QObject>
#include <QTcpSocket>

namespace tetris::client {

class tetris_client : public QObject {
  Q_OBJECT

 private:
  QTcpSocket *socket;

 public:
  explicit tetris_client(QObject *parent = nullptr);

  void doConnect();

 signals:

 public slots:
  void connected();
  void disconnected();
  void bytesWritten(qint64 bytes);
  void readyRead();
};
}  // namespace tetris::client
#endif  // ESI_ATLIR5_ATLC_PROJECT2_SRC_CLIENT_TETRIS_CLIENT_HPP_
