#include "crdt_symbol.h"

CRDT_Symbol::CRDT_Symbol() : carattere(), id("-1"), posizione(), format(), align(Qt::AlignLeft){}

CRDT_Symbol::CRDT_Symbol(QChar car, int clientID, int num, QVector<int> vet, QTextCharFormat fmt, Qt::Alignment align): carattere(car), posizione(vet), format(fmt), align(align){
    this->id = std::to_string(clientID) + "_" + std::to_string(num);
};

QChar CRDT_Symbol::getCarattere() const{
    return this->carattere;
}

QTextCharFormat CRDT_Symbol::getFormat() const{
    return this->format;
}

Qt::Alignment CRDT_Symbol::getAlignment() const{
    return this->align;
}

std::string CRDT_Symbol::getIDunivoco() const{
    return this->id;
}

QVector<int> CRDT_Symbol::getPosizione() const{
    return this->posizione;
}

QDataStream& operator<<(QDataStream& s, const CRDT_Symbol& simb){

    // todo paolo ----------------------------------------------------------------

    return s;
}

QDataStream& operator>>(QDataStream& s, CRDT_Symbol& simb){

    // todo paolo ----------------------------------------------------------------

    return s;
}
