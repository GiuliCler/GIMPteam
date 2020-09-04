#include "crdt_controller.h"
#include "crdt_message.h"
#include "GUI/editorWindow/gui_usersbar.h"
#include <QClipboard>
#include <QMimeData>
#include <iostream>
#include <QScrollBar>

//MIRKO: ti servirà anche questa
//#include <QScrollBar>


CRDT_controller::CRDT_controller(GIMPdocs *gimpdocs, GUI_Editor *parent, GUI_MyTextEdit& textEdit, int siteId, int siteCounter):
                        gimpDocs(gimpdocs), parent(parent), connection(gimpDocs->getConnection()), textEdit(textEdit), highlightUsers(false),
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
    QObject::connect(connection, &connection_to_server::sigMoveCursor, this, &CRDT_controller::remoteMove);

    parent->childToolsBar->ui->spinBox->setSpecialValueText("Default");
}


void CRDT_controller::setLeft(){
    textEdit.setAlignment(Qt::AlignLeft);
    emit menuSet(menuTools::A_LEFT);
    cursorMoved();
}

void CRDT_controller::setCenter(){
    textEdit.setAlignment(Qt::AlignCenter);
    emit menuSet(menuTools::A_CENTER);
    cursorMoved();
}

void CRDT_controller::setRight(){
    textEdit.setAlignment(Qt::AlignRight);
    emit menuSet(menuTools::A_RIGHT);
    cursorMoved();
}

void CRDT_controller::setJustified(){
    textEdit.setAlignment(Qt::AlignJustify);
    emit menuSet(menuTools::A_JUSTIFIED);
    cursorMoved();
}


void CRDT_controller::setBold(){
    if(textEdit.textCursor().hasSelection() && textEdit.textCursor().position() < textEdit.textCursor().anchor()){
        QTextCursor tmp(textEdit.textCursor());
        tmp.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
        textEdit.setFontWeight(tmp.charFormat().fontWeight() >= QFont::Bold ? QFont::Normal : QFont::Bold);
        rememberFormatChange = true;
    }
    else
        textEdit.setFontWeight(textEdit.fontWeight() >= QFont::Bold ? QFont::Normal : QFont::Bold);
    textEdit.setFocus();
}

void CRDT_controller::setItalic(){
    if(textEdit.textCursor().hasSelection() && textEdit.textCursor().position() < textEdit.textCursor().anchor()){
        QTextCursor tmp(textEdit.textCursor());
        tmp.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
        textEdit.setFontItalic(!tmp.charFormat().fontItalic());
        rememberFormatChange = true;
    }
    else
        textEdit.setFontItalic(!textEdit.fontItalic());
    textEdit.setFocus();
}

void CRDT_controller::setStrikethrough(){
    QTextCharFormat fmt;
    if(textEdit.textCursor().hasSelection() && textEdit.textCursor().position() < textEdit.textCursor().anchor()){
        QTextCursor tmp(textEdit.textCursor());
        tmp.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
        fmt.setFontStrikeOut(!tmp.charFormat().fontStrikeOut());
        rememberFormatChange = true;
    }
    else
        fmt.setFontStrikeOut(!textEdit.currentCharFormat().fontStrikeOut());
    textEdit.mergeCurrentCharFormat(fmt);
    textEdit.setFocus();
}

void CRDT_controller::setUnderlined(){
    if(textEdit.textCursor().hasSelection() && textEdit.textCursor().position() < textEdit.textCursor().anchor()){
        QTextCursor tmp(textEdit.textCursor());
        tmp.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
        textEdit.setFontUnderline(!tmp.charFormat().fontUnderline());
        rememberFormatChange = true;
    }
    else
        textEdit.setFontUnderline(!textEdit.fontUnderline());
    textEdit.setFocus();
}

