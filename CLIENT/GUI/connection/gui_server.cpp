#include "gui_server.h"
#include "../gui_login.h"
#include <QMessageBox>

#include "gui_reconnection.h"
#include "gui_connecting.h"

GUI_Server::GUI_Server(QWidget *parent) : QWidget(parent){

    //gimpParent = static_cast<GIMPdocs*>(parent);

    connection = new connection_to_server("56529", "192.168.56.1");
    gimpParent->setConnection(connection);
    GUI_Login *widget = new GUI_Login(gimpParent);
    gimpParent->setCentralWidget(widget);

   /* ui = new Ui::GUI_Server;
    ui->setupUi(this);

    //la connect col pushbutton è già stata fatta di default dall'editor in maniera implicita, ma queste devo farle in maniera esplicita perchè mi collego alla stessa slot e non posso cambiarle nome per fare l'Autoconnect
    connect(ui->addressLineEdit, &QLineEdit::returnPressed, this, &GUI_Server::on_confirmPushButton_clicked);
    connect(ui->portLineEdit, &QLineEdit::returnPressed, this, &GUI_Server::on_confirmPushButton_clicked);
*/
}

GUI_Server::~GUI_Server(){
    delete ui;
}



void GUI_Server::on_confirmPushButton_clicked(){
    if(ui->addressLineEdit->text().isEmpty()){
        QMessageBox::information(this, "", "\"Address\" field is empty");
        return;
    }
    if(ui->portLineEdit->text().isEmpty()){
        QMessageBox::information(this, "", "\"Port\" field is empty");
        return;
    }

    if(!checkAddressValidity(ui->addressLineEdit->text())){
        QMessageBox::information(this, "", "\"Address\" format is incorrect");
        return;
    }

    if(!checkPortValidity(ui->portLineEdit->text())){
        QMessageBox::information(this, "", "\"Port\" format is incorrect");
        return;
    }

    connection_to_server * connection = new connection_to_server(ui->portLineEdit->text(), ui->addressLineEdit->text());
    gimpParent->setConnection(connection);
    GUI_Login *widget = new GUI_Login(gimpParent);
    gimpParent->setCentralWidget(widget);

}


bool GUI_Server::checkAddressValidity(QString address){

    QStringList list = address.split(".");
    if(list.size() != 4)
        return false;

    for(QString numberString : list){

        //se la stringa non è un numero ritorna 0 ....
        int number = numberString.toInt();
        //... quindi se ritorna uno zero controllo che sia davvero uno zero
        if(number == 0 && numberString.compare("0") != 0)
            return false;

        if(number < 0 || 255 < number)
            return false;
    }

    return true;
}

bool GUI_Server::checkPortValidity(QString port){

    int number = port.toInt();
    //... quindi se ritorna uno zero controllo che sia davvero uno zero
    if(number == 0 && port.compare("0") != 0)
        return false;

    if(number < 0 || 65535 < number)
        return false;

    return true;
}

