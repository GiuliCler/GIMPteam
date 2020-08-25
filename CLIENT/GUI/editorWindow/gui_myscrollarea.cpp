#include "gui_myscrollarea.h"
#include "gui_usersbar.h"
#include <QHBoxLayout>
#include <QScrollBar>
#include <QPalette>

//ho bisogno che il parent sia il widget vuoto checonterrà l'ignored
GUI_MyScrollArea::GUI_MyScrollArea(QWidget *parent) : QScrollArea(parent){

    //imposto il widget che conterrà le labels della scroll area
    content = new QWidget(this);
    content->setLayout(new QHBoxLayout(content));
    this->setWidget(content);

    //scrollarea style
    setFrameShape(Shape::NoFrame);
    //sembra superflua visti i calcoli precisi che ho fatto, ma in certi casi serve
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //non mi ricordo perchè, ma se lo tolgo non si vede più il widget
    setWidgetResizable(true);
    //serve per nascondere i pixel bassi del widget che contiene la scrollbar che non ne vuole sapere di ridursi di height e quindi lo nascondo
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Ignored);
    //devo aggiungere i pixel che rimarranno nascosti. 17 è lo spessore di una scrollbar standard
    setFixedHeight(GUI_MyScrollArea::getFixedHeight() + (17 - GUI_MyScrollArea::getFixedScrollBarHeight()));
    static_cast<QWidget*>(this->parent())->setFixedHeight(GUI_MyScrollArea::getFixedHeight());

    //content style
    //è lo spacing fra le icone
    content->layout()->setSpacing(0);
    //questo serve perchè per qualche strana ragione, quando piazzo la user bar dentro il QTabWidget mi cambia il colore del background del content widget da solo e mette lo stesso che si usa di solito di default per l'attributo "window" nelle palette, e non solo lì
    //quindi la mia soluzione è mettere un colorea caso, ma metterlo trasparente...
    content->setStyleSheet("background-color: rgba(0,255,0, 0);");
    //... e devo mettere trasparente anche il background della scrollarea in generale
    QPalette pal = this->palette();
    pal.setColor(QPalette::Background, QColor(0,0,0,0));
    this->setPalette(pal);

    //scrollbar style
    this->horizontalScrollBar()->setMaximumHeight(GUI_MyScrollArea::getFixedScrollBarHeight());
    //static_cast<QWidget*>(this->horizontalScrollBar()->parent())->setMaximumHeight(17);

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
        content->layout()->setContentsMargins(0, GUI_MyScrollArea::getFixedScrollBarHeight() + 0, 0, 0 + (17 - GUI_MyScrollArea::getFixedScrollBarHeight()) + GUI_MyScrollArea::getFixedScrollBarHeight());
    else
        content->layout()->setContentsMargins(0, GUI_MyScrollArea::getFixedScrollBarHeight() + 0, 0, 0);
}
