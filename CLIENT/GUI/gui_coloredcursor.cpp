#include "gui_coloredcursor.h"
#include "gimpdocs.h"

#include <QTextEdit>
#include <QPainter>

GUI_ColoredCursor::GUI_ColoredCursor(QWidget *parent, QPoint position) : QWidget(parent){
    cursorRec = new QRect(position.x(), position.y(), 1, 13);   //ho controllato l'altezza = 10px stampando il parametro di un normale cursore

    //serve a far lampeggiare il finto cursore
    /*cursorVisible = true;
    timer = new QTimer(this);
    timer->start(500);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerSlot()));*/
}

void GUI_ColoredCursor::paintEvent(QPaintEvent *event)
{
    //if (hasFocus()) {
    //if(cursorVisible) {
        const QRect rect(*cursorRec);
        QPainter painter(this);
        painter.fillRect(rect, QColor(255, 0, 0, 255));
    //}
  //}
}

void GUI_ColoredCursor::timerSlot() {
    // non posso invertire la visibilità del cursore in paintEvent perchè non sono sempre io a decidere quando chiamare il paintEvent
    cursorVisible = !cursorVisible;

    //è l'update del widget QTextEdit per poterlo ridisegnare
    this->update();
}

void GUI_ColoredCursor::updatePosition(int x0, int y0){
    cursorRec->setX(x0);
    cursorRec->setY(y0);

    this->update();
}

void GUI_ColoredCursor::triggerPaintEvent(QPaintEvent *event){
    const QRect rect(*cursorRec);
    QPainter painter(static_cast<QTextEdit*>(this->parent())->viewport());
    painter.fillRect(rect, QColor(255, 0, 0, 255));
}
