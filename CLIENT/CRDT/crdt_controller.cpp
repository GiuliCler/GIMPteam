#include "crdt_controller.h"
#include "crdt_message.h"
#include "GUI/editorWindow/gui_usersbar.h"
#include <QClipboard>
#include <QMimeData>
#include <iostream>
#include <QScrollBar>

#define BACKWARD_SEL(action) \
    if(textEdit.textCursor().hasSelection() && textEdit.textCursor().position() < textEdit.textCursor().anchor()){ \
        QTextCursor tmp(textEdit.textCursor()); \
        tmp.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor); \
        action \
        rememberFormatChange = true; \
    }

CRDT_controller::CRDT_controller(GIMPdocs *gimpdocs, GUI_Editor *parent, GUI_MyTextEdit& textEdit, int siteId, int siteCounter):
                        gimpDocs(gimpdocs), parent(parent), textEdit(textEdit), highlightUsers(false),
                        crdt{this, gimpDocs->getConnection(), siteId, siteCounter},
                        rememberFormatChange(false), validateSpin(true), validateFontCombo(true) {
    QObject::connect(this->parent, &GUI_Editor::menuTools_event, this, &CRDT_controller::menuCall);
    QObject::connect(this, &CRDT_controller::menuSet, parent, &GUI_Editor::setMenuToolStatus);
    QObject::connect(&this->textEdit, &QTextEdit::currentCharFormatChanged, this, &CRDT_controller::currentCharFormatChanged);
    QObject::connect(&this->textEdit, &QTextEdit::cursorPositionChanged, this, &CRDT_controller::cursorMoved);
    QObject::connect(&this->textEdit, &QTextEdit::selectionChanged, this, &CRDT_controller::selectionChanged);
    QObject::connect(this->textEdit.document(), &QTextDocument::contentsChange, this, &CRDT_controller::contentChanged);
    QObject::connect(parent->childToolsBar->ui->spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &CRDT_controller::setSize);
    QObject::connect(parent->childToolsBar->ui->fontComboBox, &QFontComboBox::currentFontChanged, this, &CRDT_controller::setFont);
    QObject::connect(QApplication::clipboard(), &QClipboard::dataChanged, this, &CRDT_controller::clipboardDataChanged);
    QObject::connect(textEdit.document(), &QTextDocument::undoAvailable, this, &CRDT_controller::undoAvailableChanged);
    QObject::connect(textEdit.document(), &QTextDocument::redoAvailable, this, &CRDT_controller::redoAvailableChanged);
    QObject::connect(parent->childUsersBar, &GUI_UsersBar::highlightingUsers, this, &CRDT_controller::setUsersColors);

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
        fmt.setFontStrikeOut(!textEdit.currentCharFormat().fontStrikeOut());
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
    textEdit.setFocus();
}

void CRDT_controller::undo(){
    textEdit.undo();
    textEdit.setFocus();
}

void CRDT_controller::redo(){
    textEdit.redo();
    textEdit.setFocus();
}

void CRDT_controller::setCurrentTextColor(QColor color){
    textEdit.setTextColor(color);
    textEdit.setFocus();
}

