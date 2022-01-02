#ifndef ESI_ATLIR5_ATLC_PROJECT2_INCLUDE_SERVER_MATCH_HPP_
#define ESI_ATLIR5_ATLC_PROJECT2_INCLUDE_SERVER_MATCH_HPP_

#include <QDebug>
#include <QString>
#include <QTcpSocket>
#include <array>
#include <memory>

namespace tetris::server {

class Match : public QObject {
  Q_OBJECT
 private:
  std::array<QTcpSocket*, 2> players_;

  unsigned id_;

 public:
  explicit Match(QTcpSocket* player1, QTcpSocket* player2, unsigned id);

 signals:

 public slots:
  void slot_Disconnected();
  void slot_Reading();
};
}  // namespace tetris::server
#endif  // ESI_ATLIR5_ATLC_PROJECT2_INCLUDE_SERVER_MATCH_HPP_
