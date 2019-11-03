#include "gui_myscrollarea.h"
#include "gui_usersbar.h"
#include <QHBoxLayout>
#include <QStyle>

#include <QScrollBar>
#include <QAbstractScrollArea>

GUI_MyScrollArea::GUI_MyScrollArea(QWidget *parent) : QScrollArea(parent){

    //imposto il widget che conterrà le labels della scroll area
    content = new QWidget(this);
    content->setLayout(new QHBoxLayout(content));
    this->setWidget(content);

    //scrollarea style
    setFrameShape(Shape::NoFrame);
    setMaximumHeight(getFixedHeight());
    //sembra superflua visti i calcoli precisi che ho fatto, ma in certi casi serve
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //non mi ricordo perchè, ma se lo tolgo non si vede più il widget
    setWidgetResizable(true);

    //setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Ignored);
    setFixedHeight(GUI_MyScrollArea::getFixedHeight()+5);
    static_cast<QWidget*>(this->parent()->findChild<QWidget*>("exteriorOnlineIgnoredWrapper"))->setFixedHeight(GUI_MyScrollArea::getFixedHeight());

    //content style
    //è lo spacing fra le icone
    content->layout()->setSpacing(0);
    //questo serve perchè per qualche strana ragione, quando piazzo la user bar dentro il QTabWidget mi cambia il colore del background del content widget da solo e mette lo stesso che si usa di solito di default per l'attributo "window" nelle palette, e non solo lì
    //quindi la mia soluzione è mettere un colorea caso, ma metterlo trasparente
    //content->setStyleSheet("background-color: rgba(0,0,0, 255);");

    //this->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOn);
    //this->horizontalScrollBar()->setFixedHeight(12);
    this->horizontalScrollBar()->setMaximumHeight(12);
    static_cast<QWidget*>(this->horizontalScrollBar()->parent())->setMaximumHeight(17);


}

void GUI_MyScrollArea::updateSize(int numberOfUsers){
    //ho deciso che fino a TOT labels gli do lo spazio giusto giusto, oltre i TOT compare la scrollbar
    int number = numberOfUsers <= GUI_MyScrollArea::getMaxUsersIconsNumber() ? numberOfUsers : GUI_MyScrollArea::getMaxUsersIconsNumber();
    setMaximumWidth(number * GUI_Icons::iconSize);
    setMinimumWidth(number * GUI_Icons::iconSize);

    /* il giochetto che faccio è:
     * se c'è la scrollbar, questa occupa lo spazio sotto le icone, se non c'è ci piazzo un margin della stessa dimensione della scrollbar per rimpiazzarla
     * nota che la size complessiva non deve cambiare o scombussolo le cose agli altri widget
     * */
    if(numberOfUsers <= GUI_MyScrollArea::getMaxUsersIconsNumber())   //è come dire if(non c'è la scrollbar), solo che anche quando dovrebbe esserci non è ancora presente
        content->layout()->setContentsMargins(0, GUI_MyScrollArea::getFixedScrollBarHeight() - 2, 0, 3 + GUI_MyScrollArea::getFixedScrollBarHeight());
    else
        content->layout()->setContentsMargins(0, GUI_MyScrollArea::getFixedScrollBarHeight() + 1, 0, 1);
}
