//lo metto qui per non geenrare loop di ".h" nel .h assieme a gui_connectionError a sua volta importaato da gimpdocs
#include "../gimpdocs.h"

#include "gui_connecting.h"
#include "gui_reconnection.h"
#include "../gui_login.h"
#include "../gui_menu.h"
#include <QMovie>

void GUI_Connecting::GUI_ConnectingWrapper(QWidget *parent, GIMPdocs *gimpdocs){
    GUI_Connecting *box = new GUI_Connecting(parent);
    box->setVisible(true);

    //pingo il server
    if(!Stub::isConnectionWorking(gimpdocs->getConnection())){
        GUI_Reconnection *box2 = new GUI_Reconnection(static_cast<GIMPdocs*>(parent));
        box2->setVisible(true);
    }
    else{
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
        }
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
