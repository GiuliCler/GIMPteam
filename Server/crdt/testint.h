#ifndef TESTINT_H
#define TESTINT_H

#include <QObject>

class TestInt : public QObject
{
    Q_OBJECT
public:
    explicit TestInt(QObject *parent = nullptr);
    int n = 5;

signals:
public slots:
    void print();
};

#endif // TESTINT_H
