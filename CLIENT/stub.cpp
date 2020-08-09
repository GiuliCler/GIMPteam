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

int Stub::requestTryLogOutTemporary(connection_to_server *connection, int userId){
    int result = connection->requestTryLogOut(userId);

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

QString Stub::requestGetNicknameTemporary(connection_to_server *connection, int userId){
    QString result = QString::fromStdString(connection->requestGetNickname(userId));

    if(result.compare("errore") == 0)
        //throw GUI_ConnectionException();
        throw GUI_GenericException("Houston, abbiamo un problema");

    return result;
}

QString Stub::requestGetUsernameTemporary(connection_to_server *connection, int userId){
    QString result = QString::fromStdString(connection->requestGetUsername(userId));

    if(result.compare("errore") == 0)
        //throw GUI_ConnectionException();
        throw GUI_GenericException("Houston, abbiamo un problema");

    return result;
}

QString Stub::requestIconIdTemporary(connection_to_server *connection, int userId){
    QString result = QString::fromStdString(connection->requestIconId(userId));

    if(result.compare("errore") == 0)
        //throw GUI_ConnectionException();
        throw GUI_GenericException("Houston, abbiamo un problema");

    return result;
}





/*DOCUMENT*/
QString Stub::requestCreateDocumentTemporary(connection_to_server *connection, int userId, QString name){
    QString result = QString::fromStdString(connection->requestCreateDocument(userId, name));

    if(result.compare("errore") == 0)
        //throw GUI_ConnectionException();
        throw GUI_GenericException("Houston, abbiamo un problema");

    return result;
}

void Stub::forgetKnownDocumentTemporary(connection_to_server *connection, int userId, int documentId){
    std::string result = connection->requestDeleteDoc(userId, documentId);

    if(result.compare("errore") == 0)
        //throw GUI_ConnectionException();
        throw GUI_GenericException("Houston, abbiamo un problema");
}

std::shared_ptr<QMap<QString, int>> Stub::getKnownDocumentsTemporary(connection_to_server *connection, int userId){
    std::shared_ptr<QMap<QString, int>> vpointer = connection->getKnownDocuments(userId);

    if(vpointer == nullptr)
        //throw GUI_ConnectionException();
        throw GUI_GenericException("Houston, abbiamo un problema");

    return vpointer;
}

QString Stub::requestDocDatoUri(connection_to_server *connection, int userId, QString uri){
    //come al solito è solo per togleire i warning
    int n = userId;
    userId = n;

    QString result = QString::fromStdString(connection->requestDocDatoUri(uri, userId));

    if(result.compare("errore") == 0)
        //throw GUI_ConnectionException();
        throw GUI_GenericException("Houston, abbiamo un problema");

    return result;
}

QString Stub::requestUriTemporary(connection_to_server *connection, int docId){
    QString result = QString::fromStdString(connection->requestUri(docId));

    if(result.compare("errore") == 0)
        //throw GUI_ConnectionException();
        throw GUI_GenericException("Houston, abbiamo un problema");

    return result;
}

QString Stub::requestDocNameTemporary(connection_to_server *connection,int docId){
    QString name = QString::fromStdString(connection->requestDocName(docId));

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

int Stub::requestDocumentOwner(connection_to_server *connection, int docId){
    int userId = connection->getDocumentOwner(docId);
    // NOTA: ritorna userId = -1 in caso di errore
    return userId;
}



/*EDITOR*/
//uso un set perchè mi scanso più avanti controlli sull'unicità dello userId, che dovrebbe essere già garanita, ma non si sa mai
std::shared_ptr<QSet<int>> Stub::getWorkingUsersOnDocumentTemporary(connection_to_server *connection, int docId){
    std::shared_ptr<QSet<int>> vpointer = connection->getWorkingUsersOnDocument(docId);

    return vpointer;
}

std::shared_ptr<QSet<int>> Stub::getContributorsUsersOnDocument(connection_to_server *connection, int docId){
    int n = docId;
    docId = n;

    std::shared_ptr<QSet<int>> vpointer(new QSet<int>());
    vpointer = connection->getContributors(docId);
    return vpointer;
}

void Stub::Editor(connection_to_server *connection){
    connection->connectEditor();
}

void Stub::closeDocument(connection_to_server *connection, int userId, int docId){
    connection->disconnectEditor(userId, docId);
}

QString Stub::openKnownDocument(connection_to_server *connection, int userId, int documentId){
    QString name = QString::fromStdString(connection->openDoc(userId, documentId));

    if(name.compare("errore") == 0)
        //throw GUI_ConnectionException();
        throw GUI_GenericException("Houston, abbiamo un problema");

    return name;
}
