#ifndef STUB_H
#define STUB_H

#include <QObject>

class Stub : public QObject
{
    Q_OBJECT
public:
    explicit Stub(QObject *parent = nullptr);
    static bool tryLogin(QString username, QString password);
};

#endif // STUB_H
