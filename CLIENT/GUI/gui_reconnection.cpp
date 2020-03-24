#include "gui_reconnection.h"
#include <QClipboard>

GUI_Reconnection::GUI_Reconnection(QWidget *parent) : QDialog(parent){
    ui = new Ui::GUI_Reconnection;
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
