#include "gui_menu.h"
#include "gui_login.h"
#include "gui_profile.h"
#include "gimpdocs.h"

GUI_Menu::GUI_Menu(QWidget *parent) : QWidget(parent)
{
    ui = new Ui::GUI_Menu;
    ui->setupUi(this);
    ui->nicknameLabel->setText(Stub::getNickname());
}

void GUI_Menu::on_editPushButton_clicked()
{
    GUI_Profile *widget = new GUI_Profile(static_cast<QWidget*>(this->parent()));
    static_cast<GIMPdocs*>(this->parent())->loadCentralWidget(widget);
}
