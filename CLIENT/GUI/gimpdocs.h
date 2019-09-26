#ifndef GIMPDOCS_H
#define GIMPDOCS_H

#include <QMainWindow>
#include <QDebug>
#include <QRandomGenerator>
#include "stub.h"
#include "gui_icons.h"
#include "ui_gimpdocs.h"
#include "ui_gui_editorwindow.h"

//se proprio non posso usarla me la tengo qui per fare copia incolla
//#define PARENT static_cast<GIMPdocs*>(this->parent())


class GIMPdocs : public QMainWindow
{
    Q_OBJECT

public:
    long userid;
    //mi servono public per fare delle connect
    Ui::GIMPdocs *ui1;
    Ui::GUI_EditWindow *ui2;

    explicit GIMPdocs(QWidget *parent = nullptr);
    ~GIMPdocs();

    //servono a cambiare l'ui attiva. Widget è il central widget da caricare
    void setUi1(QWidget *widget);
    void setUi2(QWidget *widget);

private slots:
    //serve per l'azione close document che ha bisogno di uno slot
    void launchSetUi1();

};

#endif // GIMPDOCS_H
