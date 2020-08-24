#include "gui_uri.h"
#include <QClipboard>

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

void GUI_URI::on_copyPushButton_clicked(){
    QClipboard *clip = QApplication::clipboard();
    clip->setText(ui->URILabel->text());
}

void GUI_URI::on_copyPushButton_pressed(){
    ui->copiedLabel->setText("");
}

void GUI_URI::on_copyPushButton_released(){
    ui->copiedLabel->setText("URI copied");
}
