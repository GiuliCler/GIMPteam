#include "gui_reconnection.h"
#include "../gui_login.h"
#include "../gui_menu.h"

#include <QMessageBox>

/*
if(static_cast<GIMPdocs*>(parent)->userid < 0){
    //l'utente non era loggato
    GUI_Login *widget = new GUI_Login(static_cast<GIMPdocs*>(parent));
    static_cast<GIMPdocs*>(parent)->setCentralWidget(widget);
}
else{
    //l'utente era già loggato
    //forse porebbe sevire qualche controllo in più o qualche accortezza prima di cambiare drasticamente widget; ma per ora lo provo così
    GUI_Menu *widget = new GUI_Menu(static_cast<GIMPdocs*>(parent));
    static_cast<GIMPdocs*>(static_cast<GIMPdocs*>(parent))->setUi1(widget);
}*/

GUI_Reconnection::Reconnection_Results GUI_Reconnection::GUI_ReconnectionWrapper(QWidget *parent){
    GUI_Reconnection box(parent);
    //box->setVisible(true);


    /*QMessageBox msgBox;
    msgBox.setText("Confirm?");
    QAbstractButton* pButtonYes = msgBox.addButton(tr("Yeah!"), QMessageBox::YesRole);
    msgBox.addButton(tr("Nope"), QMessageBox::NoRole);
    msgBox.exec();*/

    int result = Reconnection_Results::Failure;
    while (result == Reconnection_Results::Failure) {
        result = box.exec();
        qDebug() << result;
    }

    if(result == Reconnection_Results::KillApplication)
        //non uso il QCoreApplication::quit perchè qui non funziona; probabilmente perchè questa è una funzione static
        exit(EXIT_SUCCESS);

    return Reconnection_Results::Success;
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
    qDebug() << "WAKANDA";
}

void GUI_Reconnection::on_exitPushButton_clicked(){
    GUI_Reconnection::done(Reconnection_Results::KillApplication);
    //QCoreApplication::quit();
}

void GUI_Reconnection::on_retryPushButton_clicked(){
    //mostra una label, e disabilita il pulsante "retry" prima che l'utente infuriato richieda mille reconnect!!
    bool result = Stub::isConnectionWorking(static_cast<GIMPdocs*>(this->parent())->getConnection());

    if(!result)
        GUI_Reconnection::done(Reconnection_Results::Failure);
    else
        GUI_Reconnection::done(Reconnection_Results::Success);

    return;
}
