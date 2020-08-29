#include "gui_reconnection.h"
#include "../gui_login.h"
#include "../gui_menu.h"

#include <QMessageBox>

void GUI_Reconnection::GUI_ReconnectionWrapper(QWidget *parent){
    GUI_Reconnection *box = new GUI_Reconnection(parent);

    //box->setVisible(true);
    //box->exec();
    //box->close();

    /*QMessageBox msgBox;
    msgBox.setText("Confirm?");
    QAbstractButton* pButtonYes = msgBox.addButton(tr("Yeah!"), QMessageBox::YesRole);
    msgBox.addButton(tr("Nope"), QMessageBox::NoRole);*/

    //msgBox.exec();
    if (box->exec()) {
        if(!Stub::isConnectionWorking(static_cast<GIMPdocs*>(parent)->getConnection())){
            //nascondi una label
            return;
        }
    }



}

GUI_Reconnection::GUI_Reconnection(QWidget *parent) : QDialog(parent){
    ui = new Ui::GUI_Reconnection();
    ui->setupUi(this);

    setWindowTitle("Connection failed");
    //nota: si possono settare i flag tutti assieme o uno per volta, ma non a piccoli gruppetti perchè ad ogni aggiunta con setWindowsFlagSSSS (plurale) si cancellano i precedenti
    setWindowFlag(Qt::WindowContextHelpButtonHint,false);
    setWindowFlag(Qt::Dialog);
    setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);

}

GUI_Reconnection::~GUI_Reconnection(){
    delete ui;
}

void GUI_Reconnection::on_exitPushButton_clicked(){
    QCoreApplication::quit();
}

GUI_Reconnection::Reconnection_Results GUI_Reconnection::on_retryPushButton_clicked(){
    //mostra una label

    if(!Stub::isConnectionWorking(static_cast<GIMPdocs*>(this->parent())->getConnection())){
        //nascondi una label
        return Reconnection_Results::Failure;
    }
    else{
        if(static_cast<GIMPdocs*>(parent())->userid < 0){
            //l'utente non era loggato
            GUI_Login *widget = new GUI_Login(static_cast<GIMPdocs*>(parent()));
            static_cast<GIMPdocs*>(parent())->setCentralWidget(widget);
        }
        else{
            //l'utente era già loggato
            //forse porebbe sevire qualche controllo in più o qualche accortezza prima di cambiare drasticamente widget; ma per ora lo provo così
            GUI_Menu *widget = new GUI_Menu(static_cast<GIMPdocs*>(parent()));
            static_cast<GIMPdocs*>(static_cast<GIMPdocs*>(parent()))->setUi1(widget);
        }
    }

    this->close();
}
