#include "gui_myscrollarea.h"
#include <QHBoxLayout>
#include <QDebug>
#include <QScrollBar>
#include "../gui_icons.h"
#include "gui_usersbar.h"

#define MAX_ICONWIDGET_WIDTH 10

GUI_MyScrollArea::GUI_MyScrollArea(QWidget *parent) : QScrollArea(parent){
    setWidgetResizable(true);

    //imposto il widget che conterrà il contenuto della scroll area
    content = new QWidget(this);
    content->setLayout(new QHBoxLayout(content));
    this->setWidget(content);

    //scrollarea style
    // mi serve soprattutto per la vertical policy o si slarga verso l'alto
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    setFrameShape(Shape::NoFrame);
    //il 2 bilancia il margin sotto, un 17 sta al posto della scrollbar e l'altro 17 sta soprae bilancia la scrollbar per avere simmetria
    setMaximumHeight(GUI_Icons::iconSize + (2+17) + 17);

    //content style
    content->layout()->setSpacing(0);
}

void GUI_MyScrollArea::updateSize(int numberOfUsers){
    /* la policy del widget è expanding perchè altrimenti viene schiacciato dall'altro expanding. Devo mettere almeno un expanding o per riempire lo spazio mi aumenta lo spacing fra i widget senza chiedermi il permesso
     * ho deciso che fino a TOT gli do lo spazio giusto giusto, oltre i TOT compare la scrollbar
     * */
    int number = numberOfUsers <= MAX_ICONWIDGET_WIDTH ? numberOfUsers : MAX_ICONWIDGET_WIDTH;
    setMaximumWidth(number * GUI_Icons::iconSize);
    setMinimumWidth(number * GUI_Icons::iconSize);

    /* il giochetto che faccio è:
     * se c'è la scrollbar, questa occupa lo spazio sotto le icone, se non c'è ci piazzo un margin della stessa dimensione della scrollbar per rimpiazzarla
     * nota che la size complessiva non deve cambiare o scombussolo le cose agli altri widget
     * */
    if(numberOfUsers <= MAX_ICONWIDGET_WIDTH)   //è come dire if(non c'è la scrollbar), solo che anche quando dovrebbe esserci non è ancora presente
        content->layout()->setContentsMargins(0, 2 + 17, 0, 17);
    else
        content->layout()->setContentsMargins(0, 2 + 17, 0, 0);
}