void CRDT_controller::setSize(int size){
    if(validateSpin){
        if(size > 0)
            textEdit.setFontPointSize(size);
        else
            parent->childToolsBar->ui->spinBox->setValue(defaultFontPointSize);
    }else
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

    QTextCursor tmp{textEdit.document()};
    tmp.setPosition(0);

    for(int pos=0; !tmp.atEnd(); tmp.setPosition(++pos)){

        tmp.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);

        QTextCharFormat fmt{tmp.charFormat()};
        if(highlightUsers){                 // L'utente vuole vedere il testo colorato con il colore di ogni utente
            fmt.setBackground(*(parent->getUserColor(crdt.getSiteIdAt(pos))));          // Setto il background color al colore associato all'utente che ha scritto tale simbolo selezionato
        } else {                            // L'utente non vuole vedere più il testo colorato con il colore di ogni utente
            fmt.setBackground(Qt::BrushStyle::NoBrush);     // Setto il background color a "white"
        }
        tmp.mergeCharFormat(fmt);
    }

    if(highlightUsers && textEdit.textBackgroundColor() == Qt::BrushStyle::NoBrush)
        textEdit.setTextBackgroundColor(*(parent->getUserColor(crdt.getSiteId())));

    if(!highlightUsers && textEdit.textBackgroundColor() != Qt::BrushStyle::NoBrush)
        textEdit.setTextBackgroundColor(Qt::BrushStyle::NoBrush);

    // Cancello UNDO e REDO stacks
    textEdit.document()->clearUndoRedoStacks();

    processingMessage = processingMessage_prev;
}


void CRDT_controller::currentCharFormatChanged(const QTextCharFormat &format){
    if(textEdit.textCursor().hasSelection() && textEdit.textCursor().position() < textEdit.textCursor().anchor()){
        QTextCursor tmp(textEdit.textCursor());
        tmp.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
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
                parent->childToolsBar->ui->spinBox->setValue(defaultFontPointSize);
            }
        }
        if(tmp.charFormat().font() != parent->childToolsBar->ui->fontComboBox->currentFont()){
            validateFontCombo = false;
            parent->childToolsBar->ui->fontComboBox->setCurrentFont(tmp.charFormat().font());
        }
        rememberFormatChange = true;
    }else{
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
                parent->childToolsBar->ui->spinBox->setValue(defaultFontPointSize);
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

    connection->requestSendMovedCursor(crdt.getSiteId(), textEdit.textCursor().position());
}

void CRDT_controller::selectionChanged(){
    if(processingMessage)
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

    QTextCursor tmp{textEdit.document()};
    bool mustClearStacks = false;

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
        tmp.setPosition(pos);
        for(int i = pos; i < pos + add; tmp.setPosition(++i)){
            tmp.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
            if(tmp.charFormat().background() != Qt::BrushStyle::NoBrush && tmp.charFormat().background() != Qt::white){
                QTextCharFormat fmt{tmp.charFormat()};
                fmt.setBackground(Qt::BrushStyle::NoBrush);
                tmp.mergeCharFormat(fmt);
                mustClearStacks = true;
            }
        }

        tmp.setPosition(pos+1);

        for(int i = pos; i < pos + add; ++i, tmp.movePosition(QTextCursor::NextCharacter)){
            //std::cout << "Cursor position: " << textEdit.textCursor().position() << std::endl;                        // DEBUG
            crdt.localInsert(i, textEdit.toPlainText().at(i), tmp.charFormat(), tmp.blockFormat().alignment());
        }
    }

    int cnt = 0;

