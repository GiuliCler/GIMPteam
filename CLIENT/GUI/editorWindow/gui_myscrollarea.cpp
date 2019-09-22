#include "gui_myscrollarea.h"
#include <QHBoxLayout>
#include <QDebug>
#include <QScrollBar>
#include "../gui_icons.h"
#include "gui_usersbar.h"

#define MAX_ICONWIDGET_WIDTH 10

GUI_MyScrollArea::GUI_MyScrollArea(QWidget *parent) : QScrollArea(parent){
    setWidgetResizable(true);

    //il posto il widget che conterrà il contenuto della scroll area
    content = new QWidget(this);
    content->setLayout(new QHBoxLayout(content));
    this->setWidget(content);

    //scrollarea style
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setSizeAdjustPolicy(SizeAdjustPolicy::AdjustToContents);
    setFrameShape(Shape::NoFrame);
    setContentsMargins(0,0,0,0);
    setViewportMargins(0, 0, 0, 0);
    //setMaximumHeight(GUI_Icons::iconSize + this->horizontalScrollBar()->height());

    setMaximumHeight(GUI_Icons::iconSize);

    //content style
    content->layout()->setMargin(0);
    //content->layout()->setContentsMargins(0,17,0,0);
    content->layout()->setSpacing(1);
}

void GUI_MyScrollArea::resizeEvent(QResizeEvent *event){
    // Define content margins here
    setViewportMargins(0, 0, 0, 0); // <<<<< SET MARGINS HERE
    QScrollArea::resizeEvent(event);
}

//todo: trovare un nome più appropriato perchè non sempre faccio l'update
void GUI_MyScrollArea::updateSize(int numberOfUsers){
    /*non potevo mettere policy Fixed perchè le icone sono Ignored ed il fixed non avendo un valore fisso interno si azzera, quindi lo fixo settando a mano max e min
     * la policy del widget è expanding perchè altrimenti viene schiacciato dall'altro expanding. Devo mettere almeno un expanding o per riempire lo spazio mi aumenta lo spacing fra i widget senza chiedermi il permesso
     * ho anche dato proporzioni diverse ai 2 expanding (20,1) per dire che il widget delle icone ha diritto a tutto quello di cui ha bisogno
     * */
    //ho deciso che fino a TOT gli do lo spazio giusto giusto, oltre i TOT utenti comprimo le icone e si fanno bastare lo spazio che hanno
    int number = numberOfUsers <= MAX_ICONWIDGET_WIDTH ? numberOfUsers : MAX_ICONWIDGET_WIDTH;
    //il +1 è perchè li lascio un po' più larghi
    widget()->layout()->setSpacing(0);
    setMaximumWidth((number)*GUI_Icons::iconSize);
    setMinimumWidth((number)*GUI_Icons::iconSize);
    if(numberOfUsers > MAX_ICONWIDGET_WIDTH){
        setMaximumHeight(GUI_Icons::iconSize + 17*2);
        content->layout()->setContentsMargins(0,17,0,0);
        static_cast<GUI_UsersBar*>(this->parent())->layout()->setContentsMargins(6,0,6,2);
    }
    //l'else serve per quando li rimuovo
    else{
        setMaximumHeight(GUI_Icons::iconSize);
        content->layout()->setContentsMargins(0,0,0,0);
        static_cast<GUI_UsersBar*>(this->parent())->layout()->setContentsMargins(6,17,6,19);
    }
}
