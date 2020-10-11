#ifndef CRDT_SHAREDEDITOR_H
#define CRDT_SHAREDEDITOR_H

#include <QChar>
#include <QTextCharFormat>
#include <QVector>
#include <QVectorIterator>
#include "connection_to_server.h"
#include "crdt_symbol.h"
#include <string>

class CRDT_controller;
class CRDT_Message;

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
//    std::string print();            // FUNZIONI PER IL DEBUG
    QVector<int> generaPrimaPosizione(int index);
    void localFirstInsert(int index, QChar value, QTextCharFormat fmt, Qt::Alignment align, QVector<int> posizione, int insertSize);
    void localInsert(int index, QChar value, QTextCharFormat fmt, Qt::Alignment align, QVector<int> posizione);
    void localMultipleErase(int index, int eraseSize);
    int getLength();
//    std::string to_string();        // FUNZIONI PER IL DEBUG
    Qt::Alignment getAlignAt(int pos);
    int getSiteIdAt(int pos);
    void processBuffer(int userId);

private slots:
    void process(const CRDT_Message& m);
};

#endif // CRDT_SHAREDEDITOR_H
