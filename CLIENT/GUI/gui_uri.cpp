#include "gui_uri.h"

GUI_URI::GUI_URI(QWidget *parent, QString uri) : QDialog(parent){
    ui = new Ui::GUI_URI;
    ui->setupUi(this);

    setWindowTitle("Document URI");
    //nota: si possono settare i flag tutti assieme o uno per volta, ma non a piccoli gruppetti perchè ad ogni aggiunta con setWindowsFlagSSSS (plurale) si cancellano i precedenti
    setWindowFlag(Qt::WindowContextHelpButtonHint,false);
    setWindowFlag(Qt::Dialog);
    setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);

    ui->URILabel->setText(uri);
}

GUI_URI::~GUI_URI(){
    delete ui;
}
