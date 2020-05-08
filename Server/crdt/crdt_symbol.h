#ifndef CRDT_SYMBOL_H
#define CRDT_SYMBOL_H

#include <QChar>
#include <QTextCharFormat>
#include <QVector>
#include <string>

class CRDT_Symbol
{
    friend QDataStream & operator<<(QDataStream &, const CRDT_Symbol &);
    friend QDataStream & operator>>(QDataStream &, CRDT_Symbol &);

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
    void setCarattere(QChar c);
    void setFormat(QTextCharFormat fmt);
    void setAlignment(Qt::Alignment align);
    void setIDunivoco(std::string str);
    void setPosizione(QVector<int> pos);
};

#endif // CRDT_SYMBOL_H
