#ifndef CONNECTION_TO_SERVER_H
#define CONNECTION_TO_SERVER_H

#include <QWidget>
#include <QtNetwork/QTcpSocket>
#include <QTextEdit>
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
    std::string requestDocIdDatoUri(QString uri, int userId);
    std::shared_ptr<QMap<int, QString>> getKnownDocuments(int userId);
    std::string requestDocName(int docId);
    std::shared_ptr<QSet<int>> getWorkingUsersOnDocument(int docId);
    std::string requestDeleteDoc(int userId,int documentId);
    int getDocumentOwner(int docId);
    std::string openDoc(int userId, int docId);
    void requestSendMessage(const CRDT_Message& messaggio);
    void requestSendMovedCursor(int userId, int pos);
    void requestSendStopCursor();
    void requestSendStartCursor();
    void requestChangeAlign(Qt::Alignment al);
    void connectEditor();
    void disconnectEditor(int userId, int docId);
    std::shared_ptr<QSet<int>> getContributors(int docId);
    QByteArray getFileTMP();
    std::shared_ptr<QTextEdit> requestDocumentText(int docId, int userId);
    bool pingServer();

private slots:
    void displayError(int socketError, const QString &message);
    void acceptData();
    void receiveMessage(QByteArray data);

signals:
    void error(int socketError, const QString &message);
    //void error(QTcpSocket::SocketError socketError);
    void newFile(const QString &fortune);
    void sigProcessMessage(const CRDT_Message& m);
    void sigMoveCursor(const int userId, const int pos);
    void sigStopCursor(int userId);
    void sigStartCursor(int userId);
    void sigChangeAlign(Qt::Alignment al);
    void sigOfflineUser(int userId);
    void sigOnlineUser(int userid, QString nickname, QString iconId);
    void sigNewContributor(int userid, QString nickname, QString iconId);
    void unavailableSharedDocument(int docId);
    void dataReceived(QByteArray data);
    void forceCloseEditor();

private:
    QString port;
    QString ipAddress;  
    QTcpSocket *tcpSocket = nullptr;
    QByteArray fileTMP;
    QByteArray sendBuffer;
    //GUI_Editor *editor = nullptr;
    const int Timeout = 100 * 1000;
    QByteArray readBuffer;
    qint32 readBuffer_size;
    QByteArray readData();
    void readDataFile();
    bool writeData(QByteArray data);
    bool writeDataBuffer();
    static QByteArray IntToArray(qint32 source);
    static qint32 ArrayToInt(QByteArray source);

    //QNetworkSession *networkSession = nullptr;
};

#endif // CONNECTION_TO_SERVER_H
