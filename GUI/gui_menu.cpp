#include "gui_menu.h"
#include "gui_login.h"
#include "gui_profile.h"
#include "gimpdocs.h"
#include "gui_newdoc.h"
#include "gui_opendoc.h"

#include <QPixmap>

GUI_Menu::GUI_Menu(QWidget *parent) : QWidget(parent)
{
    ui = new Ui::GUI_Menu;
    ui->setupUi(this);
    ui->nicknameLabel->setText(Stub::getNickname(static_cast<GIMPdocs*>(this->parent())->userid));

    QPixmap image = QPixmap(GUI_Icons::getIconPath(static_cast<GIMPdocs*>(this->parent())->userid));
    ui->iconLabel->setPixmap(image);
}

void GUI_Menu::on_editPushButton_clicked()
{
    GUI_Profile *widget = new GUI_Profile(static_cast<QWidget*>(this->parent()));
    static_cast<GIMPdocs*>(this->parent())->loadCentralWidget(widget);
}

void GUI_Menu::on_logoutPushButton_clicked()
{
    GUI_Login *widget = new GUI_Login(static_cast<QWidget*>(this->parent()));
    static_cast<GIMPdocs*>(this->parent())->loadCentralWidget(widget);
}

void GUI_Menu::on_newdocPushButton_clicked()
{
    GUI_Newdoc *widget = new GUI_Newdoc(static_cast<QWidget*>(this->parent()));
    static_cast<GIMPdocs*>(this->parent())->loadCentralWidget(widget);
}

void GUI_Menu::on_opendocPushButton_clicked()
{
    GUI_Opendoc *widget = new GUI_Opendoc(static_cast<QWidget*>(this->parent()));
    static_cast<GIMPdocs*>(this->parent())->loadCentralWidget(widget);
}
