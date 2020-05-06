#ifndef THREAD_BODY_H
#define THREAD_BODY_H

#include <QObject>
#include <QTcpSocket>
#include "database/collegamentoDB.h"

class Thread_body : public QObject
{
    Q_OBJECT
public:
    explicit Thread_body(int socketDescriptor, QObject *parent = nullptr);
    QTcpSocket* socket;

private:
    CollegamentoDB* database;
    QDataStream* in;

signals:
    void error(QTcpSocket::SocketError socketError);

public slots:
    void executeJob();

};

#endif // THREAD_BODY_H
