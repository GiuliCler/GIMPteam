#ifndef CONNECTION_TO_SERVER_H
#define CONNECTION_TO_SERVER_H

#include <QWidget>

#include <QtNetwork/QTcpSocket>


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
    int requestNewAccount(QString username, QString password, QString nickname, QString icon);
    long requestUpdateAccount(int userId, QString password, QString nickname, QString icon);
    long requestCreateDocument(int userId, QString name);
    QString requestGetNickname(int userId);
    QString requestGetUsername(int userId);
    QString requestIconId(int userId);
    std::string requestUri(long docId);
    std::string requestDocDatoUri(QString uri);

private slots:
    void showFile(const QString &file);
    void displayError(int socketError, const QString &message);
    void responseAtRequest();

signals:
    void error(int socketError, const QString &message);
    void error(QTcpSocket::SocketError socketError);

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
