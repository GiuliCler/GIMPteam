#include "gui_coloredcursor.h"
#include "../gimpdocs.h"

#include <QTextEdit>
#include <QPainter>
#include <QScrollBar>

GUI_ColoredCursor::GUI_ColoredCursor(QWidget *parent, QPoint position, QColor color) : QObject(parent){
    textEditParent = static_cast<QTextEdit*>(parent);

    cursorPosition = position;
    cursorColor = color;
}

void GUI_ColoredCursor::updatePosition(QPoint position){
    cursorPosition = position;
    textEditParent->viewport()->update();
}

void GUI_ColoredCursor::paint(){
    //visto che la dimensione del font può cambiare, di volta in volta ricalcolo le dimensioni del cursore
    QRect modelRect = textEditParent->cursorRect();
    /*
     * la "x" è leggermente spostata a sx, così mi metto in mezzo a 2 lettere e non copro troppo quella di DX
     * la "y" deve tener conto deldisplacement della scrollbar, altrimenti mi mette tutte le coordinate in funzione della sola viewport ed i cursori poi non scrollano più
     * la width è doppia altrimenti non si riescono a vedere
     * la height è ridotta così se si sovrappone al vero cirsore non lo copre del tutto, anche se dovrebbero essere trasparenti
     * */
    const QRect rect(cursorPosition.x() - modelRect.width()/2, cursorPosition.y() - textEditParent->verticalScrollBar()->value(), modelRect.width()*2, modelRect.height()*3/4);
    QPainter painter(textEditParent->viewport());
    painter.fillRect(rect, cursorColor);
}
