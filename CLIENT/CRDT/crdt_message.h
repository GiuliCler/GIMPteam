#ifndef CRDT_MESSAGE_H
#define CRDT_MESSAGE_H

#include <string>
#include <vector>
#include "crdt_symbol.h"

class CRDT_Symbol;

class CRDT_Message
{
    friend QDataStream & operator<<(QDataStream &, const CRDT_Message &);
    friend QDataStream & operator>>(QDataStream &, CRDT_Message &);

private:
    std::string azione;
    CRDT_Symbol simbolo;
    int creatore;

public:
    CRDT_Message();
    CRDT_Message(std::string str, CRDT_Symbol s, int id);
    std::string getAzione() const;
    CRDT_Symbol getSimbolo() const;
    int getCreatore() const;
    void setAzione(std::string azione);
    void setSimbolo(CRDT_Symbol s);
    void setCreatore(int c);
};

Q_DECLARE_METATYPE(CRDT_Message)

#endif // CRDT_MESSAGE_H
