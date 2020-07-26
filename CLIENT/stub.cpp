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





/*DOCUMENT*/
int Stub::requestCreateDocumentTemporary(connection_to_server *connection, int userId, QString name){
    int result = connection->requestCreateDocument(userId, name);

    if(result < 0)
        //throw GUI_ConnectionException();
        throw GUI_GenericException("Houston, abbiamo un problema");

    return result;
}

void Stub::forgetKnownDocument(connection_to_server *connection, int userId, int documentId){
    userId = documentId;
    documentId = userId;

    std::string result = connection->requestDeleteDoc(userId, documentId);

    //lancia un errore solo se non riesce ad eliminare il documento
    if(result.compare("errore") == 0)
        //throw GUI_ConnectionException();
        throw GUI_GenericException("Houston, abbiamo un problema");
}

std::shared_ptr<QMap<int, QString>> Stub::getKnownDocuments(int userId){
    int n = userId;
    userId = n;

    std::shared_ptr<QMap<int, QString>> vpointer(new QMap<int, QString>());
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

void Stub::openKnownDocument(int documentId){
    int n =documentId;
    documentId = n;

}

void Stub::closeDocument(int userId, int docId){
    userId = docId;
    docId = userId;

    //I don't know. Do something
}



std::string Stub::requestUriTemporary(connection_to_server *connection, int docId){
    std::string result = connection->requestUri(docId);

    if(result.compare("errore") == 0)
        //throw GUI_ConnectionException();
        throw GUI_GenericException("Houston, abbiamo un problema");

    return result;
}

std::string Stub::getDocumentName(connection_to_server *connection,int docId){
    int n = docId;
    docId = n;
    std::string name = connection->requestDocName(docId);

    if(name.compare("errore") == 0)
        //throw GUI_ConnectionException();
        throw GUI_GenericException("Houston, abbiamo un problema");

    return name;
}

std::shared_ptr<QTextDocument> Stub::getDocumentText(int docId){
    int n = docId;
    docId = n;

    std::shared_ptr<QTextDocument> docpointer(new QTextDocument());
    docpointer->setHtml("<h1>Hello, World!</h1>\n<p>Sopra la panca la capra studia. Sotto la panca la capra studia</p>");

    return docpointer;
}



/*EDITOR*/
//uso un set perchè mi scanso più avanti controlli sull'unicità dello userId, che dovrebbe essere già garanita, ma non si sa mai
std::shared_ptr<QSet<int>> Stub::getWorkingUsersOnDocument(connection_to_server *connection, int docId){
    int n = docId;
    docId = n;

    std::shared_ptr<QSet<int>> vpointer = connection->getWorkingUsersOnDocument(docId);

    return vpointer;
}

std::shared_ptr<QSet<int>> Stub::getContributorsUsersOnDocument(int docId){
    int n = docId;
    docId = n;
    std::shared_ptr<QSet<int>> vpointer(new QSet<int>());
    for(int i = 3; i < 6; i++)
        vpointer->insert(i);

    return vpointer;
}

void Stub::Editor(connection_to_server *connection, int docId){
    connection->setEditor(docId);
    return;
}
