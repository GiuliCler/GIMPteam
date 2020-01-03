#ifndef CRDT_SHAREDEDITOR_H
#define CRDT_SHAREDEDITOR_H

#include <QObject>
//#include "NetworkServer.h"

class CRDT_Symbol;
class CRDT_Message;

class CRDT_SharedEditor : public QObject
{
private:
//    NetworkServer& _server;
    int _siteId;
    std::vector<CRDT_Symbol> _symbols;
    int _counter;
    std::vector<int> generaPosizione(std::vector<int> prev, std::vector<int> next);
    std::vector<CRDT_Symbol, std::allocator<CRDT_Symbol>>::iterator trovaPosizione(std::vector<int> pos);
    int confrontaPos(std::vector<int> pos,std::vector<int> currentPos);

public:
    explicit CRDT_SharedEditor(/*NetworkServer& s*/);
    int getSiteId() const;
    std::string print();
    void localInsert(int index, char value);
    void localErase(int index);
    void process(const CRDT_Message& m);
    std::string to_string();
};

#endif // CRDT_SHAREDEDITOR_H
