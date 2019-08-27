#include "stub.h"

Stub::Stub(QObject *parent) : QObject(parent)
{

}

bool Stub::tryLogin(QString username, QString password){
    return true;
}
