#include "../gimpdocs.h"
#include "gui_connectionToServerWrapper.h"

#include <QMessageBox>

/*USERS*/

int GUI_ConnectionToServerWrapper::requestLoginWrapper(GIMPdocs *gimpdocs, QString username, QString password){
    int returnValue;

    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        returnValue = Stub::requestTryLoginTemporary(gimpdocs->getConnection(), username, password);
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        //provo a ristabilire la connessione, e se non ci riesco ci riprovo finchè non ci riesco, o finchè l'utente non si arrende
        GUI_Reconnection::GUI_ReconnectionWrapper(gimpdocs);
        return requestLoginWrapper(gimpdocs, username, password);
    } catch(GUI_GenericException &exception){
        gimpdocs->setCursor(Qt::ArrowCursor);
        QMessageBox::information(gimpdocs, "", exception.message);
        return -1;
    }

    return returnValue;
}

int GUI_ConnectionToServerWrapper::requestLogoutWrapper(GIMPdocs *gimpdocs, int userId){
    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        Stub::requestTryLogOutTemporary(gimpdocs->getConnection(), userId);
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        //provo a ristabilire la connessione
        GUI_Connecting::GUI_ConnectingWrapper(gimpdocs);
        return -1;
    } catch(GUI_GenericException &exception){
        gimpdocs->setCursor(Qt::ArrowCursor);
        QMessageBox::information(gimpdocs, "", exception.message);
        return -1;
    }

    return 1;
}

int GUI_ConnectionToServerWrapper::requestDefinitiveLogoutWrapper(GIMPdocs *gimpdocs, int userId){
    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        Stub::requestTryLogOutTemporary(gimpdocs->getConnection(), userId);
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        //provo a ristabilire la connessione
        GUI_Connecting::GUI_ConnectingWrapper(gimpdocs);
        return -1;
    } catch(GUI_GenericException &exception){
        gimpdocs->setCursor(Qt::ArrowCursor);
        QMessageBox::information(gimpdocs, "", exception.message);
        //non ritorno -1, altrimenti sono soggetto a loop infiniti. Lascio che il client si chiuda e prima o poi il server se ne accorgerà
    }

    return 1;
}

int GUI_ConnectionToServerWrapper::requestNewAccountWrapper(GIMPdocs *gimpdocs, QString username, QString password, QString nickname, QString icon){
    int returnValue;

    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        returnValue = Stub::requestNewAccountTemporary(gimpdocs->getConnection(), username, password, nickname, icon);
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        //provo a ristabilire la connessione
        GUI_Connecting::GUI_ConnectingWrapper(gimpdocs);
        return -1;
    } catch(GUI_GenericException &exception){
        gimpdocs->setCursor(Qt::ArrowCursor);
        QMessageBox::information(gimpdocs, "", exception.message);
        return -1;
    }

    return returnValue;
}

int GUI_ConnectionToServerWrapper::requestUpdateAccountWrapper(GIMPdocs *gimpdocs, int userId, QString password, QString nickname, QString icon){
    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        Stub::requestUpdateAccountTemporary(gimpdocs->getConnection(), userId, password, nickname, icon);
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        //provo a ristabilire la connessione
        GUI_Connecting::GUI_ConnectingWrapper(gimpdocs);
        return -1;
    } catch(GUI_GenericException &exception){
        gimpdocs->setCursor(Qt::ArrowCursor);
        QMessageBox::information(gimpdocs, "", exception.message);
        return -1;
    }

    return 1;
}

QString GUI_ConnectionToServerWrapper::requestGetNicknameWrapper(GIMPdocs *gimpdocs, int userId){
    QString returnValue;

    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        returnValue = Stub::requestGetNicknameTemporary(gimpdocs->getConnection(), userId);
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        //provo a ristabilire la connessione
        GUI_Connecting::GUI_ConnectingWrapper(gimpdocs);
        return "errore";
    } catch(GUI_GenericException &exception){
        gimpdocs->setCursor(Qt::ArrowCursor);
        QMessageBox::information(gimpdocs, "", exception.message);
        return "errore";
    }

    return returnValue;
}

QString GUI_ConnectionToServerWrapper::requestGetUsernameWrapper(GIMPdocs *gimpdocs, int userId){
    QString returnValue;

    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        returnValue = Stub::requestGetUsernameTemporary(gimpdocs->getConnection(), userId);
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        //provo a ristabilire la connessione
        GUI_Connecting::GUI_ConnectingWrapper(gimpdocs);
        return "errore";
    } catch(GUI_GenericException &exception){
        gimpdocs->setCursor(Qt::ArrowCursor);
        QMessageBox::information(gimpdocs, "", exception.message);
        return "errore";
    }

    return returnValue;
}

