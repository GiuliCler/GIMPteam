#include "gui_mytextedit.h"
#include "gimpdocs.h"

#include <QPainter>
#include <QColor>
#include <QTimer>

GUI_MyTextEdit::GUI_MyTextEdit(QWidget *parent) : QTextEdit(parent) {
    this->setObjectName(GUI_MyTextEdit::getObjectName());
    //per non farsi coprire dai cursori colorati
    this->setCursorWidth(2);
}

void GUI_MyTextEdit::paintEvent(QPaintEvent *event)
{
  // questo serve a disegnare tutto quanto il resto. Normalmente disegnerebbe anche il cursore nero, ma gli ho messo spessore 0
  QTextEdit::paintEvent(event);

  for(auto pair = cursorsMap.begin(); pair != cursorsMap.end(); pair++){
      pair.value()->triggerPaintEvent(event);
  }
}

void GUI_MyTextEdit::addUserCursor(long userId, QPoint position){
    cursorsMap.insert(userId, new GUI_ColoredCursor(this, position));

    //per ridisegnare tutto, nuovo cursore compreso
    this->update();
}
