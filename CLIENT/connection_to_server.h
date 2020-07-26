#ifndef CONNECTION_TO_SERVER_H
#define CONNECTION_TO_SERVER_H

#include <QWidget>
#include <QtNetwork/QTcpSocket>
#include <memory>
#include "GUI/connection/gui_connectionException.h"
#include "GUI/connection/gui_genericException.h"
#include "CRDT/crdt_message.h"

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QAction;
QT_END_NAMESPACE

class connection_to_server : public QWidget
{
        Q_OBJECT

public:
    connection_to_server(QString port, QString ipAddress);
    int requestTryLogin(QString username, QString password);
    int requestTryLogOut(int userId);
    int requestNewAccount(QString username, QString password, QString nickname, QString icon);
    long requestUpdateAccount(int userId, QString password, QString nickname, QString icon);
    long requestCreateDocument(int userId, QString name);
    std::string requestGetNickname(int userId);
    std::string requestGetUsername(int userId);
    std::string requestIconId(int userId);
    std::string requestUri(int docId);
    long requestDocDatoUri(QString uri);
    std::shared_ptr<QMap<QString, int>> getKnownDocuments(int userId);
    QString getDocumentName(int docId);
    QTcpSocket *getSocket();
    std::string requestDocName(int docId);
    std::shared_ptr<QSet<int>> getWorkingUsersOnDocument(int docId);
    std::string requestDeleteDoc(int userId,int documentId);
    void requestSendMessage(CRDT_Message *messaggio);
    void setEditor(int docId);
    void processMessage();

private slots:
    void showFile(const QString &file);
    void displayError(int socketError, const QString &message);

signals:
    void error(int socketError, const QString &message);
    void error(QTcpSocket::SocketError socketError);
    void newFile(const QString &fortune);

private:
    QString port;
    QString ipAddress;
    //Files file;
    QString current;
    QTcpSocket *tcpSocket = nullptr;
    const int Timeout = 100 * 1000;


    //QNetworkSession *networkSession = nullptr;
};

#endif // CONNECTION_TO_SERVER_H
