#include "gui_profile.h"
#include "gui_menu.h"
#include "gui_login.h"

#include <QMessageBox>
#include <QIcon>
#include <QFile>
#include <QDir>

GUI_Profile::GUI_Profile(QWidget *parent) : QWidget(parent)
{
    this->setObjectName(GUI_Profile::getObjectName());
    gimpParent = static_cast<GIMPdocs*>(parent);
    ui = new Ui::GUI_Profile;
    ui->setupUi(this);

    //style
    QFont font = ui->titleLabel->font();
    font.setPixelSize(font.pixelSize() + 10);
    ui->titleLabel->setFont(font);

    //qui controllo se sto creando un nuovo utente o se ne sto modificando uno già loggato
    if(gimpParent->userid > -1){
        //ui->backPushButton->hide();
        ui->usernameLineEdit->hide();
        fillForm();
    }
    else
        ui->usernameLabelReadonly->hide();

    loadIcons();

    //faccio le connect così premendo Enter prova a salvare
    connect(ui->nicknameLineEdit, &QLineEdit::returnPressed, this, &GUI_Profile::on_savePushButton_clicked);
    connect(ui->usernameLineEdit, &QLineEdit::returnPressed, this, &GUI_Profile::on_savePushButton_clicked);
    connect(ui->passwordLineEdit, &QLineEdit::returnPressed, this, &GUI_Profile::on_savePushButton_clicked);
    connect(ui->repeatLineEdit, &QLineEdit::returnPressed, this, &GUI_Profile::on_savePushButton_clicked);
}

GUI_Profile::~GUI_Profile(){
    delete ui;
}

void GUI_Profile::on_savePushButton_clicked()
{
    //controllo che tutti i campi siano compilati
    if(ui->nicknameLineEdit->text().isEmpty()){
        QMessageBox::information(this, "", "\"Nickname\" field is empty");
        return;
    }
    if(ui->nicknameLineEdit->text().contains('\\')){
        QMessageBox::information(this, "", "Invalid character \"\\\" is present in \"Nickname\"");
        return;
    }
    //in caso di modifica questo non ha bisogno di essere controllato perchè è read only
    if(gimpParent->userid < 0){
        if(ui->usernameLineEdit->text().isEmpty()){
            QMessageBox::information(this, "", "\"Username\" field is empty");
            return;
        }
        if(ui->usernameLineEdit->text().contains('\\')){
            QMessageBox::information(this, "", "Invalid character \"\\\" is present in \"Username\"");
            return;
        }
    }
    if(ui->passwordLineEdit->text().isEmpty()){
        QMessageBox::information(this, "", "\"Password\" field is empty");
        return;
    }
    if(ui->passwordLineEdit->text().contains('\\')){
        QMessageBox::information(this, "", "Invalid character \"\\\" is present in \"Password\"");
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

    //creo un nuovo utente o aggiorno quello vecchio
    if(gimpParent->userid < 0){
        //creo un nuovo user
        int n = gimpParent->getConnection()->requestNewAccount(ui->usernameLineEdit->text(), ui->passwordLineEdit->text(), ui->nicknameLineEdit->text(), qvariant_cast<QString>(ui->iconComboBox->currentData()));
        if(n > -1){
            gimpParent->userid = n;
        }else{
            //TODO I don't know. Do something
            QMessageBox::information(this, "", "Username already present.");
            return;
        }

    }else{
        //faccio l'update del vecchio user
        //TODO: PROBLEMA CON USERID, deve essere associato allo username=>gestione lato database??
        long n = gimpParent->getConnection()->requestUpdateAccount(gimpParent->userid, ui->passwordLineEdit->text(), ui->nicknameLineEdit->text(), qvariant_cast<QString>(ui->iconComboBox->currentData()));
        if(n != 0){
            QMessageBox::information(this, "", "Generic error");
            return;
        }
    }

    GUI_Menu *widget = new GUI_Menu(gimpParent);
    gimpParent->setCentralWidget(widget);
}

void GUI_Profile::on_backPushButton_clicked()
{

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

    std::string nickname = gimpParent->getConnection()->requestGetNickname(gimpParent->userid);
    std::string username = gimpParent->getConnection()->requestGetUsername(gimpParent->userid);
    if(nickname != "errore" && username != "errore"){
    ui->nicknameLineEdit->setText(QString::fromStdString(nickname));
    ui->usernameLabelReadonly->setText(QString::fromStdString(username));
    ui->passwordLineEdit->setText("");
    ui->repeatLineEdit->setText("");
    }else{
        QMessageBox::information(this, "", "Error in server communication");
        return;
    }
}

void GUI_Profile::loadIcons(){
    QMap<QString, QString> *m = GUI_Icons::getIconPaths();
    for (QMap<QString, QString>::iterator iter = m->begin(); iter != m->end(); iter++ )
        ui->iconComboBox->addItem(QIcon(iter.value()), "", iter.key());
}
