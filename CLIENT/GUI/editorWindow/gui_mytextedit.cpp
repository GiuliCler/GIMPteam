#include "gui_mytextedit.h"
#include "gui_editor.h"
#include <QColor>
#include <QFont>
#include <QPalette>
#include <QMimeData>
#include <QRegularExpression>

GUI_MyTextEdit::GUI_MyTextEdit(QWidget *parent) : QTextEdit(parent) {
    this->setObjectName(GUI_MyTextEdit::getObjectName());
    editorParent = static_cast<GUI_Editor*>(parent);

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


void GUI_MyTextEdit::insertFromMimeData (const QMimeData * constClipboard){
    if(constClipboard == nullptr)
        return;

    if(constClipboard->hasHtml()){
        //Se il testo da incollare ha un formato in html, provo a rimuovere eventuali evidenziazioni colorate
        //rimuovendolo a mano dalla stringa. Funziona solo con una precisa sintassi, quindi solo se il testo era stato copiato da gimpdocs
        QString newhtmlString = "";
        QVector<QStringRef> htmlsplitted = constClipboard->html().splitRef(QRegularExpression("background-color.*?;"));

        for(auto string = htmlsplitted.begin(); string != htmlsplitted.end(); string++)
            newhtmlString.append(*string);

        QMimeData *clipboard = const_cast<QMimeData *>(constClipboard);
        clipboard->setHtml(newhtmlString);
        QTextEdit::insertFromMimeData(const_cast<const QMimeData *>(clipboard));
    }
    else
        QTextEdit::insertFromMimeData(constClipboard);
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
