#include "gui_menu.h"
#include "gui_login.h"
#include "gimpdocs.h"

GUI_Menu::GUI_Menu(QWidget *parent) : QWidget(parent)
{
    ui = new Ui::GUI_Menu;
    ui->setupUi(this);
}

void GUI_Menu::on_pushButton_clicked()
{
    GUI_Login *widget = new GUI_Login(static_cast<QWidget*>(this->parent()));
    static_cast<GIMPdocs*>(this->parent())->loadCentralWidget(widget);
}
