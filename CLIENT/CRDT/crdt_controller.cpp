#include "crdt_controller.h"
#include <iostream>

CRDT_controller::CRDT_controller(GUI_Editor *parent, GUI_MyTextEdit& textEdit): textEdit(textEdit), rememberFormatChange(false){
    QObject::connect(parent, &GUI_Editor::menuTools_event, this, &CRDT_controller::menuCall);
    QObject::connect(this, &CRDT_controller::menuSet, parent, &GUI_Editor::setMenuToolStatus);
    QObject::connect(&this->textEdit, &QTextEdit::currentCharFormatChanged, this, &CRDT_controller::currentCharFormatChanged);
    QObject::connect(&this->textEdit, &QTextEdit::cursorPositionChanged, this, &CRDT_controller::cursorMoved);
    QObject::connect(this->textEdit.document(), &QTextDocument::contentsChange, this, &CRDT_controller::contentChanged);
}

void CRDT_controller::setLeft(){}
void CRDT_controller::setCenter(){}
void CRDT_controller::setRight(){}
void CRDT_controller::setJustified(){}

void CRDT_controller::setBold(){}
void CRDT_controller::setItalic(){
    if(textEdit.textCursor().hasSelection() && textEdit.textCursor().position() < textEdit.textCursor().anchor()){
        QTextCursor tmp(textEdit.textCursor());
        tmp.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
        textEdit.setFontItalic(!tmp.charFormat().fontItalic());
        rememberFormatChange = true;
    } else
        textEdit.setFontItalic(!textEdit.fontItalic());
    textEdit.setFocus();
}
void CRDT_controller::setStrikethrough(){}
void CRDT_controller::setUnderlined(){}

void CRDT_controller::setSize(int size){}
void CRDT_controller::setFont(const QFont &f){}

void CRDT_controller::copy(){}
void CRDT_controller::cut(){}
void CRDT_controller::paste(){}

void CRDT_controller::setTextColor(QColor color){}

void CRDT_controller::currentCharFormatChanged(const QTextCharFormat &format){
    if(textEdit.textCursor().hasSelection() && textEdit.textCursor().position() < textEdit.textCursor().anchor()){
        QTextCursor tmp = textEdit.textCursor();
        tmp.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
        emit menuSet(tmp.charFormat().fontItalic() ? menuTools::ITALIC_ON : menuTools::ITALIC_OFF);
        rememberFormatChange = true;
    } else
        emit menuSet(format.fontItalic() ? menuTools::ITALIC_ON : menuTools::ITALIC_OFF);
}

void CRDT_controller::cursorMoved(){
    if(rememberFormatChange){
        rememberFormatChange = false;
        currentCharFormatChanged(textEdit.currentCharFormat());
    }
}
void CRDT_controller::contentChanged(int pos, int add, int del){}


void CRDT_controller::menuCall(menuTools op){
    switch (op) {
        case A_LEFT:
            setLeft();
            break;
        case A_CENTER:
            setCenter();
            break;
        case A_RIGHT:
            setRight();
            break;
        case A_JUSTIFIED:
            setJustified();
            break;
        case BOLD_ON:
            setBold();
            break;
        case ITALIC_ON:
            setItalic();
            break;
        case UNDERLINED_ON:
            setUnderlined();
            break;
        case STRIKETHROUGH_ON:
            setStrikethrough();
            break;
    }
}
