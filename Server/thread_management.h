#ifndef THREAD_MANAGEMENT_H
#define THREAD_MANAGEMENT_H

#include "database/collegamentoDB.h"
#include "thread_body.h"
#include "crdt/crdt_servereditor.h"
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QTcpSocket>
#include <QPair>

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
extern QMap<int, CRDT_ServerEditor*> files;
extern QString path;


class Thread_management : public QThread {
    Q_OBJECT
public:
    Thread_management(int socketDescriptor, QObject *parent);
    ~Thread_management();
    void run() override;
    QTcpSocket* socket;

private:
    int socketDescriptor;
    Thread_body* body;
};

#endif // THREAD_MANAGEMENT_H
