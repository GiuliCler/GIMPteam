#ifndef CONNECTION_TO_SERVER_H
#define CONNECTION_TO_SERVER_H

#include <QWidget>
#include <QtNetwork/QTcpSocket>
#include <memory>
#include "GUI/connection/gui_connectionException.h"
#include "GUI/connection/gui_genericException.h"
#include "GUI/editorWindow/gui_editor.h"
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
    std::string requestCreateDocument(int userId, QString name);
    std::string requestGetNickname(int userId);
    std::string requestGetUsername(int userId);
    std::string requestIconId(int userId);
    std::string requestUri(int docId);
    std::string requestDocDatoUri(QString uri, int userId);
    std::shared_ptr<QMap<QString, int>> getKnownDocuments(int userId);
    QTcpSocket *getSocket();
    std::string requestDocName(int docId);
    std::shared_ptr<QSet<int>> getWorkingUsersOnDocument(int docId);
    std::string requestDeleteDoc(int userId,int documentId);
    int getDocumentOwner(int docId);
    std::string openDoc(int userId, int docId);
    void requestSendMessage(CRDT_Message *messaggio);
    void connectEditor();
    void disconnectEditor(int userId, int docId);
    void receiveMessage();
    std::shared_ptr<QSet<int>> getContributors(int docId);

private slots:
    void showFile(const QString &file);
    void displayError(int socketError, const QString &message);

signals:
    void error(int socketError, const QString &message);
    void error(QTcpSocket::SocketError socketError);
    void newFile(const QString &fortune);
    void sigProcessMessage(const CRDT_Message& m);
    void sigOfflineUser(int userId);
    void sigOnlineUser(int userId);
    void sigNewContributor(int userId);
    void unavailableSharedDocument(int docId);

private:
    QString port;
    QString ipAddress;
    //Files file;
    QString current;
    QTcpSocket *tcpSocket = nullptr;
    //GUI_Editor *editor = nullptr;
    const int Timeout = 100 * 1000;


    //QNetworkSession *networkSession = nullptr;
};

#endif // CONNECTION_TO_SERVER_H
