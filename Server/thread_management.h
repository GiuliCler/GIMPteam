#ifndef THREAD_MANAGEMENT_H
#define THREAD_MANAGEMENT_H

#include "database/collegamentoDB.h"
#include <QThread>
#include <QMutex>
#include <QWaitCondition>

extern QVector<int> jobs;       // da cambiare
extern QWaitCondition* cv_jobs;
extern QMutex* mutex_jobs;

extern QMutex mutex_users;
extern QMutex mutex_docs;

extern CollegamentoDB *database;
extern QMap<QString, int> users;
extern QMap<QString, int> documents;
extern QMap<int, std::vector<int>> online;

class Thread_management : public QThread {
    Q_OBJECT
private:

protected:
    void run();

public:
    Thread_management();
};

#endif // THREAD_MANAGEMENT_H
