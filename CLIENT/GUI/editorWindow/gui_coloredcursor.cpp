#include "gui_coloredcursor.h"
#include "../gimpdocs.h"

#include <QTextEdit>
#include <QPainter>
#include <QScrollBar>

GUI_ColoredCursor::GUI_ColoredCursor(QWidget *parent, QPoint position, QColor color) : QObject(parent){
    textEditParent = static_cast<QTextEdit*>(parent);

    cursorPosition = position;
    cursorColor = color;
    cursorColor.setAlpha(180);
}

void GUI_ColoredCursor::updatePosition(QPoint position){
    cursorPosition = position;
    static_cast<QTextEdit*>(this->parent())->viewport()->update();
}

void GUI_ColoredCursor::paint(){
    //visto che la dimensione del font può cambiare, di volta in volta ricalcolo le dimensioni del cursore
    QRect modelRect = textEditParent->cursorRect();
    const QRect rect(cursorPosition.x() - modelRect.width()/2, cursorPosition.y() - textEditParent->verticalScrollBar()->value(), modelRect.width()*2, modelRect.height()*3/4);
    QPainter painter(textEditParent->viewport());
    painter.fillRect(rect, cursorColor);
}
