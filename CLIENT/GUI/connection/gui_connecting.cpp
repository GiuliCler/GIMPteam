#include "gui_connecting.h"
#include "gui_reconnection.h"
#include <QMovie>

void GUI_Connecting::GUI_ConnectingWrapper(QWidget *parent){
    GUI_Connecting *box = new GUI_Connecting(parent);
    box->setVisible(true);

    //pingo il server
    if(!Stub::isConnectionWorking()){
        GUI_Reconnection *box2 = new GUI_Reconnection(parent);
        box2->setVisible(true);
    }

    box->close();
}

GUI_Connecting::GUI_Connecting(QWidget *parent) : QDialog(parent){
    ui = new Ui::GUI_Connecting;
    ui->setupUi(this);

    setWindowTitle("Connecting");
    //nota: si possono settare i flag tutti assieme o uno per volta, ma non a piccoli gruppetti perchè ad ogni aggiunta con setWindowsFlagSSSS (plurale) si cancellano i precedenti
    setWindowFlag(Qt::WindowContextHelpButtonHint,false);
    setWindowFlag(Qt::Dialog);
    setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);

    //metto la GIF
    QMovie *movie = new QMovie(":/other/connecting.gif");
    ui->GIFLabel->setMovie(movie);
    movie->start();

}

GUI_Connecting::~GUI_Connecting(){
    delete ui;
}
