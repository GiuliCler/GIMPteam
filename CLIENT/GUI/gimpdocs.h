#ifndef GIMPDOCS_H
#define GIMPDOCS_H


#include "gui_icons.h"
#include "ui_gimpdocs.h"
#include "ui_gui_editorwindow.h"
#include "../connection_to_server.h"
#include "connection/gui_connectionToServerWrapper.h"

#include "connection/gui_connectionException.h"
#include "connection/gui_genericException.h"

#include <QMainWindow>
#include <QDebug>
#include <QCloseEvent>
//per gli smart pointers
#include <memory>

class GIMPdocs : public QMainWindow
{
    Q_OBJECT

public:
    int userid;
    //serve per sapere se la connessione dell'editor col server è ancora attiva
    bool isEditorConnected = false;
    //mi servono public per fare delle connect
    std::unique_ptr<Ui::GIMPdocs> ui1;
    std::unique_ptr<Ui::GUI_EditWindow> ui2;

    explicit GIMPdocs(QWidget *parent = nullptr);
    void closeEvent (QCloseEvent *event);

    //servono a cambiare l'ui attiva. Widget è il central widget da caricare
    void setUi1(QWidget *widget);
    void setUi2(QWidget *widget);
    void setConnection(connection_to_server *connection);
    connection_to_server *getConnection();
    void returnToLogin();

private:
    QSize regularWindowSize;
    //serve per ripristinare lo stato maximized/normal dopo la chiusura del document in base a com'era prima
    bool alreadyMaximized;
    connection_to_server *connection = nullptr;

};

#endif // GIMPDOCS_H
