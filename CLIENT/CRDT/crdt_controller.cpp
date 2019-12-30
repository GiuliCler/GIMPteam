#include "crdt_controller.h"
#include <QClipboard>
#include <QMimeData>

#define BACKWARD_SEL(action) \
    if(textEdit.textCursor().hasSelection() && textEdit.textCursor().position() < textEdit.textCursor().anchor()){ \
        QTextCursor tmp(textEdit.textCursor()); \
        tmp.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor); \
        action \
        rememberFormatChange = true; \
    }

CRDT_controller::CRDT_controller(GUI_Editor *parent, GUI_MyTextEdit& textEdit): parent(parent), textEdit(textEdit),
                        rememberFormatChange(false), validateSpin(true), validateFontCombo(true){
    QObject::connect(this->parent, &GUI_Editor::menuTools_event, this, &CRDT_controller::menuCall);
    QObject::connect(this, &CRDT_controller::menuSet, parent, &GUI_Editor::setMenuToolStatus);
    QObject::connect(&this->textEdit, &QTextEdit::currentCharFormatChanged, this, &CRDT_controller::currentCharFormatChanged);
    QObject::connect(&this->textEdit, &QTextEdit::cursorPositionChanged, this, &CRDT_controller::cursorMoved);
    QObject::connect(&this->textEdit, &QTextEdit::selectionChanged, this, &CRDT_controller::selectionChanged);
    QObject::connect(this->textEdit.document(), &QTextDocument::contentsChange, this, &CRDT_controller::contentChanged);
    QObject::connect(parent->childToolsBar->ui->spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &CRDT_controller::setSize);
    QObject::connect(parent->childToolsBar->ui->fontComboBox, &QFontComboBox::currentFontChanged, this, &CRDT_controller::setFont);
    connect(QApplication::clipboard(), &QClipboard::dataChanged, this, &CRDT_controller::clipboardDataChanged);

    parent->childToolsBar->ui->spinBox->setSpecialValueText("Default");
}

void CRDT_controller::setLeft(){
    textEdit.setAlignment(Qt::AlignLeft);
    emit menuSet(menuTools::A_LEFT);
}
void CRDT_controller::setCenter(){
    textEdit.setAlignment(Qt::AlignCenter);
    emit menuSet(menuTools::A_CENTER);
}
void CRDT_controller::setRight(){
    textEdit.setAlignment(Qt::AlignRight);
    emit menuSet(menuTools::A_RIGHT);
}
void CRDT_controller::setJustified(){
    textEdit.setAlignment(Qt::AlignJustify);
    emit menuSet(menuTools::A_JUSTIFIED);
}

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

void CRDT_controller::setSize(int size){
    if(validateSpin)
        textEdit.setFontPointSize(size);
    else
        validateSpin = true;
    textEdit.setFocus();
}

void CRDT_controller::setFont(const QFont &f){
    if(validateFontCombo){
        textEdit.setCurrentFont(f);
    } else
        validateFontCombo = true;
    textEdit.setFocus();
}

void CRDT_controller::copy(){
    textEdit.copy();
}

void CRDT_controller::cut(){
    textEdit.cut();
}

void CRDT_controller::paste(){
    textEdit.paste();
}

void CRDT_controller::setCurrentTextColor(QColor color){
    textEdit.setTextColor(color);
    textEdit.setFocus();
}

