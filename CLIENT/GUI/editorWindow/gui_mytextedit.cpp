#include "gui_mytextedit.h"
#include "gui_editor.h"
#include <QColor>

GUI_MyTextEdit::GUI_MyTextEdit(QWidget *parent) : QTextEdit(parent) {
    this->setObjectName(GUI_MyTextEdit::getObjectName());
    editorParent = static_cast<GUI_Editor*>(parent);

    this->setCursorWidth(2);
    this->setFontPointSize(12); //TODO: fix this in a default font
    //TODO: start with left alignment on text (button left_alignment in the toolsbar should be checked at start)
    this->setText("I pulsanti funzionano un po' a caso per ragioni di debug");
}

void GUI_MyTextEdit::paintEvent(QPaintEvent *event)
{
    // questo serve a disegnare tutto quanto il resto normalmente
    QTextEdit::paintEvent(event);

    //e qui do l'ordine di disegnare sopra al foglio i cursori secondari
    for(auto pair = cursorsMap.begin(); pair != cursorsMap.end(); pair++)
      pair.value()->paint();
}

void GUI_MyTextEdit::addUserCursor(long userId, QPoint position, QColor color){
    if(cursorsMap.find(userId) != cursorsMap.end()){
        //TODO: gestione intelligente
        return;
    }

    cursorsMap.insert(userId, new GUI_ColoredCursor(this, position, color));
    //per ridisegnare tutto, nuovo cursore soprattutto
    this->viewport()->update();
}

void GUI_MyTextEdit::removeUserCursor(long userId){
    if(cursorsMap.find(userId) == cursorsMap.end()){
        //TODO:: gestione intelligente
        return;
    }

    cursorsMap.remove(userId);
    this->viewport()->update();
}
