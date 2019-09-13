#include "gui_editor.h"
#include "gimpdocs.h"
#include "gui_menu.h"

GUI_Editor::GUI_Editor(QWidget *parent, long documentId) : QWidget(parent), documentId(documentId)
{
    ui = new Ui::GUI_Editor();
    ui->setupUi(this);

}

GUI_Editor::~GUI_Editor(){
    delete ui;
}

void GUI_Editor::on_menuPushButton_clicked()
{
    GUI_Menu *widget = new GUI_Menu(static_cast<GIMPdocs*>(this->parent()));
    static_cast<GIMPdocs*>(this->parent())->setUi1(widget);
}
