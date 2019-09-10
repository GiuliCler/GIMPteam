#include "gui_profile.h"
#include "gui_menu.h"
#include "gimpdocs.h"
#include "ui_gui_login.h"

#include <QMessageBox>
#include <QIcon>
#include <QDebug>

GUI_Profile::GUI_Profile(QWidget *parent) : QWidget(parent)
{
    ui = new Ui::GUI_Profile;
    ui->setupUi(this);
    if(static_cast<GIMPdocs*>(this->parent())->userid > -1){
        ui->backPushButton->hide();
        ui->usernameLineEdit->hide();
        fillForm();
    }
    else{
        ui->usernameLabelReadonly->hide();
    }

    loadIcons();
}

void GUI_Profile::on_savePushButton_clicked()
{
    if(ui->nicknameLineEdit->text().isEmpty()){
        QMessageBox::information(this, "", "\"Nickname\" field is empty");
        return;
    }
    if(static_cast<GIMPdocs*>(this->parent())->userid < 0 && ui->usernameLineEdit->text().isEmpty()){
        QMessageBox::information(this, "", "\"Username\" field is empty");
        return;
    }
    if(ui->passwordLineEdit->text().isEmpty()){
        QMessageBox::information(this, "", "\"Password\" field is empty");
        return;
    }
    if(ui->repeatLineEdit->text().isEmpty()){
        QMessageBox::information(this, "", "\"Repeat password\" field is empty");
        return;
    }
    if(ui->passwordLineEdit->text() != ui->repeatLineEdit->text()){
        QMessageBox::information(this, "", "\"Password\" and \"Repeat password\" fields don't match");
        return;
    }

    if(static_cast<GIMPdocs*>(this->parent())->userid < 0){
        //creo un nuovo user
        long n = Stub::createUser(ui->usernameLineEdit->text(), ui->passwordLineEdit->text(), ui->nicknameLineEdit->text(), 1);
        if(n > -1)
            static_cast<GIMPdocs*>(this->parent())->userid = n;
        else{
            //TODO I don't know. Do something
        }

    }
    else{
        //faccio l'update del vecchio user
        Stub::updateUser(static_cast<GIMPdocs*>(this->parent())->userid, ui->passwordLineEdit->text(), ui->nicknameLineEdit->text(), 1);

    }
    //static_cast<GIMPdocs*>(this->parent())->userid = Stub::
    if(!static_cast<GIMPdocs*>(this->parent())->userid){
        QMessageBox::information(this, "", "Username or Password are incorrect");
        return;
    }



    GUI_Menu *widget = new GUI_Menu(static_cast<QWidget*>(this->parent()));
    static_cast<GIMPdocs*>(this->parent())->loadCentralWidget(widget);
}

void GUI_Profile::on_backPushButton_clicked()
{
    GUI_Login *widget = new GUI_Login(static_cast<QWidget*>(this->parent()));
    static_cast<GIMPdocs*>(this->parent())->loadCentralWidget(widget);
}

void GUI_Profile::fillForm(){
    if(static_cast<GIMPdocs*>(this->parent())->userid < 0)
        return;

    ui->nicknameLineEdit->setText(Stub::getNickname(static_cast<GIMPdocs*>(this->parent())->userid));
    ui->usernameLabelReadonly->setText(Stub::getUsername(static_cast<GIMPdocs*>(this->parent())->userid));
    ui->passwordLineEdit->setText(Stub::getPassword(static_cast<GIMPdocs*>(this->parent())->userid));
    ui->repeatLineEdit->setText(Stub::getPassword(static_cast<GIMPdocs*>(this->parent())->userid));
}

void GUI_Profile::loadIcons(){
    QVector<QString> *v = GUI_Icons::getIconPaths();
    QString *s;
    for (s = v->begin(); s != v->end(); s++) {
        ui->iconComboBox->addItem(QIcon(*s), "", s - v->begin());
        qDebug() << s - v->begin();
    }
}
