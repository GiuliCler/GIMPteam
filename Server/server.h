#ifndef SERVER_H
#define SERVER_H

#include <QDialog>
#include <QString>
#include <QVector>
#include "database/collegamentoDB.h"
#include "crdt/crdt_message.h"

QT_BEGIN_NAMESPACE
#include <QFileSystemModel>
#include <QMap>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtNetwork>

class Server : public QTcpServer {
    Q_OBJECT
public:
    Server(QObject *parent = nullptr);

protected:
    void incomingConnection(qintptr socketDescriptor) override;
    void timerEvent(QTimerEvent *event) override;

signals:
    void error(QTcpSocket::SocketError socketError);
    void dispatchMessage(CRDT_Message m, QString thread_id_sender, int docId);
    void checkPeriodicoClientConnessi();

private:
    int socketDescriptor;
};

#endif
