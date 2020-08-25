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
        throw GUI_ConnectionException();

    return result;
}

void Stub::requestTryLogOutTemporary(connection_to_server *connection, int userId){
    int result = connection->requestTryLogOut(userId);

    if(result < 0)
        throw GUI_ConnectionException();
        //throw GUI_GenericException("Connection Error.");
}

int Stub::requestNewAccountTemporary(connection_to_server *connection, QString username, QString password, QString nickname, QString iconId){
    int result = connection->requestNewAccount(username,password, nickname, iconId);

    if(result < 0)
        throw GUI_ConnectionException();
        //throw GUI_GenericException("Connection Error.");*/

    return result;
}

void Stub::requestUpdateAccountTemporary(connection_to_server *connection, int userId, QString password, QString nickname, QString icon){
    int result = connection->requestUpdateAccount(userId, password, nickname, icon);

    if(result < 0)
        throw GUI_ConnectionException();
        //throw GUI_GenericException("Connection Error.");
}

QString Stub::requestGetNicknameTemporary(connection_to_server *connection, int userId){
    QString result = QString::fromStdString(connection->requestGetNickname(userId));

    if(result.compare("errore") == 0)
        throw GUI_ConnectionException();
        //throw GUI_GenericException("Connection Error.");

    return result;
}

QString Stub::requestGetUsernameTemporary(connection_to_server *connection, int userId){
    QString result = QString::fromStdString(connection->requestGetUsername(userId));

    if(result.compare("errore") == 0)
        throw GUI_ConnectionException();
        //throw GUI_GenericException("Connection Error.");

    return result;
}

QString Stub::requestIconIdTemporary(connection_to_server *connection, int userId){
    QString result = QString::fromStdString(connection->requestIconId(userId));

    if(result.compare("errore") == 0)
        throw GUI_ConnectionException();
        //throw GUI_GenericException("Connection Error.");

    return result;
}





/*DOCUMENT*/
std::shared_ptr<QMap<QString, int>> Stub::getKnownDocumentsTemporary(connection_to_server *connection, int userId){
    std::shared_ptr<QMap<QString, int>> vpointer = connection->getKnownDocuments(userId);

    if(vpointer == nullptr)
        throw GUI_ConnectionException();
        //throw GUI_GenericException("Connection Error.");

    return vpointer;
}

QString Stub::requestCreateDocumentTemporary(connection_to_server *connection, int userId, QString name){
    //credo di stare ricevendo un malloppo di parametri stringati tutti assieme
    QString result = QString::fromStdString(connection->requestCreateDocument(userId, name));

    if(result.compare("errore") == 0)
        throw GUI_ConnectionException();
        //throw GUI_GenericException("Connection Error.");

    return result;
}

void Stub::requestDeleteDocTemporary(connection_to_server *connection, int userId, int documentId){
    std::string result = connection->requestDeleteDoc(userId, documentId);

    if(result.compare("errore") == 0)
        throw GUI_ConnectionException();
        //throw GUI_GenericException("Connection Error.");
}

QString Stub::openDocTemporary(connection_to_server *connection, int userId, int documentId){
    //anche qui sto ricevendo un malloppo di parametri stringati assieme
    QString name = QString::fromStdString(connection->openDoc(userId, documentId));

    if(name.compare("errore") == 0)
        throw GUI_ConnectionException();
        //throw GUI_GenericException("Connection Error.");

    return name;
}

void Stub::closeDocumentTemporary(connection_to_server *connection, int userId, int docId){
    connection->disconnectEditor(userId, docId);
}

QString Stub::requestDocDatoUriTemporary(connection_to_server *connection, int userId, QString uri){
    //anche qui sto ricevendo un malloppo di parametri stringati assieme
    QString result = QString::fromStdString(connection->requestDocDatoUri(uri, userId));

    if(result.compare("errore") == 0)
        throw GUI_ConnectionException();
        //throw GUI_GenericException("Connection Error.");

    return result;
}


/*DOCUMENT PROPERTIES*/

QString Stub::requestUriTemporary(connection_to_server *connection, int docId){
    QString result = QString::fromStdString(connection->requestUri(docId));

    if(result.compare("errore") == 0)
        throw GUI_ConnectionException();
        //throw GUI_GenericException("Connection Error.");

    return result;
}

QString Stub::requestDocNameTemporary(connection_to_server *connection,int docId){
    QString name = QString::fromStdString(connection->requestDocName(docId));

    if(name.compare("errore") == 0)
        throw GUI_ConnectionException();
        //throw GUI_GenericException("Connection Error.");

    return name;
}

std::shared_ptr<QTextDocument> Stub::getDocumentText(connection_to_server *connection, int docId, int userId){
    int n = docId;
    docId = n;

    //std::shared_ptr<QTextDocument> docpointer(new QTextDocument());
    //docpointer->setHtml("<h1>Hello, World!</h1>\n<p>Sopra la panca la capra studia. Sotto la panca la capra studia</p>");
    std::shared_ptr<QTextDocument> docpointer = connection->requestDocumentText(docId, userId);
    return docpointer;
}

int Stub::getDocumentOwnerTemporary(connection_to_server *connection, int docId){
    int result = connection->getDocumentOwner(docId);

    if(result < 0)
        throw GUI_ConnectionException();
        //throw GUI_GenericException("Connection Error.");

    return result;
}



/*EDITOR*/
//uso un set perchè mi scanso più avanti controlli sull'unicità dello userId, che dovrebbe essere già garanita, ma non si sa mai
std::shared_ptr<QSet<int>> Stub::getWorkingUsersOnDocumentTemporary(connection_to_server *connection, int docId){
    std::shared_ptr<QSet<int>> vpointer = connection->getWorkingUsersOnDocument(docId);

    if(vpointer == nullptr)
        throw GUI_ConnectionException();
        //throw GUI_GenericException("Connection Error.");

    return vpointer;
}

std::shared_ptr<QSet<int>> Stub::getContributorsTemporary(connection_to_server *connection, int docId){
    std::shared_ptr<QSet<int>> vpointer = connection->getContributors(docId);

    if(vpointer == nullptr)
        throw GUI_ConnectionException();
        //throw GUI_GenericException("Connection Error.");

    return vpointer;
}

void Stub::startEditorConnectionTemporary(connection_to_server *connection){
    connection->connectEditor();
}
