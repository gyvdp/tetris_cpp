#ifndef ESI_ATLIR5_ATLC_PROJECT2_INCLUDE_SERVER_MATCH_HPP_
#define ESI_ATLIR5_ATLC_PROJECT2_INCLUDE_SERVER_MATCH_HPP_

#include <QDebug>
#include <QTcpSocket>
#include <array>
#include <memory>

class Match : public QObject {
  Q_OBJECT
 private:
  std::array<std::shared_ptr<QTcpSocket>, 2> players_;
  unsigned id_;

 public:
  inline explicit Match(const std::shared_ptr<QTcpSocket>& player1,
                        const std::shared_ptr<QTcpSocket>& player2, unsigned id)
      : players_({player1, player2}), id_(id) {
    qDebug() << "Creat match " << id;
    for (auto& player : players_) {
      //      connect(player.get(), SIGNAL(connected()), this,
      //      SLOT(connected())); connect(player.get(), SIGNAL(disconnected()),
      //      this, SLOT(disconnected())); connect(player.get(),
      //      SIGNAL(bytesWritten(qint64)), this,
      //              SLOT(bytesWritten(qint64)));
      //      connect(player.get(), SIGNAL(readyRead()), this,
      //      SLOT(readyRead())); player->write("Game Launched");
    }
  }

  // public slots:
  //  void communication();
  //  void disconnected();
  //  void bytesWritten(QByteArray);
  //  void readyRead(QByteArray);
};

#endif  // ESI_ATLIR5_ATLC_PROJECT2_INCLUDE_SERVER_MATCH_HPP_