void CRDT_controller::setUsersColors(bool value){

    // Setto il valore di highlightUsers al valore di GUI_Editor->usersColors
    highlightUsers = value;

//    qDebug()<<"setUsersColors chiamata .. flag: "<< highlightUsers;     // DEBUG

    bool processingMessage_prev = processingMessage;
    processingMessage = true;

    QTextCursor current = textEdit.textCursor();
    QTextCursor tmp{textEdit.document()};
    tmp.setPosition(0);

    for(int pos=0; !tmp.atEnd(); tmp.setPosition(++pos)){

        tmp.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
        textEdit.setTextCursor(tmp);

        if(highlightUsers){                 // L'utente vuole vedere il testo colorato con il colore di ogni utente
            textEdit.setTextBackgroundColor(*(parent->getUserColor(crdt.getSiteIdAt(pos))));           // Setto il background color al colore associato all'utente che ha scritto tale simbolo selezionato
//              textEdit.setTextBackgroundColor(QColor{0, 255, 0});       // (colore di prova) TODO: DA RIMUOVERE
        } else {                            // L'utente non vuole vedere più il testo colorato con il colore di ogni utente
            textEdit.setTextBackgroundColor(QColor{255, 255, 255});     // Setto il background color a "white"
        }
    }

    textEdit.setTextCursor(current);

    // Cancello UNDO e REDO stacks
    textEdit.document()->clearUndoRedoStacks();

    processingMessage = processingMessage_prev;
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
    if(processingMessage)                         // TODO: Paolo non sa se è da togliere o no.....
        return;

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

void CRDT_controller::contentChanged(int pos, int del, int add){
    if(processingMessage)
        return;

    textEdit.textCursor().joinPreviousEditBlock();

    if(pos + del - 1 > crdt.getLength() - 1){
        del--;
        add--;
    }

    //    DEBUG: get some info on what has been modified
    std::cout << "pos: " << pos << "; add: " << add << "; del: " << del << std::endl;

    if(del > 0){
        for(int i = pos + del - 1; i >= pos; --i)
            crdt.localErase(i);
    }

    if(add > 0){
        QTextCursor current = textEdit.textCursor();
        QTextCursor tmp{textEdit.document()};

        tmp.setPosition(pos);
        tmp.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, add);
        textEdit.setTextCursor(tmp);
        textEdit.setTextBackgroundColor(QColor{255, 255, 255});     // Setto il background a "white"

        tmp.setPosition(pos+1);

        for(int i = pos; i < pos + add; ++i, tmp.movePosition(QTextCursor::NextCharacter)){
            textEdit.setTextCursor(tmp);
            //std::cout << "Cursor position: " << textEdit.textCursor().position() << std::endl;            // DEBUG
            crdt.localInsert(i, textEdit.toPlainText().at(i), textEdit.currentCharFormat(), textEdit.alignment());
        }

        textEdit.setTextCursor(current);
    }

    int cnt = 0;

//    std::cout << "At end: " << textEdit.textCursor().atEnd() << "; Alignment: " << textEdit.alignment() /* << "; crdt-al: " << crdt.getAlignAt(textEdit.textCursor().position()) */ << std::endl;      // DEBUG
    if(!textEdit.textCursor().atEnd() &&  textEdit.alignment() != crdt.getAlignAt(textEdit.textCursor().position())){
//        std::cout << "At end: " << textEdit.textCursor().atEnd() << "; Alignment: " << textEdit.alignment() << "; crdt-al: " << crdt.getAlignAt(textEdit.textCursor().position()) << std::endl;        // DEBUG
        QTextCursor current = textEdit.textCursor();
        int pos1 = current.position();
        QTextCursor tmp = current;
        //cancello dal fondo del blocco a tmp
        tmp.movePosition(QTextCursor::EndOfBlock);
        for(int i = tmp.position() - 1; i >= pos1 ; --i, ++cnt)
            crdt.localErase(i);

        tmp.setPosition(pos1);
        tmp.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, cnt);
        textEdit.setTextCursor(tmp);
        textEdit.setTextBackgroundColor(QColor{255, 255, 255});     // Setto il background a "white"

        tmp.setPosition(pos1+1);
        // inserisco da tmp a fondo del blocco
        for(int i = pos1; i < pos1 + cnt; ++i, tmp.movePosition(QTextCursor::NextCharacter)){
            textEdit.setTextCursor(tmp);
            //std::cout << "Cursor position: " << textEdit.textCursor().position() << std::endl;                            // DEBUG
            crdt.localInsert(i, textEdit.toPlainText().at(i), textEdit.currentCharFormat(), textEdit.alignment());
        }
//        crdt.print();                                 // DEBUGs
        textEdit.setTextCursor(current);
    }

    if(highlightUsers){
        QTextCursor current = textEdit.textCursor();
        QTextCursor tmp{textEdit.document()};
        tmp.setPosition(pos);
        tmp.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, add+cnt);
        textEdit.setTextCursor(tmp);
        textEdit.setTextBackgroundColor(*(parent->getUserColor(crdt.getSiteIdAt(pos))));           // Setto il background color al colore associato all'utente che ha scritto tale simbolo selezionato
