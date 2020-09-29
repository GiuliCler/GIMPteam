#include "gui_mytextedit.h"
#include "gui_editor.h"
#include <QColor>
#include <QFont>
#include <QPalette>

GUI_MyTextEdit::GUI_MyTextEdit(QWidget *parent) : QTextEdit(parent) {
    this->setObjectName(GUI_MyTextEdit::getObjectName());
    editorParent = static_cast<GUI_Editor*>(parent);

    installEventFilter(this);

    QPalette palette = this->palette();
    palette.setColor(QPalette::Inactive, QPalette::Highlight, palette.color(QPalette::Active, QPalette::Highlight));
    this->setPalette(palette);
}

void GUI_MyTextEdit::setupTextEdit(){
    //devo mettere il setFocus in una funzione chiamata successivamente al costruttore perchè sì, altrimenti mi cancella il focus
    this->setFocus();
    this->setCursorWidth(2);

    QFont font = this->font();
    font.setPointSize(12);
    this->setFont(font);

    currentCharFormatChanged(this->currentCharFormat());
    cursorPositionChanged();
    this->document()->clearUndoRedoStacks();
}

void GUI_MyTextEdit::paintEvent(QPaintEvent *event){
    // questo serve a disegnare tutto quanto il resto normalmente
    QTextEdit::paintEvent(event);

    //e qui do l'ordine di disegnare sopra al foglio i cursori secondari
    for(auto pair = cursorsMap.begin(); pair != cursorsMap.end(); pair++)
      pair.value()->paint();
}

void GUI_MyTextEdit::addUserCursor(int userId, QPoint position, QColor color){
    if(cursorsMap.find(userId) != cursorsMap.end())
        return;

    cursorsMap.insert(userId, new GUI_ColoredCursor(this, position, color));
    //per ridisegnare tutto, nuovo cursore soprattutto
    this->viewport()->update();
}

void GUI_MyTextEdit::removeUserCursor(int userId){
    if(cursorsMap.find(userId) == cursorsMap.end())
        return;

    cursorsMap.remove(userId);
    this->viewport()->update();
}

void GUI_MyTextEdit::on_updateCursorPosition_emitted(int userId, QPoint position){
    if(cursorsMap.find(userId) == cursorsMap.end())
        return;

    cursorsMap[userId]->updatePosition(position);
}

bool GUI_MyTextEdit::eventFilter(QObject *watched, QEvent *event){

    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);

        if (keyEvent->matches(QKeySequence::Paste)){
            editorParent->on_actionPaste();
            return true;
        }
    }

    return false;
}
