#ifndef THREAD_MANAGEMENT_H
#define THREAD_MANAGEMENT_H

#include "database/collegamentoDB.h"
#include "thread_body.h"
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QTcpSocket>
#include <QPair>

extern QMutex* mutex_users;
extern QMutex* mutex_docs;
extern QMutex* mutex_workingUsers;
extern QMutex* mutex_db;

extern QMap<QString, int> users;
extern QMap<QString, int> documents;
extern QMap<int, QVector<int>> workingUsers;
extern QString path;

class Thread_management : public QThread {
    Q_OBJECT
public:
    Thread_management(int socketDescriptor, QObject *parent);
    void run() override;
    QTcpSocket* socket;

private:
    CollegamentoDB *database;
    int socketDescriptor;

    Thread_body* body;

signals:

public slots:
    //    void disconnected();        // DA TOGLIERE POI
};

#endif // THREAD_MANAGEMENT_H
