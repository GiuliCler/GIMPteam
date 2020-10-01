#ifndef THREAD_BODY_H
#define THREAD_BODY_H

#include <QObject>
#include <QTcpSocket>
#include "database/collegamentoDB.h"
#include <QMutex>
#include "crdt/crdt_message.h"
#include "crdt/crdt_symbol.h"
#include "crdt/crdt_servereditor.h"

extern QMutex* mutex_users;
extern QMutex* mutex_docs;
extern QMutex* mutex_workingUsers;
extern QMutex* mutex_db;
extern QMutex* mutex_logged_users;
extern QMutex* mutex_files;

extern QMap<QString, int> users;
extern QMap<QString, int> documents;
extern QVector<QString> logged_users;
extern QMap<int, QVector<int>> workingUsers;
extern QMap<int, std::shared_ptr<CRDT_ServerEditor>> files;
extern QString path;

class Thread_body : public QObject
{
    Q_OBJECT
public:
    explicit Thread_body(int socketDescriptor, QThread* server, QObject *parent = nullptr);
    ~Thread_body();
    QTcpSocket* socket;

private:
    QThread* server;
    const int Timeout = 100 * 1000;
    CollegamentoDB database;
    int current_siteCounter;
    int current_docId;
    int current_userId;
    std::shared_ptr<CRDT_ServerEditor> crdt;
    QByteArray readBuffer;
    qint32 readBuffer_size;

    QString getUsername(int userId);
    QString getDocname(int docId);
    QString threadId_toQString(std::thread::id id);
    void stampaLoggedUsers();
    bool isLogged(QString username);
    void signup(QString username, QString password, QString nickname, QString icon);
    void login(QString username, QString password);
    void getDocText(int docId, int userId);
    void logout(int userId);
    void update(int userId, QString password, QString nickname, QString icon);
    void retrieveUsername(int userId);
    void getNickname(int userId);
    void getIcon(int userId);
    void getDocs(int userId);
    void newDoc(QString docName, int userId);
    void getDocIdDatoUri(QString uri, int userId);
    void getUri(int docId);
    void getOwnerId(int docId);
    void retrieveDocName(int docId);
    void deleteDoc(int userId, int docId);
    void openDocument(int docId, int userId);
    int openDoc(QString docName, int docId, int userId, int new_doc);
    void closeDocument(int docId, int userId);
    void getWorkingUsersGivenDoc(int docId);
    void getCollaboratorsGivenDoc(int docId);
    void notifyNewWorkingUser(int userId, int docId);
    void notifyWorkingUserAway(int userId, int docId);
    void notifyNewContributor(int userId, int docId);
    void sendEndBuffer();
    int addToWorkingUsers(int docId, int userId, int open_new);
    bool removeFromWorkingUsers(int docId, int userId);
    void forceCloseDocument(int docId_deleted);
    void moveCursor(int userId, int pos);
    void stopCursor();
    void startCursor();
    static qint32 ArrayToInt(QByteArray source);
    bool writeData(QByteArray data);
    static QByteArray IntToArray(qint32 source);


signals:
    void error(QTcpSocket::SocketError socketError);
    void messageToServer(CRDT_Message m, QString thread_id_sender, int docId);
    void finished();
    void dataReceived(QByteArray data);

public slots:
    void readData();
    void executeJob(QByteArray data);
    void processMessage(CRDT_Message m, QString thread_id_sender, int docId);
    void checkPeriodicoClientConnessiSlot();

};

#endif // THREAD_BODY_H