//    std::cout << "At end: " << textEdit.textCursor().atEnd() << "; Alignment: " << textEdit.alignment() /* << "; crdt-al: " << crdt.getAlignAt(textEdit.textCursor().position()) */ << std::endl;      // DEBUG
    if(!tmp.atEnd() &&  tmp.blockFormat().alignment() != crdt.getAlignAt(tmp.position())){
//        std::cout << "At end: " << textEdit.textCursor().atEnd() << "; Alignment: " << textEdit.alignment() << "; crdt-al: " << crdt.getAlignAt(textEdit.textCursor().position()) << std::endl;        // DEBUG
        int pos1 = textEdit.textCursor().position();
        tmp = textEdit.textCursor();
        //cancello dal fondo del blocco a tmp
        tmp.movePosition(QTextCursor::EndOfBlock);
        for(int i = tmp.position() - 1; i >= pos1 ; --i, ++cnt)
            crdt.localErase(i);

        tmp.setPosition(pos1);
        for(int i = pos1; i < pos1 + cnt; tmp.setPosition(++i)){
            tmp.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
            if(tmp.charFormat().background() != Qt::BrushStyle::NoBrush && tmp.charFormat().background() != Qt::white){
                QTextCharFormat fmt{tmp.charFormat()};
                fmt.setBackground(Qt::BrushStyle::NoBrush);
                tmp.mergeCharFormat(fmt);
                mustClearStacks = true;
            }
        }

        tmp.setPosition(pos1+1);
        // inserisco da tmp a fondo del blocco
        for(int i = pos1; i < pos1 + cnt; ++i, tmp.movePosition(QTextCursor::NextCharacter)){
            //std::cout << "Cursor position: " << textEdit.textCursor().position() << std::endl;                            // DEBUG
            crdt.localInsert(i, textEdit.toPlainText().at(i), tmp.charFormat(), tmp.blockFormat().alignment());
        }
//        crdt.print();                                 // DEBUG
    }

    if(highlightUsers){
        mustClearStacks = true;
        tmp.setPosition(pos);

        if(add+cnt > 0){
            for(int i = pos; i < pos + add + cnt; tmp.setPosition(++i)){
                tmp.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
                QTextCharFormat fmt{tmp.charFormat()};
                fmt.setBackground(*(parent->getUserColor(crdt.getSiteIdAt(pos))));           // Setto il background color al colore associato all'utente che ha scritto tale simbolo selezionato
                tmp.mergeCharFormat(fmt);
            }
        }
    }

    if(mustClearStacks){
        if(!highlightUsers){
            QTextCharFormat fmt{textEdit.currentCharFormat()};
            fmt.setBackground(Qt::BrushStyle::NoBrush);
            textEdit.mergeCurrentCharFormat(fmt);
            emit notifyDeletedStack();
        }
        textEdit.document()->clearUndoRedoStacks();
    }
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


void CRDT_controller::remoteDelete(int pos){

//    std::cout<<"EHI! SONO NELLA REMOTE DELETE! Position: "<< pos <<std::endl;

    bool processingMessage_prev = processingMessage;
    processingMessage = true;

    int pos_prev = textEdit.textCursor().position();
    QTextCursor tmp{textEdit.document()};
    tmp.beginEditBlock();
    tmp.setPosition(pos);

    tmp.deleteChar();

    tmp.endEditBlock();

    tmp.setPosition(pos_prev <= pos ? pos_prev : pos_prev-1);
    textEdit.setTextCursor(tmp);
    if(textEdit.alignment() != Qt::AlignLeft)
        cursorMoved();

    if(highlightUsers)
        textEdit.document()->clearUndoRedoStacks();

    processingMessage = processingMessage_prev;
}

void CRDT_controller::remoteInsert(int pos, QChar c, QTextCharFormat fmt, Qt::Alignment align){

//    std::cout<<"EHI! SONO NELLA REMOTE INSERT! Char: "<< c.toLatin1() <<std::endl;

    bool processingMessage_prev = processingMessage;
    processingMessage = true;

    int pos_prev = textEdit.textCursor().position();
    QTextCursor tmp{textEdit.document()};
    tmp.beginEditBlock();
    tmp.setPosition(pos);

//    std::cout<<"AAAA TextEdit... cursor: "<<textEdit.textCursor().position()<<", pos: "<<pos<<std::endl;        // DEBUG
    QTextBlockFormat blockFmt{tmp.blockFormat()};

    if(highlightUsers){
        fmt.setBackground(*(parent->getUserColor(crdt.getSiteIdAt(pos))));
//        qDebug()<<"highlightUsers: "<<highlightUsers<<", background color: "<<fmt.background().color();        // DEBUG
    }

    tmp.insertText(c, fmt);
    if(tmp.blockFormat().alignment() != align){
        blockFmt.setAlignment(align);
        tmp.mergeBlockFormat(blockFmt);
    }
//    std::cout << "Block End: " << textEdit.textCursor().atBlockEnd() << "; Alignment: " << align << std::endl;

    tmp.endEditBlock();

    tmp.setPosition(pos_prev <= pos ? pos_prev : pos_prev+1);
    textEdit.setTextCursor(tmp);

    if(textEdit.alignment() != Qt::AlignLeft)
        cursorMoved();

    if(highlightUsers)
        textEdit.document()->clearUndoRedoStacks();

    processingMessage = processingMessage_prev;
}

void CRDT_controller::remoteMove(int userId, int pos){
    QTextCursor tmp{textEdit.document()};
    tmp.setPosition(pos);

    QPoint position = QPoint (textEdit.cursorRect(tmp).topLeft().x(), textEdit.cursorRect(tmp).topLeft().y() + textEdit.verticalScrollBar()->value());
    emit updateCursorPosition(userId, position);
}
