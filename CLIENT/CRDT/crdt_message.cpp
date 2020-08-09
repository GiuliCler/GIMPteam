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

void CRDT_Message::setAzione(std::string azione){
    this->azione = azione;
}

void CRDT_Message::setSimbolo(CRDT_Symbol s){
    this->simbolo = s;
}

void CRDT_Message::setCreatore(int c){
    this->creatore = c;
}

QDataStream& operator<<(QDataStream& s, const CRDT_Message& m){
    QString str = QString::fromStdString(m.getAzione());

    // Invio sul QDataStream gli oggetti nell'ordine:     QString --> CRDT_Symbol --> int
    s << str.toUtf8() << m.getSimbolo() << m.getCreatore();

    return s;
}

QDataStream& operator>>(QDataStream& s, CRDT_Message& m){
    QByteArray azione;
    CRDT_Symbol simbolo;
    int creatore;

    // Ricevo sul QDataStream gli oggetti nell'ordine:     QString --> CRDT_Symbol --> int
    s >> azione >> simbolo >> creatore;

    m.setAzione(azione.toStdString());
    m.setSimbolo(simbolo);
    m.setCreatore(creatore);

    return s;
}
