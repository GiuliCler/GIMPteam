#include "../gimpdocs.h"
#include "gui_connectionToServerWrapper.h"

#include <QMessageBox>

int GUI_ConnectionToServerWrapper::requestTryLoginWrapper(GIMPdocs *gimpdocs, QString username, QString password){
    int returnValue;

    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        returnValue = Stub::requestTryLoginTemporary(gimpdocs->getConnection(), username, password);
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

long GUI_ConnectionToServerWrapper::requestNewAccountWrapper(GIMPdocs *gimpdocs, QString username, QString password, QString nickname, QString icon){
    int returnValue;

    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        returnValue = Stub::requestNewAccountTemporary(gimpdocs->getConnection(), username, password, nickname, icon);
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

long GUI_ConnectionToServerWrapper::requestUpdateAccountWrapper(GIMPdocs *gimpdocs, int userId, QString password, QString nickname, QString icon){
    int returnValue;

    try {
        gimpdocs->setCursor(Qt::WaitCursor);
        returnValue = Stub::requestUpdateAccountTemporary(gimpdocs->getConnection(), userId, password, nickname, icon);
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
