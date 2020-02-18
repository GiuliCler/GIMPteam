#ifndef GIMPDOCS_H
#define GIMPDOCS_H


#include "stub.h"
#include "gui_icons.h"
#include "ui_gimpdocs.h"
#include "ui_gui_editorwindow.h"
#include "../connection_to_server.h"
#include <QMainWindow>
#include <QDebug>

class GIMPdocs : public QMainWindow
{
    Q_OBJECT

public:
    int userid;
    QSize regularWindowSize;
    //serve per ripristinare lo stato maximized/normal dopo la chiusura del document in base a com'era prima
    bool alreadyMaximized;
    //mi servono public per fare delle connect
    Ui::GIMPdocs *ui1;
    Ui::GUI_EditWindow *ui2;

    explicit GIMPdocs(QWidget *parent = nullptr);
    ~GIMPdocs();

    //servono a cambiare l'ui attiva. Widget è il central widget da caricare
    void setUi1(QWidget *widget);
    void setUi2(QWidget *widget);
    connection_to_server *c;
    connection_to_server *getConnection();

};

#endif // GIMPDOCS_H
