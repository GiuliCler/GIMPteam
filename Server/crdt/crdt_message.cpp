#include "crdt_message.h"
#include "crdt_symbol.h"

CRDT_Message::CRDT_Message(): azione("Braiiiiins"), simbolo(*new CRDT_Symbol()), creatore(7){};

CRDT_Message::CRDT_Message(std::string str, CRDT_Symbol s, int id): azione(str), simbolo(s), creatore(id){};

std::string CRDT_Message::getAzione() const{
    return this->azione;
}

CRDT_Symbol CRDT_Message::getSimbolo() const{
    return this->simbolo;
}

int CRDT_Message::getCreatore() const{
    return this->creatore;
}
