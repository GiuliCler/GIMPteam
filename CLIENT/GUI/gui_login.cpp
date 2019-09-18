#include "gui_login.h"
#include "gui_profile.h"
#include "gimpdocs.h"
#include "gui_menu.h"
#include <QMessageBox>

GUI_Login::GUI_Login(QWidget *parent) : QWidget(parent)
{
    this->setObjectName(GUI_Login::getObjectName());
    ui = new Ui::GUI_Login();
    ui->setupUi(this);
    //serve a segnalare che non ci sono utenti attivi e rimuove l'id dell'eventuale user che ha appena fatto il logout
    static_cast<GIMPdocs*>(this->parent())->userid = -1;

}

GUI_Login::~GUI_Login(){
    delete ui;
}

void GUI_Login::on_newAccountButton_clicked()
{
    static_cast<GIMPdocs*>(this->parent())->userid = -1;
    GUI_Profile *widget = new GUI_Profile(static_cast<QWidget*>(this->parent()));
    static_cast<GIMPdocs*>(this->parent())->setCentralWidget(widget);
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

    static_cast<GIMPdocs*>(this->parent())->userid = Stub::tryLogin(ui->usernameLineEdit->text(), ui->passwordLineEdit->text());
    if(static_cast<GIMPdocs*>(this->parent())->userid < 0){
        QMessageBox::information(this, "", "Username or Password are incorrect");
        return;
    }

    GUI_Menu *widget = new GUI_Menu(static_cast<QWidget*>(this->parent()));
    static_cast<GIMPdocs*>(this->parent())->setCentralWidget(widget);
}
