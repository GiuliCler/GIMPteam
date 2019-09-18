#include "gui_menu.h"
#include "gui_login.h"
#include "gui_profile.h"
#include "gui_newdoc.h"
#include "gui_opendoc.h"

#include <QPixmap>

GUI_Menu::GUI_Menu(QWidget *parent) : QWidget(parent)
{
    this->setObjectName(GUI_Menu::getObjectName());
    gimpParent = static_cast<GIMPdocs*>(parent);
    ui = new Ui::GUI_Menu;
    ui->setupUi(this);

    setProfileArea();
    setDocumentArea();
}

GUI_Menu::~GUI_Menu(){
    delete ui;
}

void GUI_Menu::setProfileArea(){
    ui->nicknameLabel->setText(Stub::getNickname(gimpParent->userid));
    int iconId = Stub::getIconId(gimpParent->userid);
    QPixmap image = QPixmap(GUI_Icons::getIconPath(iconId));
    ui->iconLabel->setPixmap(image);
}

void GUI_Menu::setDocumentArea(){
    //setto un layout ai due tab ed aggiungo ai layout i 2 widget
    ui->newdocTab->setLayout(new QGridLayout());
    //purtroppo settargli il parent è inutile perchè nel momento in cui faccio addWidget gli viene modificato il parent
    ui->newdocTab->layout()->addWidget(new GUI_Newdoc(this));

    ui->opendocTab->setLayout(new QGridLayout());
    ui->opendocTab->layout()->addWidget(new GUI_Opendoc(this));
}

void GUI_Menu::on_editPushButton_clicked()
{
    GUI_Profile *widget = new GUI_Profile(gimpParent);
    gimpParent->setCentralWidget(widget);
}

void GUI_Menu::on_logoutPushButton_clicked()
{
    GUI_Login *widget = new GUI_Login(gimpParent);
    gimpParent->setCentralWidget(widget);
}
