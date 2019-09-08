#include "stub.h"

Stub::Stub(QObject *parent) : QObject(parent)
{

}

bool Stub::tryLogin(QString username, QString password){

    //l'assegnazione serve solo a togliere i warning
    username = password;
    password = username;

    return true;
}

QString Stub::getNickname(){
    return "Mew";
}