QString GUI_ConnectionToServerWrapper::requestGetIconIdWrapper(GIMPdocs *gimpdocs, int userId){
    QString returnValue;

    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        returnValue = Stub::requestIconIdTemporary(gimpdocs->getConnection(), userId);
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        //provo a ristabilire la connessione
        GUI_Connecting::GUI_ConnectingWrapper(gimpdocs);
        return "errore";
    } catch(GUI_GenericException &exception){
        gimpdocs->setCursor(Qt::ArrowCursor);
        QMessageBox::information(gimpdocs, "", exception.message);
        return "errore";
    }

    return returnValue;
}



/*DOCUMENTS*/

std::shared_ptr<QMap<int, QString>> GUI_ConnectionToServerWrapper::requestGetKnownDocumentsWrapper(GIMPdocs *gimpdocs, int userId){
    std::shared_ptr<QMap<int, QString>> mpointer = nullptr;

    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        mpointer = Stub::getKnownDocumentsTemporary(gimpdocs->getConnection(), userId);
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        //provo a ristabilire la connessione
        GUI_Connecting::GUI_ConnectingWrapper(gimpdocs);
        return nullptr;
    } catch(GUI_GenericException &exception){
        gimpdocs->setCursor(Qt::ArrowCursor);
        QMessageBox::information(gimpdocs, "", exception.message);
        return nullptr;
    }

    return mpointer;
}

QString GUI_ConnectionToServerWrapper::requestCreateDocumentWrapper(GIMPdocs *gimpdocs, int userId, QString name){
    QString returnValue;

    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        returnValue = Stub::requestCreateDocumentTemporary(gimpdocs->getConnection(), userId, name);
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        //provo a ristabilire la connessione
        GUI_Connecting::GUI_ConnectingWrapper(gimpdocs);
        return "errore";
    } catch(GUI_GenericException &exception){
        gimpdocs->setCursor(Qt::ArrowCursor);
        QMessageBox::information(gimpdocs, "", exception.message);
        return "errore";
    }

    return returnValue;
}

int GUI_ConnectionToServerWrapper::requestDeleteDocumentWrapper(GIMPdocs *gimpdocs, int userId, int documentId){

    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        Stub::requestDeleteDocTemporary(gimpdocs->getConnection(), userId, documentId);
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        //provo a ristabilire la connessione
        GUI_Connecting::GUI_ConnectingWrapper(gimpdocs);
        return -1;
    }  catch(GUI_GenericException &exception){
        gimpdocs->setCursor(Qt::ArrowCursor);
        QMessageBox::information(gimpdocs, "", exception.message);
        return -1;
    }

    return 1;
}

QString GUI_ConnectionToServerWrapper::requestOpenDocumentWrapper(GIMPdocs *gimpdocs, int userId, int documentId){
    QString returnValue;

    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        returnValue = Stub::openDocTemporary(gimpdocs->getConnection(), userId, documentId);
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        //provo a ristabilire la connessione
        GUI_Connecting::GUI_ConnectingWrapper(gimpdocs);
        return "errore";
    } catch(GUI_GenericException &exception){
        gimpdocs->setCursor(Qt::ArrowCursor);
        QMessageBox::information(gimpdocs, "", exception.message);
        return "errore";
    }

    return returnValue;
}

int GUI_ConnectionToServerWrapper::requestCloseDocumentWrapper(GIMPdocs *gimpdocs, int userId, int docId){
    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        Stub::closeDocumentTemporary(gimpdocs->getConnection(), userId, docId);
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        //provo a ristabilire la connessione
        GUI_Connecting::GUI_ConnectingWrapper(gimpdocs);
        return -1;
    } catch(GUI_GenericException &exception){
        gimpdocs->setCursor(Qt::ArrowCursor);
        QMessageBox::information(gimpdocs, "", exception.message);
        return -1;
    }

    //è solo per dire che è andato tutto bene
    return 1;
}


QString GUI_ConnectionToServerWrapper::requestDocumentDatoUriWrapper(GIMPdocs *gimpdocs, int userId, QString uri){
    QString returnValue;

    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        returnValue = Stub::requestDocDatoUriTemporary(gimpdocs->getConnection(), userId, uri);
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        //provo a ristabilire la connessione
        GUI_Connecting::GUI_ConnectingWrapper(gimpdocs);
        return "errore";
    } catch(GUI_GenericException &exception){
        gimpdocs->setCursor(Qt::ArrowCursor);
        QMessageBox::information(gimpdocs, "", exception.message);
        return "errore";
    }

    return returnValue;
}


