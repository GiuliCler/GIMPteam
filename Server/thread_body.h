#ifndef THREAD_BODY_H
#define THREAD_BODY_H

#include <QObject>
#include <QTcpSocket>
#include "database/collegamentoDB.h"
#include <QMutex>

extern QMutex* mutex_users;
extern QMutex* mutex_docs;
extern QMutex* mutex_workingUsers;
extern QMutex* mutex_db;

extern QMap<QString, int> users;
extern QMap<QString, int> documents;
extern QMap<int, QVector<int>> workingUsers;
extern QString path;

class Thread_body : public QObject
{
    Q_OBJECT
public:
    explicit Thread_body(int socketDescriptor, QObject *parent = nullptr);
    QTcpSocket* socket;

private:
    CollegamentoDB* database;
    QDataStream* in;
    void create(QString username, QString password, QString nickname, QString icon);
    void login(QString username, QString password);
    void update(int userId, QString password, QString nickname, QString icon);
    void getUsername(int userId);
    void getNickname(int userId);
    void getIcon(int userId);
    void getDocs(int userId);
    void newDoc(QString docName, int userId);
    void getDocumentDatoUri(QString uri);
    void getUri(int docId);
    void getDocName(int docId);
    void deleteDoc(int userId, int docId);
    void openDoc(int docId, int userId);
    void getWorkingUsersGivenDoc(int docId);
    int addToWorkingUsers(int docId, int userId, int open_new);
    int removeFromWorkingUsers(int docId, int userId);      // da implementare e da usare
signals:
    void error(QTcpSocket::SocketError socketError);
    void testNotifica();

public slots:
    void executeJob();
    void receiveNotifica();

};

#endif // THREAD_BODY_H
