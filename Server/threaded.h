#ifndef THREADED_H
#define THREADED_H

#include <QThread>
#include <QTcpSocket>
#include "database/collegamentoDB.h"

//! [0]
class Threaded : public QThread
{
    Q_OBJECT

public:
    Threaded(QObject *parent, CollegamentoDB *DB);

/*public slots:
    void disconnectFromClient();
    void runServer();

signals:
    void error(QTcpSocket::SocketError socketError);
*/
private:
    qintptr socketDescriptor;
    QString text;
    CollegamentoDB DB;
};
//! [0]

#endif