//        textEdit.setTextBackgroundColor(QColor{255, 0, 0});       // (colore di prova) TODO: DA RIMUOVERE
        textEdit.setTextCursor(current);
    }

    textEdit.textCursor().endEditBlock();
}

void CRDT_controller::clipboardDataChanged(){
    if (const QMimeData *md = QApplication::clipboard()->mimeData())
        parent->setMenuToolStatus(md->hasText() ? PASTE_ON : PASTE_OFF);
}

void CRDT_controller::undoAvailableChanged(bool available){
    parent->setMenuToolStatus(available ? UNDO_ON : UNDO_OFF);
}

void CRDT_controller::redoAvailableChanged(bool available){
    parent->setMenuToolStatus(available ? REDO_ON : REDO_OFF);
}

void CRDT_controller::menuCall(menuTools op){
    switch (op) {
        case UNDO_ON:
            undo();
            break;
        case REDO_ON:
            redo();
            break;
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

void CRDT_controller::remoteDelete(int pos, int id_sender){

//    std::cout<<"EHI! SONO NELLA REMOTE DELETE! Position: "<< pos <<std::endl;

    bool processingMessage_prev = processingMessage;
    processingMessage = true;

    textEdit.textCursor().beginEditBlock();

    QTextCursor current = textEdit.textCursor();

    QTextCursor tmp{textEdit.document()};
    tmp.setPosition(pos);
    textEdit.setTextCursor(tmp);

    QPoint position = QPoint (textEdit.cursorRect().topLeft().x(), textEdit.cursorRect().topLeft().y() + textEdit.verticalScrollBar()->value());
    emit updateCursorPosition(id_sender, position);

    textEdit.textCursor().deleteChar();         // ananas DA MODIFICARE: tmp al posto textEdit.textCursor()

    textEdit.setTextCursor(current);

    textEdit.textCursor().endEditBlock();

    processingMessage = processingMessage_prev;
}

void CRDT_controller::remoteInsert(int pos, QChar c, QTextCharFormat fmt, Qt::Alignment align, int id_sender){

//    std::cout<<"EHI! SONO NELLA REMOTE INSERT! Char: "<< c.toLatin1() <<std::endl;

    bool processingMessage_prev = processingMessage;
    processingMessage = true;

    textEdit.textCursor().beginEditBlock();

    QTextCursor current = textEdit.textCursor();              // ananas DA TOGLIERE

    QTextCursor tmp{textEdit.document()};
    tmp.setPosition(pos);
    textEdit.setTextCursor(tmp);                              // ananas TOGLIERE

//    std::cout<<"AAAA TextEdit... cursor: "<<textEdit.textCursor().position()<<", pos: "<<pos<<std::endl;        // DEBUG
    QTextBlockFormat blockFmt{textEdit.textCursor().blockFormat()};

    if(highlightUsers){
        fmt.setBackground(*(parent->getUserColor(crdt.getSiteIdAt(pos))));
//        qDebug()<<"highlightUsers: "<<highlightUsers<<", background color: "<<fmt.background().color();        // DEBUG
//        fmt.setBackground(Qt::blue);        // (colore di prova) TODO: DA RIMUOVERE
    }

    textEdit.textCursor().insertText(c, fmt);
    if(textEdit.alignment() != align){
        blockFmt.setAlignment(align);
        textEdit.textCursor().mergeBlockFormat(blockFmt);
    }
//    std::cout << "Block End: " << textEdit.textCursor().atBlockEnd() << "; Alignment: " << align << std::endl;


    QPoint position = QPoint (textEdit.cursorRect().topLeft().x(), textEdit.cursorRect().topLeft().y() + textEdit.verticalScrollBar()->value());
    emit updateCursorPosition(id_sender, position);

    textEdit.setTextCursor(current);                      // ananas DA TOGLIERE

    textEdit.textCursor().endEditBlock();

    processingMessage = processingMessage_prev;
}
