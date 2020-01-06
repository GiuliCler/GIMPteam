#ifndef CRDT_SYMBOL_H
#define CRDT_SYMBOL_H

#include <QChar>
#include <QTextCharFormat>
#include <QVector>
#include <string>

class CRDT_Symbol
{
private:
    QChar carattere;
    std::string id;
    QVector<int> posizione;
    QTextCharFormat format;
    Qt::Alignment align;

public:

    CRDT_Symbol();
    CRDT_Symbol(QChar car, int clientID, int num, QVector<int> vet, QTextCharFormat fmt, Qt::Alignment align);
    QChar getCarattere() const;
    QTextCharFormat getFormat() const;
    Qt::Alignment getAlignment() const;
    std::string getIDunivoco()const;
    QVector<int> getPosizione() const;
};

#endif // CRDT_SYMBOL_H
