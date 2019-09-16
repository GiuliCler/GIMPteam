#include "gui_mytextedit.h"

#include <QPainter>
#include <QColor>
#include <QTimer>

GUI_MyTextEdit::GUI_MyTextEdit(QWidget *parent) : QTextEdit(parent) {
    cursorVisible = true;

    this->setCursorWidth(0);

    timer = new QTimer(this);
    timer->start(500);
    //connect(this, SIGNAL(sendUpdate()), this, SLOT(update()));
    connect(timer, SIGNAL(timeout()), this, SLOT(timerSlot()));
}

void GUI_MyTextEdit::paintEvent(QPaintEvent *event)
{
  // questo serve a disegnare tutto quanto il resto. Normalmente disegnerebbe anche il sursore nero, ma gli ho messo spessore 0
  QTextEdit::paintEvent(event);
  // disegno il cursore a intermittenza
  if (hasFocus()) {
    if(cursorVisible) {

        const QRect curRect = cursorRect(textCursor());
        const QRect fakeRect(curRect.x(), curRect.y(), 1, curRect.height());
        QPainter painter(viewport());
        painter.fillRect(fakeRect, QColor(255, 0, 0, 255));
    }
  }
}

void GUI_MyTextEdit::timerSlot() {
    // non posso invertire la visibilità del cursore in paintEvent perchè non sono sempre io a decidere quando chiamare il paintEvent
    cursorVisible = !cursorVisible;

    //è l'update del widget QTextEdit per poterlo ridisegnare
    this->update();
}
