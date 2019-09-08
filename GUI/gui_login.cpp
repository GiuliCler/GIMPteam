#include "gui_login.h"
#include "gui_profile.h"
#include "gimpdocs.h"
#include "gui_menu.h"
#include <QMessageBox>

GUI_Login::GUI_Login(QWidget *parent) : QWidget(parent)
{
    ui = new Ui::GUI_Login();
    ui->setupUi(this);
}

void GUI_Login::on_newAccountButton_clicked()
{
    GUI_Profile *widget = new GUI_Profile(static_cast<QWidget*>(this->parent()));
    static_cast<GIMPdocs*>(this->parent())->loadCentralWidget(widget);
}

void GUI_Login::on_loginButton_clicked()
{

    if(ui->usernameLineEdit->text().isEmpty()){
        QMessageBox::information(this, "", "\"Username\" field is empty");
        return;
    }
    if(ui->passwordLineEdit->text().isEmpty()){
        QMessageBox::information(this, "", "\"Password\" field is empty");
        return;
    }
    if(!Stub::tryLogin(ui->usernameLineEdit->text(), ui->passwordLineEdit->text())){
        QMessageBox::information(this, "", "Username or Password are incorrect");
        return;
    }

    //TODO devo farmi ritornare l'id dalla getLogin anzichè un boolean, e poi passarlo al costruttore di Menù

    GUI_Menu *widget = new GUI_Menu(static_cast<QWidget*>(this->parent()));
    static_cast<GIMPdocs*>(this->parent())->loadCentralWidget(widget);
}
