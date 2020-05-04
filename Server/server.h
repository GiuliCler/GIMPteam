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
    ~Server() override;

protected:
    void incomingConnection(qintptr socketDescriptor) override;

signals:
    void error(QTcpSocket::SocketError socketError);
//    void notifica_tutti_i_threads(CRDT_Message messaggio);
    void notifica_tutti_i_threads(int messaggio);

public slots:
    void runServer();

private:
    CollegamentoDB *database;
    int socketDescriptor;
//    QTcpSocket *socket;
};

#endif
