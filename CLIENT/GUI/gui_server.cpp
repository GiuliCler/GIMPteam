#include "gui_server.h"
#include <QMessageBox>

GUI_Server::GUI_Server(QWidget *parent) : QDialog(parent){
    ui = new Ui::GUI_Server;
    ui->setupUi(this);

    setWindowTitle("Server connection");
    //nota: si possono settare i flag tutti assieme o uno per volta, ma non a piccoli gruppetti perchè ad ogni aggiunta con setWindowsFlagSSSS (plurale) si cancellano i precedenti
    setWindowFlag(Qt::WindowContextHelpButtonHint,false);
    setWindowFlag(Qt::Dialog);
    setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);

    /*ui->URILabel->setText(uri);

    //style
    QFont font = ui->URILabel->font();
    font.setItalic(true);
    font.setPixelSize(font.pixelSize() + 2);
    ui->URILabel->setFont(font);*/
}

GUI_Server::~GUI_Server(){
    delete ui;
}



void GUI_Server::on_connectPushButton_clicked(){
    if(ui->addressLineEdit->text().isEmpty()){
        QMessageBox::information(this, "", "\"Address\" field is empty");
        return;
    }
    if(ui->portLineEdit->text().isEmpty()){
        QMessageBox::information(this, "", "\"Port\" field is empty");
        return;
    }

    connection = new connection_to_server(ui->portLineEdit->text(), ui->addressLineEdit->text());
    static_cast<GIMPdocs*>(parent())->setConnection(connection);
    this->close();

}
