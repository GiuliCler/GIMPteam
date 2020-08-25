#include "gui_menu.h"
#include "gui_login.h"
#include "gui_profile.h"
#include "gui_newdoc.h"
#include "gui_opendoc.h"
#include <QPixmap>
#include <QTextCodec>

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
    //carico nickname e icona dell'utente
    QString nickname = GUI_ConnectionToServerWrapper::requestGetNicknameWrapper(gimpParent, gimpParent->userid);
    if(nickname.compare("errore") != 0)
        ui->nicknameLabel->setText(nickname);

    QString iconId = GUI_ConnectionToServerWrapper::requestGetIconIdWrapper(gimpParent, gimpParent->userid);
    if(iconId.compare("errore") != 0){
        QString iconPath = GUI_Icons::getIconPath(iconId);
        if(iconPath.compare("") == 0)
            //non dovrebbe mai succedere, a meno che il server non elimini delle icone senza avvisare gli user che avevano scelto quell'icona
            return;

        QPixmap image = QPixmap(iconPath);
        ui->iconLabel->setPixmap(image);
    }
}

void GUI_Menu::setDocumentArea(){
    //so che il parent verrà modificato nel momento in cui lo aggiungo al layout, ma viene salvato come GimpParent
    ui->newdocTab->layout()->addWidget(new GUI_Newdoc(this));
    ui->opendocTab->layout()->addWidget(new GUI_Opendoc(this));

}

void GUI_Menu::on_editPushButton_clicked(){
    GUI_Profile *widget = new GUI_Profile(gimpParent);
    gimpParent->setCentralWidget(widget);
}

void GUI_Menu::on_logoutPushButton_clicked(){
    if(GUI_ConnectionToServerWrapper::requestLogoutWrapper(gimpParent, gimpParent->userid) == -1)
        return;

    GUI_Login *widget = new GUI_Login(gimpParent);
    gimpParent->setCentralWidget(widget);
}
