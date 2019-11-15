#include "stub.h"
#include <QVector>
#include <QSet>

Stub::Stub(QObject *parent) : QObject(parent)
{

}

long Stub::tryLogin(QString username, QString password){

    //l'assegnazione serve solo a togliere i warning
    username = password;
    password = username;

    return 1;
}

QString Stub::getIconId(long userId){
    int n =userId;
    userId = n;

    return "Mew.png";
}

QString Stub::getNickname(long userid){
    if(userid < 0)
        return "";

    return "Mew";
}

QString Stub::getUsername(long userid){
    if(userid < 0)
        return "";

    if(userid == 1)
        return "Ancient Mew";

    return "Boh";
}

QString Stub::getPassword(long userid){
    if(userid < 0)
        return "";

    if(userid == 1)
        return "Montruschio";

    return "Boh";
}

long Stub::createUser(QString username, QString password, QString nickname, QString iconId){
    //tutte 'ste assegnazioni sono solo per togliere i warning
    username = password;
    password = nickname;
    password = iconId;

    return 1;
}

int Stub::updateUser(long id, QString password, QString nickname, QString iconId){
    //tutte 'ste assegnazioni sono solo per togliere i warning
    password = nickname;
    password = iconId;
    int n = id;
    id = n;

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

void Stub::closeDocument(long userId, long docId){
    userId = docId;
    docId = userId;

    //I don't know. Do something
}

int Stub::forgetDocumentWithName(long userId, QString docname){
    int docId = userId;;
    userId = docId;
    QString pippo = docname;

    //I don't know. Do something
    return 0;
}

QString Stub::getDocumentURI(long docId){
    long n = docId;
    docId= n;

    return "httpippo";
}

long Stub::getDocumentId(QString name){
    QString pippo = name;
     return 1;
}

std::shared_ptr<QVector<QString>> Stub::getDocuments(long userId){
    long n = userId;
    userId = n;

    std::shared_ptr<QVector<QString>> vpointer(new QVector<QString>());
    vpointer->insert(0, "United States Declaration of independence");
    vpointer->insert(1, "Magna Carta Libertatum");
    vpointer->insert(2, "Hammurabi's Code");
    vpointer->insert(3, "Domande e risposte di Security: appello gennaio 2020");

    return vpointer;
}

//uso un set perchè mi scanso più avanti controlli sull'unicità dello userId, che dovrebbe essere già garanita, ma non si sa mai
std::shared_ptr<QSet<long>> Stub::getWorkingUsersOnDocument(long docId){
    long n = docId;
    docId = n;
    std::shared_ptr<QSet<long>> vpointer(new QSet<long>());
    for(int i = 0; i < 5; i++)
        vpointer->insert(i);

    return vpointer;
}

std::shared_ptr<QSet<long>> Stub::getContributorsUsersOnDocument(long docId){
    long n = docId;
    docId = n;
    std::shared_ptr<QSet<long>> vpointer(new QSet<long>());
    for(int i = 3; i < 6; i++)
        vpointer->insert(i);

    return vpointer;
}

QColor Stub::getCurrentTextColor(){
    return QColor(0,0,0,255);
}

void Stub::setCurrentTextColor(QColor color){
    //al solito, è per evitare i warnings
    QColor c = color;
    color = c;

    return;
}

std::shared_ptr<QTextDocument> Stub::getTextDocument(){
    std::shared_ptr<QTextDocument> docpointer(new QTextDocument());
    docpointer->setHtml("<h1>Hello, World!</h1>\n<p>Sopra la panca la capra studia. Sotto la panca la capra studia</p>");

    return docpointer;
}
