#include "stub.h"
#include <QVector>
#include <QSet>

Stub::Stub(QObject *parent) : QObject(parent)
{

}

bool Stub::isConnectionWorking(){
    return false;
}

/*USERS*/
int Stub::requestTryLoginTemporary(connection_to_server *connection, QString username, QString password){
    int result = connection->requestTryLogin(username, password);

    if(result < 0)
        //per ora ne tiro una a caso, ma la funzione requestTryLogin dovrà tirare quella appropriata
        //throw GUI_ConnectionException();
        throw GUI_GenericException("Houston, abbiamo un problema");

    return result;
}

int Stub::requestNewAccountTemporary(connection_to_server *connection, QString username, QString password, QString nickname, QString iconId){
    int result = connection->requestNewAccount(username,password, nickname, iconId);

    if(result < 0)
        //throw GUI_ConnectionException();
        throw GUI_GenericException("Houston, abbiamo un problema");

    return result;
}

int Stub::requestUpdateAccountTemporary(connection_to_server *connection, int userId, QString password, QString nickname, QString icon){
    int result = connection->requestUpdateAccount(userId, password, nickname, icon);

    if(result < 0)
        //throw GUI_ConnectionException();
        throw GUI_GenericException("Houston, abbiamo un problema");

    return result;
}

std::string Stub::requestGetNicknameTemporary(connection_to_server *connection, int userId){
    std::string result = connection->requestGetNickname(userId);

    if(result.compare("errore") == 0)
        //throw GUI_ConnectionException();
        throw GUI_GenericException("Houston, abbiamo un problema");

    return result;
}

std::string Stub::requestGetUsernameTemporary(connection_to_server *connection, int userId){
    std::string result = connection->requestGetUsername(userId);

    if(result.compare("errore") == 0)
        //throw GUI_ConnectionException();
        throw GUI_GenericException("Houston, abbiamo un problema");

    return result;
}

std::string Stub::requestIconIdTemporary(connection_to_server *connection, int userId){
    std::string result = connection->requestIconId(userId);

    if(result.compare("errore") == 0)
        //throw GUI_ConnectionException();
        throw GUI_GenericException("Houston, abbiamo un problema");

    return result;
}

QString Stub::getPassword(long userid){
    if(userid < 0)
        return "";

    if(userid == 1)
        return "Montruschio";

    return "Boh";
}




/*DOCUMENT*/
long Stub::requestCreateDocumentTemporary(connection_to_server *connection, int userId, QString name){
    long result = connection->requestCreateDocument(userId, name);

    if(result < 0)
        //throw GUI_ConnectionException();
        throw GUI_GenericException("Houston, abbiamo un problema");

    return result;
}

int Stub::forgetDocumentWithName(long userId, QString docname){
    int docId = userId;;
    userId = docId;
    QString pippo = docname;

    //I don't know. Do something
    return 0;
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

std::string Stub::requestDocDatoUriTemporary(connection_to_server *connection, QString uri){
    std::string result = connection->requestDocDatoUri(uri);

    if(result.compare("errore") == 0)
        //throw GUI_ConnectionException();
        throw GUI_GenericException("Houston, abbiamo un problema");

    return result;
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



std::string Stub::requestUriTemporary(connection_to_server *connection, long docId){
    std::string result = connection->requestUri(docId);

    if(result.compare("errore") == 0)
        //throw GUI_ConnectionException();
        throw GUI_GenericException("Houston, abbiamo un problema");

    return result;
}

long Stub::getDocumentId(QString name){
    QString pippo = name;
     return 1;
}

QString Stub::getDocumentName(long docId){
    long n = docId;
    docId = n;

    return "The Tales of Beedle the Bard";
}

std::shared_ptr<QTextDocument> Stub::getDocumentText(){
    std::shared_ptr<QTextDocument> docpointer(new QTextDocument());
    docpointer->setHtml("<h1>Hello, World!</h1>\n<p>Sopra la panca la capra studia. Sotto la panca la capra studia</p>");

    return docpointer;
}



/*EDITOR*/
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


