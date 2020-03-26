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
    QString nickname;
    QString result = GUI_ConnectionToServerWrapper::requestGetNicknameWrapper(gimpParent, gimpParent->userid);
    if(result.compare("errore") == 0)
        return;
    else
        nickname = result;
    ui->nicknameLabel->setText(nickname);

    QString iconId;
    result = GUI_ConnectionToServerWrapper::requestIconIdWrapper(gimpParent, gimpParent->userid);
    if(result.compare("errore") == 0)
        return;
    else
        iconId = result;

    QPixmap image = QPixmap(GUI_Icons::getIconPath(iconId));
    ui->iconLabel->setPixmap(image);
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
    GUI_Login *widget = new GUI_Login(gimpParent);
    gimpParent->setCentralWidget(widget);
}
