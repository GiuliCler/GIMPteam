#include "crdt_controller.h"
#define BACKWARD_SEL(action) \
    if(textEdit.textCursor().hasSelection() && textEdit.textCursor().position() < textEdit.textCursor().anchor()){ \
        QTextCursor tmp(textEdit.textCursor()); \
        tmp.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor); \
        action \
        rememberFormatChange = true; \
    }

CRDT_controller::CRDT_controller(GUI_Editor *parent, GUI_MyTextEdit& textEdit): textEdit(textEdit), rememberFormatChange(false){
    QObject::connect(parent, &GUI_Editor::menuTools_event, this, &CRDT_controller::menuCall);
    QObject::connect(this, &CRDT_controller::menuSet, parent, &GUI_Editor::setMenuToolStatus);
    QObject::connect(&this->textEdit, &QTextEdit::currentCharFormatChanged, this, &CRDT_controller::currentCharFormatChanged);
    QObject::connect(&this->textEdit, &QTextEdit::cursorPositionChanged, this, &CRDT_controller::cursorMoved);
    QObject::connect(&this->textEdit, &QTextEdit::selectionChanged, this, &CRDT_controller::selectionChanged);
    QObject::connect(this->textEdit.document(), &QTextDocument::contentsChange, this, &CRDT_controller::contentChanged);
}

void CRDT_controller::setLeft(){}
void CRDT_controller::setCenter(){}
void CRDT_controller::setRight(){}
void CRDT_controller::setJustified(){}

void CRDT_controller::setBold(){
    BACKWARD_SEL(textEdit.setFontWeight(tmp.charFormat().fontWeight() >= QFont::Bold ? QFont::Normal : QFont::Bold);)
    else
        textEdit.setFontWeight(textEdit.fontWeight() >= QFont::Bold ? QFont::Normal : QFont::Bold);
    textEdit.setFocus();
}
void CRDT_controller::setItalic(){
    BACKWARD_SEL(textEdit.setFontItalic(!tmp.charFormat().fontItalic());)
    else
        textEdit.setFontItalic(!textEdit.fontItalic());
    textEdit.setFocus();
}
void CRDT_controller::setStrikethrough(){
    QTextCharFormat fmt;
    BACKWARD_SEL(fmt.setFontStrikeOut(!tmp.charFormat().fontStrikeOut());)
    else
        fmt.setFontStrikeOut(!textEdit.fontItalic());
    textEdit.mergeCurrentCharFormat(fmt);
    textEdit.setFocus();
}
void CRDT_controller::setUnderlined(){
    BACKWARD_SEL(textEdit.setFontUnderline(!tmp.charFormat().fontUnderline());)
    else
        textEdit.setFontUnderline(!textEdit.fontUnderline());
    textEdit.setFocus();
}

void CRDT_controller::setSize(int size){}
void CRDT_controller::setFont(const QFont &f){}

void CRDT_controller::copy(){}
void CRDT_controller::cut(){}
void CRDT_controller::paste(){}

void CRDT_controller::setTextColor(QColor color){}

void CRDT_controller::currentCharFormatChanged(const QTextCharFormat &format){
    BACKWARD_SEL(
                emit menuSet(tmp.charFormat().fontItalic() ? menuTools::ITALIC_ON : menuTools::ITALIC_OFF);
                emit menuSet(tmp.charFormat().fontStrikeOut() ? menuTools::STRIKETHROUGH_ON : menuTools::STRIKETHROUGH_OFF);
                emit menuSet(tmp.charFormat().fontUnderline() ? menuTools::UNDERLINED_ON : menuTools::UNDERLINED_OFF);
                emit menuSet(tmp.charFormat().fontWeight() >= QFont::Bold ? menuTools::BOLD_ON : menuTools::BOLD_OFF);
            )
    else{
        emit menuSet(format.fontItalic() ? menuTools::ITALIC_ON : menuTools::ITALIC_OFF);
        emit menuSet(format.fontStrikeOut() ? menuTools::STRIKETHROUGH_ON : menuTools::STRIKETHROUGH_OFF);
        emit menuSet(format.fontUnderline() ? menuTools::UNDERLINED_ON : menuTools::UNDERLINED_OFF);
        emit menuSet(format.fontWeight() >= QFont::Bold ? menuTools::BOLD_ON : menuTools::BOLD_OFF);
    }
}

void CRDT_controller::cursorMoved(){
    if(rememberFormatChange){
        rememberFormatChange = false;
        currentCharFormatChanged(textEdit.currentCharFormat());
    }
}
void CRDT_controller::selectionChanged(){
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
