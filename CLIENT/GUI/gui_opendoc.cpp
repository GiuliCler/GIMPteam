#include "gui_opendoc.h"
#include "gimpdocs.h"
#include "gui_editor.h"

GUI_Opendoc::GUI_Opendoc(QWidget *parent) : QWidget(parent)
{
    ui = new Ui::GUI_Opendoc;
    ui->setupUi(this);
}

GUI_Opendoc::~GUI_Opendoc(){
    delete ui;
}

void GUI_Opendoc::on_openDocsPushButton_clicked()
{
    QObject *par  = this->parent();
    QString cl = "GIMPdocs";    //l'ho definito solo per applicare la ".length()"
    while(strncmp(par->metaObject()->className(), "GIMPdocs", static_cast<size_t>(cl.length()))){
        par = par->parent();
    }

    GUI_Editor *widget = new GUI_Editor(static_cast<GIMPdocs*>(par));
    static_cast<GIMPdocs*>(par)->setUi2(widget);
}

void GUI_Opendoc::on_openURIPushButton_clicked()
{
    QObject *par  = this->parent();
    QString cl = "GIMPdocs";    //l'ho definito solo per applicare la ".length()"
    while(strncmp(par->metaObject()->className(), "GIMPdocs", static_cast<size_t>(cl.length()))){
        par = par->parent();
    }

    GUI_Editor *widget = new GUI_Editor(static_cast<GIMPdocs*>(par));
    static_cast<GIMPdocs*>(par)->setUi2(widget);
}