void CRDT_controller::currentCharFormatChanged(const QTextCharFormat &format){
    BACKWARD_SEL(
                emit menuSet(tmp.charFormat().fontItalic() ? menuTools::ITALIC_ON : menuTools::ITALIC_OFF);
                emit menuSet(tmp.charFormat().fontStrikeOut() ? menuTools::STRIKETHROUGH_ON : menuTools::STRIKETHROUGH_OFF);
                emit menuSet(tmp.charFormat().fontUnderline() ? menuTools::UNDERLINED_ON : menuTools::UNDERLINED_OFF);
                emit menuSet(tmp.charFormat().fontWeight() >= QFont::Bold ? menuTools::BOLD_ON : menuTools::BOLD_OFF);
                parent->childToolsBar->setTextColorIconColor(tmp.charFormat().foreground().color());
                if(static_cast<int>(tmp.charFormat().fontPointSize()) != parent->childToolsBar->ui->spinBox->value()){
                    validateSpin = false;
                    parent->childToolsBar->ui->spinBox->setValue(static_cast<int>(tmp.charFormat().fontPointSize()));
                    if(parent->childToolsBar->ui->spinBox->value() == parent->childToolsBar->ui->spinBox->minimum()){
                        validateSpin = false;
                        parent->childToolsBar->ui->spinBox->setValue(12); // TODO define a default font size?
                    }
                }
                if(tmp.charFormat().font() != parent->childToolsBar->ui->fontComboBox->currentFont()){
                    validateFontCombo = false;
                    parent->childToolsBar->ui->fontComboBox->setCurrentFont(tmp.charFormat().font());
                }
            )
    else{
        emit menuSet(format.fontItalic() ? menuTools::ITALIC_ON : menuTools::ITALIC_OFF);
        emit menuSet(format.fontStrikeOut() ? menuTools::STRIKETHROUGH_ON : menuTools::STRIKETHROUGH_OFF);
        emit menuSet(format.fontUnderline() ? menuTools::UNDERLINED_ON : menuTools::UNDERLINED_OFF);
        emit menuSet(format.fontWeight() >= QFont::Bold ? menuTools::BOLD_ON : menuTools::BOLD_OFF);

        parent->childToolsBar->setTextColorIconColor(format.foreground().color());
        if(static_cast<int>(textEdit.fontPointSize()) != parent->childToolsBar->ui->spinBox->value()){
            if(textEdit.textCursor().hasSelection())
                validateSpin = false;
            parent->childToolsBar->ui->spinBox->setValue(static_cast<int>(textEdit.fontPointSize()));
            if(parent->childToolsBar->ui->spinBox->value() == parent->childToolsBar->ui->spinBox->minimum()){
                if(textEdit.textCursor().hasSelection())
                    validateSpin = false;
                parent->childToolsBar->ui->spinBox->setValue(12); // TODO define a default font size?
            }
        }
        if(textEdit.currentFont() != parent->childToolsBar->ui->fontComboBox->currentFont()) {
            if(textEdit.textCursor().hasSelection())
                validateFontCombo = false;
            parent->childToolsBar->ui->fontComboBox->setCurrentFont(textEdit.currentFont());
        }
    }
}

void CRDT_controller::cursorMoved(){
    switch (textEdit.alignment()) {
        case Qt::AlignLeft:
            emit menuSet(menuTools::A_LEFT);
            break;
        case Qt::AlignCenter:
            emit menuSet(menuTools::A_CENTER);
            break;
        case Qt::AlignRight:
            emit menuSet(menuTools::A_RIGHT);
            break;
        case Qt::AlignJustify:
            emit menuSet(menuTools::A_JUSTIFIED);
            break;
    }

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

    if(textEdit.textCursor().hasSelection()){
        parent->setMenuToolStatus(CUT_ON);
        parent->setMenuToolStatus(COPY_ON);
    } else {
        parent->setMenuToolStatus(CUT_OFF);
        parent->setMenuToolStatus(COPY_OFF);
    }
}
void CRDT_controller::contentChanged(int pos, int add, int del){}

void CRDT_controller::clipboardDataChanged(){
    if (const QMimeData *md = QApplication::clipboard()->mimeData())
        parent->setMenuToolStatus(md->hasText() ? PASTE_ON : PASTE_OFF);
}

void CRDT_controller::menuCall(menuTools op){
    switch (op) {
        case COPY_ON:
            copy();
            break;
        case CUT_ON:
            cut();
            break;
        case PASTE_ON:
            paste();
            break;
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
        default:
            break;
    }
}
