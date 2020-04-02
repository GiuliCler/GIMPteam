#ifndef SERVER_H
#define SERVER_H

#include <QDialog>
#include <QString>
#include <QVector>
#include "database/collegamentoDB.h"

QT_BEGIN_NAMESPACE
#include <QMap>
#include <QTcpServer>
#include <QTcpSocket>

//! [0]
class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server(QObject *parent = nullptr);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

signals:
    void error(QTcpSocket::SocketError socketError);

public slots:
    //void disconnectFromClient();
    void runServer();

private:
    QStringList fortunes;
    CollegamentoDB *database;
    int socketDescriptor;
    QTcpSocket *socket;
    QMap<QString, int> users;
    QMap<QString, int> documents;
    QMap<int, std::vector<int>> online;    // QMap formata da coppie (docId, [userId1, userId2, userId3, ...])
};
//! [0]

#endif
