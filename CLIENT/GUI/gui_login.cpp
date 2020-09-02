#include "gui_login.h"
#include "gui_profile.h"
#include "gui_menu.h"
#include <QMessageBox>

GUI_Login::GUI_Login(QWidget *parent) : QWidget(parent)
{
    this->setObjectName(GUI_Login::getObjectName());
    gimpParent = static_cast<GIMPdocs*>(parent);
    ui = new Ui::GUI_Login();
    ui->setupUi(this);

    //serve a segnalare che non ci sono utenti attivi e rimuove l'id dell'eventuale user che ha appena fatto il logout
    gimpParent->userid = -1;

    //la connect col pushbutton è già stata fatta di default dall'editor in maniera implicita, ma queste devo farle in maniera esplicita perchè mi collego alla stessa slot e non posso cambiarle nome per fare l'Autoconnect
    connect(ui->usernameLineEdit, &QLineEdit::returnPressed, this, &GUI_Login::on_loginButton_clicked);
    connect(ui->passwordLineEdit, &QLineEdit::returnPressed, this, &GUI_Login::on_loginButton_clicked);

}

GUI_Login::~GUI_Login(){
    delete ui;
}

void GUI_Login::on_newAccountButton_clicked()
{
    gimpParent->userid = -1;
    GUI_Profile *widget = new GUI_Profile(gimpParent);
    gimpParent->setCentralWidget(widget);
}

void GUI_Login::on_loginButton_clicked()
{
    //faccio un po' di controlli sui contenuti delle lineEdit di username e password
    if(!checkFieldValidity(ui->usernameLineEdit->text(), "Username"))
        return;
    if(!checkFieldValidity(ui->passwordLineEdit->text(), "Password"))
        return;

    int result = GUI_ConnectionToServerWrapper::requestLoginWrapper(gimpParent, ui->usernameLineEdit->text(), ui->passwordLineEdit->text());
    if( result == -1)
        return;

    gimpParent->userid = result;


    GUI_Menu *widget = new GUI_Menu(gimpParent);
    gimpParent->setCentralWidget(widget);
}


bool GUI_Login::checkFieldValidity(QString value, QString name){
    if(value.isEmpty()){
        QMessageBox::information(this, "", "\"" + name + "\" field is empty");
        return false;
    }
    if(value.contains('\\')){
        QMessageBox::information(this, "", "Invalid character \"\\\" is present in \"" + name + "\" field");
        return false;
    }

    return true;
}
