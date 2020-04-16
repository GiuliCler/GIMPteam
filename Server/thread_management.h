#ifndef THREAD_MANAGEMENT_H
#define THREAD_MANAGEMENT_H

#include "database/collegamentoDB.h"
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QTcpSocket>
#include <QPair>

//extern QVector<QPair<QString, int>> jobs;
//extern QWaitCondition* cv_jobs;
//extern QMutex* mutex_jobs;

extern QMutex* mutex_users;
extern QMutex* mutex_docs;
extern QMutex* mutex_db;

extern QMap<QString, int> users;
extern QMap<QString, int> documents;
extern QMap<int, std::vector<int>> online;

class Thread_management : public QThread {
    Q_OBJECT
public:
    Thread_management(int socketDescriptor, QObject *parent);
    void run() override;
    QTcpSocket* socket;

private:
    CollegamentoDB *database;
    int socketDescriptor;
    void create(QString username, QString password, QString nickname, QString icon);
    void login(QString username, QString password);
    void update(int userId, QString password, QString nickname, QString icon);
    void getUsername(int userId);
    void getNickname(int userId);
    void getIcon(int userId);
    void getDocs(int userId);
    void newDoc();                  // DA RIEMPIRE
    void getDocumentDatoUri();      // DA RIEMPIRE
    void getUri(int docId);

signals:
    void error(QTcpSocket::SocketError socketError);

public slots:
//    void executeJob();          // DA TOGLIERE POI
//    void disconnected();        // DA TOGLIERE POI
};

#endif // THREAD_MANAGEMENT_H
