#ifndef CRDT_SHAREDEDITOR_H
#define CRDT_SHAREDEDITOR_H

#include <QChar>
#include <QTextCharFormat>
#include <QVector>
#include <QVectorIterator>
#include "crdt_symbol.h"
#include <string>

class CRDT_controller;
class CRDT_Message;
class connection_to_server;

class CRDT_SharedEditor: public QObject
{
    Q_OBJECT
private:
    CRDT_controller *parent;
    connection_to_server *connection;
    int _siteId;
    QVector<CRDT_Symbol> _symbols;
    int _counter;
    QVector<int> generaPosizione(QVector<int> prev, QVector<int> next);
    QVector<CRDT_Symbol>::iterator trovaPosizione(QVector<int> pos);
    int confrontaPos(QVector<int> pos, QVector<int> currentPos);

public:
    explicit CRDT_SharedEditor(CRDT_controller *parent, connection_to_server *connection, int siteId, int siteCounter);
    int getSiteId() const;
    std::string print();            // FUNZIONI PER IL DEBUG
    void localInsert(int index, QChar value, QTextCharFormat fmt, Qt::Alignment align);
    void localErase(int index);
    int getLength();
    std::string to_string();        // FUNZIONI PER IL DEBUG

public slots:
    void process(const CRDT_Message& m);
};

#endif // CRDT_SHAREDEDITOR_H
