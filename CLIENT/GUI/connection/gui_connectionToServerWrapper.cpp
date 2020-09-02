#include "../gimpdocs.h"
#include "gui_connectionToServerWrapper.h"
#include "gui_reconnection.h"

#include <QMessageBox>


bool GUI_ConnectionToServerWrapper::isConnectionWorking(GIMPdocs *gimpdocs){
    bool returnValue;

    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        returnValue = gimpdocs->getConnection()->pingServer();
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        handleReconnection(gimpdocs);
    } catch(GUI_GenericException &exception){
        gimpdocs->setCursor(Qt::ArrowCursor);
        QMessageBox::information(gimpdocs, "", exception.message);
        return false;
    }

    return returnValue;
}


/*USERS*/
int GUI_ConnectionToServerWrapper::requestLoginWrapper(GIMPdocs *gimpdocs, QString username, QString password){
    int returnValue;

    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        returnValue = gimpdocs->getConnection()->requestTryLogin(username, password);
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        handleReconnection(gimpdocs);
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
        gimpdocs->getConnection()->requestTryLogOut(userId);
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        handleReconnection(gimpdocs);
    } catch(GUI_GenericException &exception){
        gimpdocs->setCursor(Qt::ArrowCursor);
        QMessageBox::information(gimpdocs, "", exception.message);
        return -1;
    }

    return 1;
}

int GUI_ConnectionToServerWrapper::requestDefinitiveLogoutWrapper(GIMPdocs *gimpdocs, int userId){
    //questa è un'uscita di forza bruta quando le cose non funzionano. Se il server o la connessione mi danno problemi io chiudo tutto lo stesso

    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        gimpdocs->getConnection()->requestTryLogOut(userId);
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        //return -1;
    } catch(GUI_GenericException &exception){
        gimpdocs->setCursor(Qt::ArrowCursor);
        //non ritorno -1, altrimenti sono soggetto a loop infiniti. Lascio che il client si chiuda e prima o poi il server se ne accorgerà
    }

    return 1;
}

int GUI_ConnectionToServerWrapper::requestNewAccountWrapper(GIMPdocs *gimpdocs, QString username, QString password, QString nickname, QString iconId){
    int returnValue;

    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        returnValue = gimpdocs->getConnection()->requestNewAccount(username,password, nickname, iconId);
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        handleReconnection(gimpdocs);
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
        gimpdocs->getConnection()->requestUpdateAccount(userId, password, nickname, icon);
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        handleReconnection(gimpdocs);
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
        returnValue = QString::fromStdString(gimpdocs->getConnection()->requestGetNickname(userId));
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        handleReconnection(gimpdocs);
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
        returnValue = QString::fromStdString(gimpdocs->getConnection()->requestGetUsername(userId));
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        handleReconnection(gimpdocs);
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
        returnValue = QString::fromStdString(gimpdocs->getConnection()->requestIconId(userId));
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        handleReconnection(gimpdocs);
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
        mpointer = gimpdocs->getConnection()->getKnownDocuments(userId);
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        handleReconnection(gimpdocs);
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
        //sto ricevendo un malloppo di parametri stringati tutti assieme
        returnValue = QString::fromStdString(gimpdocs->getConnection()->requestCreateDocument(userId, name));
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        handleReconnection(gimpdocs);
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
        gimpdocs->getConnection()->requestDeleteDoc(userId, documentId);
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        handleReconnection(gimpdocs);
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
        //anche qui sto ricevendo un malloppo di parametri stringati assieme
        returnValue = QString::fromStdString(gimpdocs->getConnection()->openDoc(userId, documentId));
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        handleReconnection(gimpdocs);
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
        gimpdocs->getConnection()->disconnectEditor(userId, docId);
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        handleReconnection(gimpdocs);
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
        //anche qui sto ricevendo un malloppo di parametri stringati assieme
        returnValue = QString::fromStdString(gimpdocs->getConnection()->requestDocIdDatoUri(uri, userId));
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        handleReconnection(gimpdocs);
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
        returnValue = QString::fromStdString(gimpdocs->getConnection()->requestUri(docId));
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        handleReconnection(gimpdocs);
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
        returnValue = QString::fromStdString(gimpdocs->getConnection()->requestDocName(docId));
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        handleReconnection(gimpdocs);
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
        returnValue = gimpdocs->getConnection()->getDocumentOwner(docId);
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        handleReconnection(gimpdocs);
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
        docpointer = gimpdocs->getConnection()->requestDocumentText(docId, userId);
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        handleReconnection(gimpdocs);
    } catch(GUI_GenericException &exception){
        gimpdocs->setCursor(Qt::ArrowCursor);
        QMessageBox::information(gimpdocs, "", exception.message);
        return nullptr;
    }

    return docpointer;
}


/*EDITOR*/
int GUI_ConnectionToServerWrapper::requestStartEditorConnection(GIMPdocs *gimpdocs){
    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        gimpdocs->getConnection()->connectEditor();
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        handleReconnection(gimpdocs);
    } catch(GUI_GenericException &exception){
        gimpdocs->setCursor(Qt::ArrowCursor);
        QMessageBox::information(gimpdocs, "", exception.message);
        return -1;
    }

    return 1;
}

//uso un set perchè è una garanzia in più sull'unicità dello userId
std::shared_ptr<QSet<int>> GUI_ConnectionToServerWrapper::getWorkingUsersOnDocumentWrapper(GIMPdocs *gimpdocs, int docId){
    std::shared_ptr<QSet<int>> users;

    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        users = gimpdocs->getConnection()->getWorkingUsersOnDocument(docId);
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        handleReconnection(gimpdocs);
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
        contributors = gimpdocs->getConnection()->getContributors(docId);
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        handleReconnection(gimpdocs);
    } catch(GUI_GenericException &exception){
        gimpdocs->setCursor(Qt::ArrowCursor);
        QMessageBox::information(gimpdocs, "", exception.message);
        return nullptr;
    }

    return contributors;
}




void GUI_ConnectionToServerWrapper::handleReconnection(GIMPdocs *gimpdocs){
    //provo a ristabilire la connessione, e se non ci riesco ci riprovo finchè non ci riesco, o finchè l'utente non si arrende. E quando ci riesco ... chiudo tutto e riparto da capo
    GUI_Reconnection::GUI_ReconnectionWrapper(gimpdocs);
    gimpdocs->returnToLogin();
}
