#include "gui_mytextedit.h"
#include "gui_editor.h"

#include <QPainter>
#include <QColor>

GUI_MyTextEdit::GUI_MyTextEdit(QWidget *parent) : QTextEdit(parent) {
    this->setObjectName(GUI_MyTextEdit::getObjectName());
    editorParent = static_cast<GUI_Editor*>(parent);
    //per non farsi coprire dai cursori colorati
    this->setCursorWidth(2);
}

void GUI_MyTextEdit::paintEvent(QPaintEvent *event)
{
    // questo serve a disegnare tutto quanto il resto. Normalmente disegnerebbe anche il cursore nero, ma gli ho messo spessore 0
    QTextEdit::paintEvent(event);

    for(auto pair = cursorsMap.begin(); pair != cursorsMap.end(); pair++){
      pair.value()->paint();
    }
}

void GUI_MyTextEdit::addUserCursor(long userId, QPoint position, QColor color){
    if(cursorsMap.find(userId) != cursorsMap.end()){
        //TODO: gestione intelligente
        //cursorsMap[userId]->updatePosition(position);
        return;
    }
    cursorsMap.insert(userId, new GUI_ColoredCursor(this, position, color));

    //per ridisegnare tutto, nuovo cursore compreso
    this->viewport()->update();
}

void GUI_MyTextEdit::removeUserCursor(long userId){
    if(cursorsMap.find(userId) == cursorsMap.end()){
        //TODO:: gestione intelligente
    }

    cursorsMap.remove(userId);
    //per ridisegnare tutto, nuovo cursore compreso
    this->viewport()->update();
}
