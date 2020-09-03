#include "gui_profile.h"
#include "gui_menu.h"
#include "gui_login.h"

#include <QMessageBox>
#include <QIcon>
//#include <QFile>
//#include <QDir>

GUI_Profile::GUI_Profile(QWidget *parent) : QWidget(parent)
{
    this->setObjectName(GUI_Profile::getObjectName());
    gimpParent = static_cast<GIMPdocs*>(parent);
    ui.reset(new Ui::GUI_Profile);
    ui->setupUi(this);

    loadIcons();

    //qui controllo se sto creando un nuovo utente o se ne sto modificando uno già loggato
    if(gimpParent->userid > -1){
        ui->usernameLineEdit->hide();
        fillForm();
    }
    else
        ui->usernameLabelReadonly->hide();


    //faccio le connect così premendo Enter prova a salvare
    connect(ui->nicknameLineEdit, &QLineEdit::returnPressed, this, &GUI_Profile::on_savePushButton_clicked);
    connect(ui->usernameLineEdit, &QLineEdit::returnPressed, this, &GUI_Profile::on_savePushButton_clicked);
    connect(ui->passwordLineEdit, &QLineEdit::returnPressed, this, &GUI_Profile::on_savePushButton_clicked);
    connect(ui->repeatLineEdit, &QLineEdit::returnPressed, this, &GUI_Profile::on_savePushButton_clicked);
}

GUI_Profile::~GUI_Profile(){
    //delete ui;
}

void GUI_Profile::on_savePushButton_clicked(){
    if(!checkFieldValidity(ui->nicknameLineEdit->text(), "Nickname"))
        return;
    //in caso di modifica questo non ha bisogno di essere controllato perchè è read only
    if(gimpParent->userid < 0){
        if(!checkFieldValidity(ui->usernameLineEdit->text(), "Username"))
            return;
    }
    if(!checkFieldValidity(ui->passwordLineEdit->text(), "Password"))
        return;
    if(!checkFieldValidity(ui->repeatLineEdit->text(), "Repeat password"))
        return;

    if(!checkPasswordSecurity(ui->passwordLineEdit->text(), ui->repeatLineEdit->text()))
        return;

    //creo un nuovo utente o aggiorno quello vecchio
    if(gimpParent->userid < 0){
        //creo un nuovo user
        int result = GUI_ConnectionToServerWrapper::requestNewAccountWrapper(gimpParent, ui->usernameLineEdit->text(), ui->passwordLineEdit->text(), ui->nicknameLineEdit->text(), qvariant_cast<QString>(ui->iconComboBox->currentData()));
        if(result == -1)
            return;

        gimpParent->userid = result;
    }else{
        //faccio l'update del vecchio user
        if(GUI_ConnectionToServerWrapper::requestUpdateAccountWrapper(gimpParent, gimpParent->userid, ui->passwordLineEdit->text(), ui->nicknameLineEdit->text(), qvariant_cast<QString>(ui->iconComboBox->currentData())) == -1)
            return;
    }

    GUI_Menu *widget = new GUI_Menu(gimpParent);
    gimpParent->setCentralWidget(widget);
}

void GUI_Profile::on_backPushButton_clicked(){

    if(gimpParent->userid < 0){
        GUI_Login *widget = new GUI_Login(gimpParent);
        gimpParent->setCentralWidget(widget);
    }
    else{
        GUI_Menu *widget = new GUI_Menu(gimpParent);
        gimpParent->setCentralWidget(widget);
    }

}

void GUI_Profile::fillForm(){
    //questo if non dovrebbe mai attivarsi, ma non si sa mai
    if(gimpParent->userid < 0)
        return;

    QString iconId = GUI_ConnectionToServerWrapper::requestGetIconIdWrapper(gimpParent, gimpParent->userid);
    if(iconId.compare("errore") != 0){
        QString iconPath = GUI_Icons::getIconPath(iconId);
        //non dovrebbe mai dare problemi, a meno che il server non elimini delle icone senza avvisare gli user che avevano scelto quell'icona
        if(iconPath.compare("") != 0){
            int boxIndex = ui->iconComboBox->findData(iconId);
            ui->iconComboBox->setCurrentIndex(boxIndex);
        }
    }

    QString nickname = GUI_ConnectionToServerWrapper::requestGetNicknameWrapper(gimpParent, gimpParent->userid);
    if(nickname.compare("errore") != 0)
        ui->nicknameLineEdit->setText(nickname);

    QString username = GUI_ConnectionToServerWrapper::requestGetUsernameWrapper(gimpParent, gimpParent->userid);
    if(username.compare("errore") != 0)
        ui->usernameLabelReadonly->setText(username);
}

void GUI_Profile::loadIcons(){
    QMap<QString, QString> *m = GUI_Icons::getIconPaths();
    for (QMap<QString, QString>::iterator iter = m->begin(); iter != m->end(); iter++ )
        ui->iconComboBox->addItem(QIcon(iter.value()), "", iter.key());
}

bool GUI_Profile::checkFieldValidity(QString value, QString fieldName){
    if(value.isEmpty()){
        QMessageBox::information(this, "", "\"" + fieldName + "\" field is empty");
        return false;
    }
    if(value.contains('\\') || value.contains('_')){
        QMessageBox::information(this, "", "An invalid character \"\\\", \"_\" is present in \"" + fieldName + "\" field");
        return false;
    }

    return true;
}

bool GUI_Profile::checkPasswordSecurity(QString password, QString repeatPassword){
    int minLength = 4;

    if(password.compare(repeatPassword) != 0){
        QMessageBox::information(this, "", "Password and repeated password must be equal");
        return false;
    }

    if(password.length() < minLength){
        QMessageBox::information(this, "", "Password should be at least " + QString::number(minLength) + " characters long");
        return false;
    }

    return true;
}