/*DOCUMENT PROPERTIES*/

QString GUI_ConnectionToServerWrapper::requestUriWrapper(GIMPdocs *gimpdocs, int docId){
    QString returnValue;

    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        returnValue = Stub::requestUriTemporary(gimpdocs->getConnection(), docId);
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        //provo a ristabilire la connessione
        GUI_Connecting::GUI_ConnectingWrapper(gimpdocs);
        return "errore";
    } catch(GUI_GenericException &exception){
        gimpdocs->setCursor(Qt::ArrowCursor);
        QMessageBox::information(gimpdocs, "", exception.message);
        return "errore";
    }

    return returnValue;
}

QString GUI_ConnectionToServerWrapper::requestDocumentNameWrapper(GIMPdocs *gimpdocs, int docId){
    QString returnValue;

    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        returnValue = Stub::requestDocNameTemporary(gimpdocs->getConnection(), docId);
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        //provo a ristabilire la connessione
        GUI_Connecting::GUI_ConnectingWrapper(gimpdocs);
        return "errore";
    } catch(GUI_GenericException &exception){
        gimpdocs->setCursor(Qt::ArrowCursor);
        QMessageBox::information(gimpdocs, "", exception.message);
        return "errore";
    }

    return returnValue;
}

int GUI_ConnectionToServerWrapper::requestDocumentOwnerWrapper(GIMPdocs *gimpdocs, int docId){
    int returnValue;

    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        returnValue = Stub::getDocumentOwnerTemporary(gimpdocs->getConnection(), docId);
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        //provo a ristabilire la connessione
        GUI_Connecting::GUI_ConnectingWrapper(gimpdocs);
        return -1;
    } catch(GUI_GenericException &exception){
        gimpdocs->setCursor(Qt::ArrowCursor);
        QMessageBox::information(gimpdocs, "", exception.message);
        return -1;
    }

    return returnValue;
}

std::shared_ptr<QTextEdit> GUI_ConnectionToServerWrapper::getDocumentTextWrapper(GIMPdocs *gimpdocs, int docId, int userId){

    std::shared_ptr<QTextEdit> docpointer;

    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        docpointer = Stub::getDocumentText(gimpdocs->getConnection(), docId, userId);
        //Stub::getDocumentText(gimpdocs->getConnection(), docId, userId, filename);
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        //provo a ristabilire la connessione
        GUI_Connecting::GUI_ConnectingWrapper(gimpdocs);
        return nullptr;
    } catch(GUI_GenericException &exception){
        gimpdocs->setCursor(Qt::ArrowCursor);
        QMessageBox::information(gimpdocs, "", exception.message);
        return nullptr;
    }

    return docpointer;
}


/*EDITOR*/

std::shared_ptr<QSet<int>> GUI_ConnectionToServerWrapper::getWorkingUsersOnDocumentWrapper(GIMPdocs *gimpdocs, int docId){
    std::shared_ptr<QSet<int>> users;

    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        users = Stub::getWorkingUsersOnDocumentTemporary(gimpdocs->getConnection(), docId);
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        //provo a ristabilire la connessione
        GUI_Connecting::GUI_ConnectingWrapper(gimpdocs);
        return nullptr;
    } catch(GUI_GenericException &exception){
        gimpdocs->setCursor(Qt::ArrowCursor);
        QMessageBox::information(gimpdocs, "", exception.message);
        return nullptr;
    }

    return users;
}

std::shared_ptr<QSet<int>> GUI_ConnectionToServerWrapper::getContributorsUsersOnDocumentWrapper(GIMPdocs *gimpdocs, int docId){
    std::shared_ptr<QSet<int>> contributors;

    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        contributors = Stub::getContributorsTemporary(gimpdocs->getConnection(), docId);
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        //provo a ristabilire la connessione
        GUI_Connecting::GUI_ConnectingWrapper(gimpdocs);
        return nullptr;
    } catch(GUI_GenericException &exception){
        gimpdocs->setCursor(Qt::ArrowCursor);
        QMessageBox::information(gimpdocs, "", exception.message);
        return nullptr;
    }

    return contributors;
}

int GUI_ConnectionToServerWrapper::requestStartEditorConnection(GIMPdocs *gimpdocs){
    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        Stub::startEditorConnectionTemporary(gimpdocs->getConnection());
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        //provo a ristabilire la connessione
        GUI_Connecting::GUI_ConnectingWrapper(gimpdocs);
        return -1;
    } catch(GUI_GenericException &exception){
        gimpdocs->setCursor(Qt::ArrowCursor);
        QMessageBox::information(gimpdocs, "", exception.message);
        return -1;
    }

    return 1;
}
