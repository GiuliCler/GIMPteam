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
