#include "gui_newdoc.h"
#include "gui_menu.h"
#include "gimpdocs.h"
#include "gui_editor.h"

#include "ui_gui_editorwindow.h"
#include <QDebug>

GUI_Newdoc::GUI_Newdoc(QWidget *parent) : QWidget(parent)
{
    ui = new Ui::GUI_Newdoc;
    ui->setupUi(this);
}

GUI_Newdoc::~GUI_Newdoc(){
    delete ui;
}

void GUI_Newdoc::on_createPushButton_clicked()
{
    /*
     * Qui devo fare una lunga serie di chiamate al parent perchè tutti quegli oggetti che ho innestato nel form ui si sono settati il padre come volevano loro
     * In più devo usare la strncmp perchè il "!=" è deprecated e devo scrivere la stringa nella strncmp perchè non sa convertire sa Qstring ad array di caratteri
     * */
    QObject *par  = this->parent();
    QString cl = "GIMPdocs";    //l'ho definito solo per applicare la ".length()"
    while(strncmp(par->metaObject()->className(), "GIMPdocs", static_cast<size_t>(cl.length()))){
        par = par->parent();
    }

    GUI_Editor *widget = new GUI_Editor(static_cast<GIMPdocs*>(par));
    static_cast<GIMPdocs*>(par)->setUi2(widget);
}
