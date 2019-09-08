#include "gui_newdoc.h"
#include "gui_menu.h"
#include "gimpdocs.h"

GUI_Newdoc::GUI_Newdoc(QWidget *parent) : QWidget(parent)
{
    ui = new Ui::GUI_Newdoc;
    ui->setupUi(this);
}

void GUI_Newdoc::on_pushButton_clicked()
{
    GUI_Menu *widget = new GUI_Menu(static_cast<QWidget*>(this->parent()));
    static_cast<GIMPdocs*>(this->parent())->loadCentralWidget(widget);
}
