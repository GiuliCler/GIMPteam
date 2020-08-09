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

void CRDT_Symbol::setCarattere(QChar c){
    this->carattere = c;
}

void CRDT_Symbol::setFormat(QTextCharFormat fmt){
    this->format = fmt;
}

void CRDT_Symbol::setAlignment(Qt::Alignment align){
    this->align = align;
}

void CRDT_Symbol::setIDunivoco(std::string str){
    this->id = str;
}

void CRDT_Symbol::setPosizione(QVector<int> pos){
    this->posizione = pos;
}

QDataStream& operator<<(QDataStream& s, const CRDT_Symbol& simb){
    QString str = QString::fromStdString(simb.getIDunivoco());
    s << simb.getCarattere() << str.toUtf8() << simb.getPosizione() << simb.getFormat() << simb.getAlignment();
    return s;
}

QDataStream& operator>>(QDataStream& s, CRDT_Symbol& simb){
    QChar carattere;
    QByteArray id;
    QVector<int> posizione;
    QTextCharFormat format;
    Qt::Alignment align;

    s >> carattere >> id >> posizione >> format >> align;

    simb.setCarattere(carattere);
    simb.setIDunivoco(id.toStdString());
    simb.setPosizione(posizione);
    simb.setFormat(format);
    simb.setAlignment(align);

    return s;
}
