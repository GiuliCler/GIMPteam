#include "stub.h"
#include <QVector>

Stub::Stub(QObject *parent) : QObject(parent)
{

}

long Stub::tryLogin(QString username, QString password){

    //l'assegnazione serve solo a togliere i warning
    username = password;
    password = username;

    return 1;
}

int Stub::getIconId(int userId){
    int n =userId;
    userId = n;

    return 1;
}

QString Stub::getNickname(long id){
    if(id < 0)
        return "";

    if(id == 1)
        return "Mew";

    return "Boh";
}

QString Stub::getUsername(long id){
    if(id < 0)
        return "";

    if(id == 1)
        return "Ancient Mew";

    return "Boh";
}

QString Stub::getPassword(long id){
    if(id < 0)
        return "";

    if(id == 1)
        return "Montruschio";

    return "Boh";
}

long Stub::createUser(QString username, QString password, QString nickname, int iconId){
    //tutte 'ste assegnazioni sono solo per togliere i warning
    username = password;
    password = nickname;
    int n = iconId;
    iconId = n;

    return 1;
}

int Stub::updateUser(long id, QString password, QString nickname, int iconId){
    //tutte 'ste assegnazioni sono solo per togliere i warning
    password = nickname;
    id = iconId;
    iconId = id;

    return 0;
}

long Stub::createDocument(int userId, QString name){
    int n = userId;
    userId = n;
    QString s = name;

    return 1;
}

long Stub::openWithURI(QString uri){
    QString s = uri;

    return 1;
}

long Stub::openWithName(QString name){
    QString s = name;

    return 1;
}

std::shared_ptr<QVector<QString>> Stub::getDocuments(long userId){
    long n = userId;
    userId = n;

    std::shared_ptr<QVector<QString>> vpointer(new QVector<QString>());
    //QVector<QString> vec;
    vpointer->insert(0, "United States Declaration of independence");
    vpointer->insert(1, "Magna Carta Libertatum");
    vpointer->insert(2, "Hammurabi's Code");
    vpointer->insert(3, "Domande e risposte di Security: appello gennaio 2020");

    return vpointer;
}
