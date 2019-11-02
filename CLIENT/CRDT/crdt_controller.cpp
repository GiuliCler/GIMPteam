#include "crdt_controller.h"
#include <iostream>

CRDT_controller::CRDT_controller(GUI_MyTextEdit& textEdit, GUI_ToolsBar& toolbar): textEdit(textEdit), toolbar(toolbar), rememberFormatChange(false){
    QObject::connect(this->toolbar.findChild<QPushButton*>("alignLeftPushButton"), &QPushButton::clicked, this, &CRDT_controller::setLeft);
    QObject::connect(this->toolbar.findChild<QPushButton*>("alignCenterPushButton"), &QPushButton::clicked, this, &CRDT_controller::setCenter);
    QObject::connect(this->toolbar.findChild<QPushButton*>("alignRightPushButton"), &QPushButton::clicked, this, &CRDT_controller::setRight);
    QObject::connect(this->toolbar.findChild<QPushButton*>("alignJustifiedPushButton"), &QPushButton::clicked, this, &CRDT_controller::setJustified);

    QObject::connect(this->toolbar.findChild<QPushButton*>("boldPushButton"), &QPushButton::clicked, this, &CRDT_controller::setBold);
    QObject::connect(this->toolbar.findChild<QPushButton*>("italicPushButton"), &QPushButton::clicked, this, &CRDT_controller::setItalic);
    QObject::connect(this->toolbar.findChild<QPushButton*>("strikethroughPushButton"), &QPushButton::clicked, this, &CRDT_controller::setStrikethrough);
    QObject::connect(this->toolbar.findChild<QPushButton*>("underlinedPushButton"), &QPushButton::clicked, this, &CRDT_controller::setUnderlined);

    QObject::connect(this->toolbar.findChild<QSpinBox*>("spinBox"), QOverload<int>::of(&QSpinBox::valueChanged), this, &CRDT_controller::setSize);
    QObject::connect(this->toolbar.findChild<QFontComboBox*>("fontComboBox"), &QFontComboBox::currentFontChanged, this, &CRDT_controller::setFont);

    QObject::connect(this->toolbar.findChild<QPushButton*>("copyPushButton"), &QPushButton::clicked, this, &CRDT_controller::copy);
    QObject::connect(this->toolbar.findChild<QPushButton*>("cutPushButton"), &QPushButton::clicked, this, &CRDT_controller::cut);
    QObject::connect(this->toolbar.findChild<QPushButton*>("pastePushButton"), &QPushButton::clicked, this, &CRDT_controller::paste);

    QObject::connect(this->toolbar.findChild<QPushButton*>("colorPushButton"), &QPushButton::clicked, this, &CRDT_controller::setTextColor);

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
        toolbar.findChild<QPushButton*>("italicPushButton")->setChecked(tmp.charFormat().fontItalic());
        rememberFormatChange = true;
    } else
        toolbar.findChild<QPushButton*>("italicPushButton")->setChecked(format.fontItalic());
}

void CRDT_controller::cursorMoved(){
    if(rememberFormatChange){
        rememberFormatChange = false;
        currentCharFormatChanged(textEdit.currentCharFormat());
    }
}
void CRDT_controller::contentChanged(int pos, int add, int del){}
