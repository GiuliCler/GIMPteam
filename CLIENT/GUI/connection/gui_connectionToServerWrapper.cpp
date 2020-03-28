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

int GUI_ConnectionToServerWrapper::requestDocDatoUriWrapper(GIMPdocs *gimpdocs, QString uri){
    int returnValue;
    //gli assegno un valore giusto per togliere il warning
    returnValue = 1;

    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        //non ho ben capito cos'è questa stringa ritornata
        std::string stringa = Stub::requestDocDatoUriTemporary(gimpdocs->getConnection(), uri);

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

QString GUI_ConnectionToServerWrapper::requestUriWrapper(GIMPdocs *gimpdocs, long docId){
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
