#include "../gimpdocs.h"
#include "gui_connectionToServerWrapper.h"

#include <QMessageBox>

int GUI_ConnectionToServerWrapper::requestTryLoginWrapper(GIMPdocs *gimpdocs, QString username, QString password){
    int returnValue;

    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        returnValue = Stub::requestTryLoginTemporary(gimpdocs->getConnection(), username, password);
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
    int returnValue;

    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        returnValue = Stub::requestUpdateAccountTemporary(gimpdocs->getConnection(), userId, password, nickname, icon);
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

QString GUI_ConnectionToServerWrapper::requestGetNicknameWrapper(GIMPdocs *gimpdocs, int userId){
    QString returnValue;

    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        std::string stringa = Stub::requestGetNicknameTemporary(gimpdocs->getConnection(), userId);
        returnValue = QString::fromStdString(stringa);
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
        std::string stringa = Stub::requestGetUsernameTemporary(gimpdocs->getConnection(), userId);
        returnValue = QString::fromStdString(stringa);
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

QString GUI_ConnectionToServerWrapper::requestIconIdWrapper(GIMPdocs *gimpdocs, int userId){
    QString returnValue;

    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        std::string stringa = Stub::requestIconIdTemporary(gimpdocs->getConnection(), userId);
        returnValue = QString::fromStdString(stringa);
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



/*DOCUMENT*/
int GUI_ConnectionToServerWrapper::requestCreateDocumentWrapper(GIMPdocs *gimpdocs, int userId, QString name){
    int returnValue;

    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        returnValue = Stub::requestCreateDocumentTemporary(gimpdocs->getConnection(), userId, name);
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

int GUI_ConnectionToServerWrapper::openKnownDocumentWrapper(GIMPdocs *gimpdocs, int documentId){

    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        Stub::openKnownDocument(documentId);
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
int GUI_ConnectionToServerWrapper::requestLogOutWrapper(GIMPdocs *gimpdocs, int userId){
    int returnValue = 1;
    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        returnValue = Stub::requestLogOut(gimpdocs->getConnection(), userId);
        gimpdocs->setCursor(Qt::ArrowCursor);
    } catch (GUI_ConnectionException &exception) {
        gimpdocs->setCursor(Qt::ArrowCursor);
        //provo a ristabilire la connessione
        GUI_Connecting::GUI_ConnectingWrapper(gimpdocs);
        return -1;
    }
    return returnValue;
}

int GUI_ConnectionToServerWrapper::forgetKnownDocumentWrapper(GIMPdocs *gimpdocs, int userId, int documentId){

    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        Stub::forgetKnownDocument(gimpdocs->getConnection(), userId, documentId);
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

std::shared_ptr<QMap<QString, int>> GUI_ConnectionToServerWrapper::getKnownDocumentsWrapper(GIMPdocs *gimpdocs, int userId){
    std::shared_ptr<QMap<QString, int>> mpointer = nullptr;

    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        mpointer = gimpdocs->getConnection()->getKnownDocuments(userId);
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

int GUI_ConnectionToServerWrapper::requestDocDatoUriWrapper(GIMPdocs *gimpdocs, QString uri){
    int returnValue;

    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        returnValue = gimpdocs->getConnection()->requestDocDatoUri(uri);
        gimpdocs->setCursor(Qt::ArrowCursor);
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

QString GUI_ConnectionToServerWrapper::requestUriWrapper(GIMPdocs *gimpdocs, int docId){
    QString returnValue;

    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        std::string stringa = Stub::requestUriTemporary(gimpdocs->getConnection(), docId);
        returnValue = QString::fromStdString(stringa);
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

QString GUI_ConnectionToServerWrapper::getDocumentNameWrapper(GIMPdocs *gimpdocs, int docId){
    QString returnValue;

    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        std::string stringa = Stub::getDocumentName(gimpdocs->getConnection(), docId);
        returnValue = QString::fromStdString(stringa);
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

int GUI_ConnectionToServerWrapper::closeDocumentWrapper(GIMPdocs *gimpdocs, int userId, int docId){
    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        Stub::closeDocument(userId, docId);
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


std::shared_ptr<QTextDocument> GUI_ConnectionToServerWrapper::getDocumentTextWrapper(GIMPdocs *gimpdocs, int docId){
    std::shared_ptr<QTextDocument> docpointer;

    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        docpointer = Stub::getDocumentText(docId);
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
        users = Stub::getWorkingUsersOnDocument(gimpdocs->getConnection(), docId);
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
        contributors = Stub::getWorkingUsersOnDocument(gimpdocs->getConnection(), docId);
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
