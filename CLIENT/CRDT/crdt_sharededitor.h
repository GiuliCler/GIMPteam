#ifndef CRDT_SHAREDEDITOR_H
#define CRDT_SHAREDEDITOR_H

#include <QChar>
#include <QTextCharFormat>
#include <QVector>
#include <QVectorIterator>
//#include "NetworkServer.h"
#include "crdt_symbol.h"
#include <string>

class CRDT_controller;
class CRDT_Message;

class CRDT_SharedEditor
{
private:
    CRDT_controller *parent;
//    NetworkServer& _server;
    int _siteId;
    QVector<CRDT_Symbol> _symbols;
    int _counter;
    QVector<int> generaPosizione(QVector<int> prev, QVector<int> next);
    QVector<CRDT_Symbol>::iterator trovaPosizione(QVector<int> pos);
    int confrontaPos(QVector<int> pos, QVector<int> currentPos);

public:
    explicit CRDT_SharedEditor(CRDT_controller *parent/*, NetworkServer& s*/);
    int getSiteId() const;
//    std::string print();
    void localInsert(int index, QChar value, QTextCharFormat fmt, Qt::Alignment align);
    void localErase(int index);
    void process(const CRDT_Message& m);
    int getLength();
//    std::string to_string();
};

#endif // CRDT_SHAREDEDITOR_H
