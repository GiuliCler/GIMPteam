#ifndef CRDT_MESSAGE_H
#define CRDT_MESSAGE_H

#include <QObject>
#include <string>
#include <vector>
#include "crdt_symbol.h"

class CRDT_Symbol;

class CRDT_Message : public QObject
{
private:
    std::string azione;
    CRDT_Symbol simbolo;
    int creatore;

public:
    CRDT_Message(std::string str, CRDT_Symbol s, int id);
    std::string getAzione() const;
    CRDT_Symbol getSimbolo() const;
    int getCreatore() const;
};

#endif // CRDT_MESSAGE_H
