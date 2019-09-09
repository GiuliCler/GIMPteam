#include "stub.h"

Stub::Stub(QObject *parent) : QObject(parent)
{

}

long Stub::tryLogin(QString username, QString password){

    //l'assegnazione serve solo a togliere i warning
    username = password;
    password = username;

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

void Stub::updateUser(long id, QString password, QString nickname, int iconId){
    //tutte 'ste assegnazioni sono solo per togliere i warning
    password = nickname;
    id = iconId;
    iconId = id;
}
