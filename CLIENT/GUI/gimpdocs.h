#ifndef GIMPDOCS_H
#define GIMPDOCS_H


#include "stub.h"
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

class GIMPdocs : public QMainWindow
{
    Q_OBJECT

public:
    int userid;
    bool isEditorConnected = false;
    //mi servono public per fare delle connect
    Ui::GIMPdocs *ui1;
    Ui::GUI_EditWindow *ui2;

    explicit GIMPdocs(QWidget *parent = nullptr);
    ~GIMPdocs();
    void closeEvent (QCloseEvent *event);

    //servono a cambiare l'ui attiva. Widget è il central widget da caricare
    void setUi1(QWidget *widget);
    void setUi2(QWidget *widget);
    void setConnection(connection_to_server *connection);
    connection_to_server *getConnection();

private:
    QSize regularWindowSize;
    //serve per ripristinare lo stato maximized/normal dopo la chiusura del document in base a com'era prima
    bool alreadyMaximized;
    connection_to_server *c = nullptr;

};

#endif // GIMPDOCS_H
