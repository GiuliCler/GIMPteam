#include "gui_newdoc.h"
#include "gui_menu.h"
#include "gimpdocs.h"
#include "gui_editor.h"

#include "ui_gui_editorwindow.h"
#include <QMessageBox>

GUI_Newdoc::GUI_Newdoc(QWidget *parent) : QWidget(parent), gimpParent(parent)
{
    ui = new Ui::GUI_Newdoc;
    ui->setupUi(this);
}

GUI_Newdoc::~GUI_Newdoc(){
    delete ui;
}

void GUI_Newdoc::on_createPushButton_clicked()
{
    if(ui->nameLineEdit->text().isEmpty()){
        QMessageBox::information(this, "", "\"Name\" field is empty");
        return;
    }

    long id = Stub::createDocument(static_cast<GIMPdocs*>(this->gimpParent)->userid, ui->nameLineEdit->text());
    if(id < 0){
        QMessageBox::information(this, "", "Generic error creating document");
        //TODO gestire più dettagliatamente
        return;
    }

    GUI_Editor *widget = new GUI_Editor(static_cast<GIMPdocs*>(this->gimpParent), id);
    static_cast<GIMPdocs*>(this->gimpParent)->setUi2(widget);
}
