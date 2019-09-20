#include "gui_coloredcursor.h"
#include "../gimpdocs.h"

#include <QTextEdit>
#include <QPainter>

GUI_ColoredCursor::GUI_ColoredCursor(QWidget *parent, QPoint position, QColor color) : QWidget(parent){
    cursorPosition = position;
    cursorColor = color;
}

void GUI_ColoredCursor::updatePosition(QPoint position){
    cursorPosition = position;
    static_cast<QTextEdit*>(this->parent())->viewport()->update();
}

void GUI_ColoredCursor::paint(){
    //visto ch la dimensione del font può cambiare, di volta in volta ricalcolo le dimensioni del cursore
    QRect modelRect = static_cast<QTextEdit*>(this->parent())->cursorRect();
    const QRect rect(cursorPosition.x(), cursorPosition.y(), modelRect.width(), modelRect.height() -1);
    QPainter painter(static_cast<QTextEdit*>(this->parent())->viewport());
    painter.fillRect(rect, cursorColor);
}
