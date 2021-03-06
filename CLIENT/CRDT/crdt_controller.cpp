#include "crdt_controller.h"
#include "crdt_message.h"
#include "GUI/editorWindow/gui_usersbar.h"
#include "GUI/connection/gui_reconnection.h"
#include <QClipboard>
#include <QMimeData>
#include <iostream>
#include <QScrollBar>

#include <ctime>


CRDT_controller::CRDT_controller(GIMPdocs *gimpdocs, GUI_Editor *parent, GUI_MyTextEdit& textEdit, int siteId, int siteCounter):
                        QObject(parent), gimpDocs(gimpdocs),  editorParent(parent),  connection(gimpDocs->getConnection()), textEdit(textEdit), highlightUsers(false),
                        crdt{this, gimpDocs->getConnection(), siteId, siteCounter},
                        rememberFormatChange(false), validateSpin(true), validateFontCombo(true), deletedAmountOnPaste(-1),
                        cursorMovable_sem(0){
    //QObject::connect(this->editorParent, &GUI_Editor::menuTools_event, this, &CRDT_controller::menuCall);
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
    //QObject::connect(parent->childUsersBar, &GUI_UsersBar::highlightingUsers, this, &CRDT_controller::setUsersColors);
    QObject::connect(connection, &connection_to_server::sigMoveCursor, this, &CRDT_controller::remoteMove, Qt::ConnectionType::QueuedConnection);
    QObject::connect(connection, &connection_to_server::sigStopCursor, this, &CRDT_controller::remoteStopCursor, Qt::ConnectionType::QueuedConnection);
    QObject::connect(connection, &connection_to_server::sigStartCursor, this, &CRDT_controller::remoteStartCursor, Qt::ConnectionType::QueuedConnection);
    QObject::connect(connection, &connection_to_server::sigChangeAlign, this, &CRDT_controller::remoteChangeAlign, Qt::ConnectionType::QueuedConnection);

    parent->childToolsBar->ui->spinBox->setSpecialValueText("Default");
}

CRDT_controller::~CRDT_controller(){
//    qDebug() << "Distruttore CRDT_controller chiamato";        // DEBUG
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
        // selecting from right to left => should consider the format of the letter on the right of the cursor
        QTextCursor tmp(textEdit.textCursor());
        tmp.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
        textEdit.setFontWeight(tmp.charFormat().fontWeight() >= QFont::Bold ? QFont::Normal : QFont::Bold);
        rememberFormatChange = true;
    }
    else
        // no selection or selecting from left to right => should consider the format of the letter on the left of the cursor
        textEdit.setFontWeight(textEdit.fontWeight() >= QFont::Bold ? QFont::Normal : QFont::Bold);
    textEdit.setFocus();
}

void CRDT_controller::setItalic(){
    if(textEdit.textCursor().hasSelection() && textEdit.textCursor().position() < textEdit.textCursor().anchor()){
        // selecting from right to left => should consider the format of the letter on the right of the cursor
        QTextCursor tmp(textEdit.textCursor());
        tmp.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
        textEdit.setFontItalic(!tmp.charFormat().fontItalic());
        rememberFormatChange = true;
    }
    else
        // no selection or selecting from left to right => should consider the format of the letter on the left of the cursor
        textEdit.setFontItalic(!textEdit.fontItalic());
    textEdit.setFocus();
}

void CRDT_controller::setStrikethrough(){
    QTextCharFormat fmt;
    if(textEdit.textCursor().hasSelection() && textEdit.textCursor().position() < textEdit.textCursor().anchor()){
        // selecting from right to left => should consider the format of the letter on the right of the cursor
        QTextCursor tmp(textEdit.textCursor());
        tmp.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
        fmt.setFontStrikeOut(!tmp.charFormat().fontStrikeOut());
        rememberFormatChange = true;
    }
    else
        // no selection or selecting from left to right => should consider the format of the letter on the left of the cursor
        fmt.setFontStrikeOut(!textEdit.currentCharFormat().fontStrikeOut());
    textEdit.mergeCurrentCharFormat(fmt);
    textEdit.setFocus();
}

void CRDT_controller::setUnderlined(){
    if(textEdit.textCursor().hasSelection() && textEdit.textCursor().position() < textEdit.textCursor().anchor()){
        // selecting from right to left => should consider the format of the letter on the right of the cursor
        QTextCursor tmp(textEdit.textCursor());
        tmp.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
        textEdit.setFontUnderline(!tmp.charFormat().fontUnderline());
        rememberFormatChange = true;
    }
    else
        // no selection or selecting from left to right => should consider the format of the letter on the left of the cursor
        textEdit.setFontUnderline(!textEdit.fontUnderline());
    textEdit.setFocus();
}

void CRDT_controller::setSize(int size){
    // validate spin:
    //      = true => wanna change for real the size
    //      = false => the function has been called only because of a change of selection, cannot change the size
    if(validateSpin){
        if(size > 0)
            textEdit.setFontPointSize(size);
        else
            // size can't be <= 0. Set it to a default value
            editorParent->childToolsBar->ui->spinBox->setValue(defaultFontPointSize);
    }else
        validateSpin = true;
    cursorMoved();
    textEdit.setFocus();
}

void CRDT_controller::setFont(const QFont &f){
    // validate font combo:
    //      = true => wanna change for real the font
    //      = false => the function has been called only because of a change of selection, cannot change the font
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
    deletedAmountOnPaste = textEdit.textCursor().selectedText().length();
    if(textEdit.document()->isEmpty())
        alignBeforePaste = textEdit.alignment();
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

    bool processingMessage_prev = processingMessage;
    processingMessage = true;

    QTextCursor tmp{textEdit.document()};
    tmp.setPosition(0);

    if(highlightUsers){

        int inizio = -1, fine = -1, id_corrente = -1;

        for(int pos = 0; pos < crdt.getLength(); tmp.setPosition(++pos)){
            if(crdt.getSiteIdAt(pos) != id_corrente){
                if(inizio == -1){
                    inizio = pos;
                    id_corrente = crdt.getSiteIdAt(pos);
                } else {
                    fine = pos - 1;
                    int selezionate = fine - inizio;

                    tmp.setPosition(inizio);
                    tmp.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, selezionate + 1);
                    QTextCharFormat fmt;
                    fmt.setBackground(editorParent->getUserColor(id_corrente));
                    tmp.mergeCharFormat(fmt);

                    inizio = pos;
                    fine = -1;
                    tmp.setPosition(pos);
                    id_corrente = crdt.getSiteIdAt(pos);
                }
            }
        }
        if(inizio != -1){
            fine = crdt.getLength();
            int selezionate = fine - inizio;

            tmp.setPosition(inizio);
            tmp.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, selezionate);
            QTextCharFormat fmt;
            fmt.setBackground(editorParent->getUserColor(id_corrente));
            tmp.mergeCharFormat(fmt);
        }
    } else {
        tmp.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, crdt.getLength());
        QTextCharFormat fmt;
        fmt.setBackground(Qt::BrushStyle::NoBrush);
        tmp.mergeCharFormat(fmt);
    }

    if(highlightUsers && textEdit.textBackgroundColor() == Qt::BrushStyle::NoBrush)
        textEdit.setTextBackgroundColor(editorParent->getUserColor(crdt.getSiteId()));

    if(!highlightUsers && textEdit.textBackgroundColor() != Qt::BrushStyle::NoBrush)
        textEdit.setTextBackgroundColor(Qt::BrushStyle::NoBrush);

    // Cancello UNDO e REDO stacks
    textEdit.document()->clearUndoRedoStacks();

    processingMessage = processingMessage_prev;
}


void CRDT_controller::currentCharFormatChanged(const QTextCharFormat &format){
    if(textEdit.textCursor().hasSelection() && textEdit.textCursor().position() < textEdit.textCursor().anchor()){
        // selecting from right to left => should consider the format of the letter on the right of the cursor
        QTextCursor tmp(textEdit.textCursor());
        tmp.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);

        // check if the text is bold, strikethrough, underlined and/or italic and update the toolbar
        emit menuSet(tmp.charFormat().fontItalic() ? menuTools::ITALIC_ON : menuTools::ITALIC_OFF);
        emit menuSet(tmp.charFormat().fontStrikeOut() ? menuTools::STRIKETHROUGH_ON : menuTools::STRIKETHROUGH_OFF);
        emit menuSet(tmp.charFormat().fontUnderline() ? menuTools::UNDERLINED_ON : menuTools::UNDERLINED_OFF);
        emit menuSet(tmp.charFormat().fontWeight() >= QFont::Bold ? menuTools::BOLD_ON : menuTools::BOLD_OFF);

        // check the color of the text update the toolbar
        editorParent->childToolsBar->setTextColorIconColor(tmp.charFormat().foreground().color());

        // check the font point size and update the toolbar
        if(static_cast<int>(tmp.charFormat().fontPointSize()) != editorParent->childToolsBar->ui->spinBox->value()){
            validateSpin = false;
            editorParent->childToolsBar->ui->spinBox->setValue(static_cast<int>(tmp.charFormat().fontPointSize()));
            if(editorParent->childToolsBar->ui->spinBox->value() == editorParent->childToolsBar->ui->spinBox->minimum()){
                validateSpin = false;
                editorParent->childToolsBar->ui->spinBox->setValue(defaultFontPointSize);
            }
        }

        // check the font of the text and update the toolbar
        if(tmp.charFormat().font() != editorParent->childToolsBar->ui->fontComboBox->currentFont()){
            validateFontCombo = false;
            editorParent->childToolsBar->ui->fontComboBox->setCurrentFont(tmp.charFormat().font());
        }
        rememberFormatChange = true;

    }else{

        // no selection or selecting from left to right => should consider the format of the letter on the left of the cursor
        // same steps as before (bold/italic/..., color, size, font)
        emit menuSet(format.fontItalic() ? menuTools::ITALIC_ON : menuTools::ITALIC_OFF);
        emit menuSet(format.fontStrikeOut() ? menuTools::STRIKETHROUGH_ON : menuTools::STRIKETHROUGH_OFF);
        emit menuSet(format.fontUnderline() ? menuTools::UNDERLINED_ON : menuTools::UNDERLINED_OFF);
        emit menuSet(format.fontWeight() >= QFont::Bold ? menuTools::BOLD_ON : menuTools::BOLD_OFF);

        editorParent->childToolsBar->setTextColorIconColor(format.foreground().color());

        if(static_cast<int>(textEdit.fontPointSize()) != editorParent->childToolsBar->ui->spinBox->value()){
            if(textEdit.textCursor().hasSelection())
                validateSpin = false;
            editorParent->childToolsBar->ui->spinBox->setValue(static_cast<int>(textEdit.fontPointSize()));
            if(editorParent->childToolsBar->ui->spinBox->value() == editorParent->childToolsBar->ui->spinBox->minimum()){
                if(textEdit.textCursor().hasSelection())
                    validateSpin = false;
                editorParent->childToolsBar->ui->spinBox->setValue(defaultFontPointSize);
            }
        }

        if(textEdit.currentFont() != editorParent->childToolsBar->ui->fontComboBox->currentFont()) {
            if(textEdit.textCursor().hasSelection())
                validateFontCombo = false;
            editorParent->childToolsBar->ui->fontComboBox->setCurrentFont(textEdit.currentFont());
        }
    }
}


void CRDT_controller::cursorMoved(){

    if(cursorMovable_sem > 0)
        return;

    // update the alignment button on the toolbar
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

    // if it's needed to recheck the current format (e.g.backward selection)
    if(rememberFormatChange){
        rememberFormatChange = false;
        currentCharFormatChanged(textEdit.currentCharFormat());
    }

    // notify the server that the user moved the cursor
    try {
        connection->requestSendMovedCursor(crdt.getSiteId(), textEdit.textCursor().position());
    } catch (GUI_ConnectionException &exception){
        GUI_Reconnection::GUI_ReconnectionWrapper(gimpDocs);
        gimpDocs->returnToLogin();
    }
}

void CRDT_controller::selectionChanged(){
    // ignore this function if performing remote operations
    if(processingMessage)
        return;

    // if it's needed to recheck the current format (e.g.backward selection)
    if(rememberFormatChange){
        rememberFormatChange = false;
        currentCharFormatChanged(textEdit.currentCharFormat());
    }

    if(textEdit.textCursor().hasSelection()){
        editorParent->setMenuToolStatus(CUT_ON);
        editorParent->setMenuToolStatus(COPY_ON);
    } else {
        editorParent->setMenuToolStatus(CUT_OFF);
        editorParent->setMenuToolStatus(COPY_OFF);
    }
}


void CRDT_controller::contentChanged(int pos, int del, int add){

    // ignore this function if performing remote operations
    if(processingMessage)
        return;

    cursorMovable_sem++;
    if(cursorMovable_sem == 1)
        QObject::disconnect(&this->textEdit, &QTextEdit::cursorPositionChanged, this, &CRDT_controller::cursorMoved);
    try {
        connection->requestSendStopCursor();
    } catch (GUI_ConnectionException &exception){
        GUI_Reconnection::GUI_ReconnectionWrapper(gimpDocs);
        gimpDocs->returnToLogin();
    }


    QTextCursor tmp{textEdit.document()};
    bool mustClearStacks = false;

    //std::cout << "Before adj - pos: " << pos << "; add: " << add << "; del: " << del <<"; deletedAmountOnPaste: " << deletedAmountOnPaste << std::endl;     // DEBUG

    if(deletedAmountOnPaste != -1){
        if(pos == 0){
            add = add - del + deletedAmountOnPaste;
            del = deletedAmountOnPaste;
            mustClearStacks = true;
            if(add == textEdit.document()->characterCount() -1){
                QTextBlockFormat fmt;
                fmt.setAlignment(alignBeforePaste);

                tmp.select(QTextCursor::Document);
                tmp.mergeBlockFormat(fmt);
            }
        }
        deletedAmountOnPaste = -1;
    }

    tmp.setPosition(pos);

    if(pos + del -1 > crdt.getLength() - 1){
        del--;
        add--;
        if(add == 0 && del == 0 && pos == 0){
            try {
                connection->requestChangeAlign(textEdit.alignment());
            } catch (GUI_ConnectionException &exception){
                GUI_Reconnection::GUI_ReconnectionWrapper(gimpDocs);
                gimpDocs->returnToLogin();
            }
        }
    }

    //std::cout << "After adj - pos: " << pos << "; add: " << add << "; del: " << del << std::endl;     // DEBUG

    // remove the deleted letters from the crdt
    if(del > 0)
        crdt.localMultipleErase(pos, del);

    // insert the added letters in the crdt
    if(add > 0){

        // make sure that the background is NoBrush/white before the insertion
        bool colored = false;
        for(int i = pos; i < pos + add; tmp.setPosition(++i)){
            if(tmp.charFormat().background() != Qt::BrushStyle::NoBrush && tmp.charFormat().background() != Qt::white){
                colored = true;
                break;
            }
        }

        if(colored){
            tmp.setPosition(pos);
            tmp.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, add);
            QTextCharFormat fmt;
            fmt.setBackground(Qt::BrushStyle::NoBrush);
            tmp.mergeCharFormat(fmt);
            mustClearStacks = true;
        }

        tmp.setPosition(pos+1);

        int inizio = -1, fine = -1;
        for(int i = pos+1; i < pos + add; ++i){
            tmp.setPosition(i);
            QTextCharFormat fmt{tmp.charFormat()};
            if(fmt.fontPointSize() <= 0){
                if(inizio == -1){
                    inizio = i - 1;
                }
            } else {
                if(inizio != -1){
                    fine = i - 1;
                    int selezionate = fine - inizio;

                    tmp.setPosition(inizio);
                    tmp.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, selezionate + 1);
                    QTextCharFormat fmt;
                    fmt.setFontPointSize(defaultFontPointSize);
                    tmp.mergeCharFormat(fmt);

                    inizio = -1;
                    fine = -1;
                    tmp.setPosition(i);
                }
            }
        }
        if(inizio != -1){
            fine = pos + add - 1;
            int selezionate = fine - inizio;

            tmp.setPosition(inizio);
            tmp.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, selezionate + 1);
            QTextCharFormat fmt;
            fmt.setFontPointSize(defaultFontPointSize);
            tmp.mergeCharFormat(fmt);
        }

        tmp.setPosition(pos+1);

        // Trovo dove inserire la prima lettera
        QVector<int> firstPosition = crdt.generaPrimaPosizione(pos);

        QString document = textEdit.toPlainText();

        if(document.at(pos) == '\n'){
            tmp.movePosition(QTextCursor::PreviousCharacter);
            QTextCharFormat fmt{tmp.charFormat()};
            crdt.localFirstInsert(pos, document.at(pos), fmt, tmp.blockFormat().alignment(), firstPosition, add);
            tmp.movePosition(QTextCursor::NextCharacter);
        } else {
            QTextCharFormat fmt{tmp.charFormat()};
            crdt.localFirstInsert(pos, document.at(pos), fmt, tmp.blockFormat().alignment(), firstPosition, add);
        }

        // Aggiungo al fondo del vettore di interi il siteId
        firstPosition.push_back(crdt.getSiteId());
        firstPosition.push_back(crdt.getSiteId());

        // Insert in crdt, making sure that the font size is > 0 (or use the default one)
        for(int i = pos+1; i < pos + add; ++i){
            tmp.movePosition(QTextCursor::NextCharacter);
            firstPosition[firstPosition.size()-2]++;

            if(document.at(i) == '\n'){
                tmp.movePosition(QTextCursor::PreviousCharacter);
                QTextCharFormat fmt{tmp.charFormat()};
                crdt.localInsert(i, document.at(i), fmt, tmp.blockFormat().alignment(), firstPosition);
                tmp.movePosition(QTextCursor::NextCharacter);
            } else {
                QTextCharFormat fmt{tmp.charFormat()};
                crdt.localInsert(i, document.at(i), fmt, tmp.blockFormat().alignment(), firstPosition);
            }
        }
    }

    int cnt = 0;

    // if i'm changing the alignment of the paragraph next to the cursor (deleting an enter)
    if(!tmp.atEnd() &&  tmp.blockFormat().alignment() != crdt.getAlignAt(tmp.position())){

        int pos1 = tmp.position();
        //cancello dal fondo del blocco a tmp
        tmp.movePosition(QTextCursor::EndOfBlock);

        // remove these letters (w/ the old alignment) from the crdt
        cnt = tmp.position() - pos1 + 1;
        crdt.localMultipleErase(pos1, cnt);

        // re-insert the letters making sure that the format is correct
        tmp.setPosition(pos1);
        bool colored = false;
        for(int i = pos1; i < pos1 + cnt; tmp.setPosition(++i)){
            if(tmp.charFormat().background() != Qt::BrushStyle::NoBrush && tmp.charFormat().background() != Qt::white){
                colored = true;
                break;
            }
        }
        if(colored){
            tmp.setPosition(pos1);
            tmp.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, cnt);
            QTextCharFormat fmt;
            fmt.setBackground(Qt::BrushStyle::NoBrush);
            tmp.mergeCharFormat(fmt);
            mustClearStacks = true;
        }

        tmp.setPosition(pos1+1);

        int inizio = -1, fine = -1;
        for(int i = pos1+1; i < pos1 + cnt; ++i){
            tmp.setPosition(i);
            QTextCharFormat fmt{tmp.charFormat()};
            if(fmt.fontPointSize() <= 0){
                if(inizio == -1){
                    inizio = i - 1;
                }
            } else {
                if(inizio != -1){
                    fine = i - 1;
                    int selezionate = fine - inizio;

                    tmp.setPosition(inizio);
                    tmp.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, selezionate + 1);
                    QTextCharFormat fmt;
                    fmt.setFontPointSize(defaultFontPointSize);
                    tmp.mergeCharFormat(fmt);

                    inizio = -1;
                    fine = -1;
                    tmp.setPosition(i);
                }
            }
        }
        if(inizio != -1){
            fine = pos1 + cnt - 1;
            int selezionate = fine - inizio;

            tmp.setPosition(inizio);
            tmp.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, selezionate + 1);
            QTextCharFormat fmt;
            fmt.setFontPointSize(defaultFontPointSize);
            tmp.mergeCharFormat(fmt);
        }

        tmp.setPosition(pos1+1);

        // Trovo dove inserire la prima lettera
        QVector<int> firstPosition = crdt.generaPrimaPosizione(pos1);

        QString document = textEdit.toPlainText();

        if(document.at(pos1) == '\n'){
            tmp.movePosition(QTextCursor::PreviousCharacter);
            QTextCharFormat fmt{tmp.charFormat()};
            crdt.localFirstInsert(pos1, document.at(pos1), fmt, tmp.blockFormat().alignment(), firstPosition, cnt);
            tmp.movePosition(QTextCursor::NextCharacter);
        } else {
            QTextCharFormat fmt{tmp.charFormat()};
            crdt.localFirstInsert(pos1, document.at(pos1), fmt, tmp.blockFormat().alignment(), firstPosition, cnt);
        }

        // Aggiungo al fondo del vettore di interi il siteId
        firstPosition.push_back(crdt.getSiteId());
        firstPosition.push_back(crdt.getSiteId());

        // insert in crdt, making sure that the font size is > 0 (or use the default one)
        for(int i = pos1+1; i < pos1 + cnt; ++i){
            tmp.movePosition(QTextCursor::NextCharacter);

            firstPosition[firstPosition.size()-2]++;
            
            if(document.at(i) == '\n'){
                tmp.movePosition(QTextCursor::PreviousCharacter);
                QTextCharFormat fmt{tmp.charFormat()};
                crdt.localInsert(i, document.at(i), fmt, tmp.blockFormat().alignment(), firstPosition);
                tmp.movePosition(QTextCursor::NextCharacter);
            } else {
                QTextCharFormat fmt{tmp.charFormat()};
                crdt.localInsert(i, document.at(i), fmt, tmp.blockFormat().alignment(), firstPosition);
            }
        }
    }

    // if "users colors" is selected, visualize the background according to who modified what (otherwise it should be white / NoBrush)
    if(highlightUsers){
        mustClearStacks = true;
        tmp.setPosition(pos);

        if(add+cnt > 0){
            tmp.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, add + cnt);
            QTextCharFormat format;
            format.setBackground(editorParent->getUserColor(crdt.getSiteIdAt(pos)));
            tmp.mergeCharFormat(format);
        }
    }

    // if the text was changed in the function, clear the undo stack
    if(mustClearStacks){
        if(!highlightUsers){
            QTextCharFormat fmt{textEdit.currentCharFormat()};
            fmt.setBackground(Qt::BrushStyle::NoBrush);
            textEdit.mergeCurrentCharFormat(fmt);
            emit notifyDeletedStack();
        }
        textEdit.document()->clearUndoRedoStacks();
    }

    if(cursorMovable_sem == 1){
        QObject::connect(&this->textEdit, &QTextEdit::cursorPositionChanged, this, &CRDT_controller::cursorMoved);
    }
    cursorMovable_sem--;
    try {
        connection->requestSendStartCursor();
    } catch (GUI_ConnectionException &exception){
        GUI_Reconnection::GUI_ReconnectionWrapper(gimpDocs);
        gimpDocs->returnToLogin();
    }

    if(highlightUsers && cursorMovable_sem == 0)
        cursorMoved();
}

// if the clipboard has some text, enable the paste
void CRDT_controller::clipboardDataChanged(){
    if (const QMimeData *md = QApplication::clipboard()->mimeData())
        editorParent->setMenuToolStatus(md->hasText() ? PASTE_ON : PASTE_OFF);
}

// enable / disable the undo button
void CRDT_controller::undoAvailableChanged(bool available){
    editorParent->setMenuToolStatus(available ? UNDO_ON : UNDO_OFF);
}

// enable / disable the redo button
void CRDT_controller::redoAvailableChanged(bool available){
    editorParent->setMenuToolStatus(available ? REDO_ON : REDO_OFF);
}


void CRDT_controller::menuCall(menuTools op){
    // receive a new operation and check what type of operation should be performed
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


// show the delection of the letter by another user
void CRDT_controller::remoteDelete(int start, int cnt){

//    std::cout<<"EHI! SONO NELLA REMOTE DELETE! Position: "<< pos <<std::endl;         // DEBUG

    bool processingMessage_prev = processingMessage;
    processingMessage = true;

    QTextCursor tmp{textEdit.document()};
    tmp.beginEditBlock();
    tmp.setPosition(start);
    tmp.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, cnt);
    tmp.removeSelectedText();

    tmp.endEditBlock();

    if(highlightUsers)
        textEdit.document()->clearUndoRedoStacks();

    processingMessage = processingMessage_prev;
}

// show the insertion of a new letter by another user
void CRDT_controller::remoteInsert(int pos, QString s, QTextCharFormat fmt, Qt::Alignment align){

//    std::cout<<"EHI! SONO NELLA REMOTE INSERT! Char: "<< c.toLatin1() <<std::endl;        // DEBUG

    bool processingMessage_prev = processingMessage;
    processingMessage = true;

    QTextCursor tmp{textEdit.document()};

    // edit block => insert and chang a format together in the same undo operation
    tmp.beginEditBlock();
    tmp.setPosition(pos);

    if(fmt.fontPointSize() <= 0)
        fmt.setFontPointSize(defaultFontPointSize);

    QTextBlockFormat blockFmt;

    if(highlightUsers){
        fmt.setBackground(editorParent->getUserColor(crdt.getSiteIdAt(pos)));
    }

    tmp.insertText(s, fmt);

    if(s.back() == '\n')
        tmp.movePosition(QTextCursor::PreviousCharacter);

    if(tmp.blockFormat().alignment() != align){
        tmp.setPosition(pos);
        tmp.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor,
                         s.back() == '\n' ? s.length()-1 : s.length());

        blockFmt.setAlignment(align);
        tmp.mergeBlockFormat(blockFmt);
    }

    tmp.endEditBlock();

    if(highlightUsers)
        textEdit.document()->clearUndoRedoStacks();

    processingMessage = processingMessage_prev;
}

// update a colored cursor of another user
void CRDT_controller::remoteMove(int userId, int pos){

    QTextCursor tmp{textEdit.document()};

    if(pos >= textEdit.document()->characterCount())
        pos = textEdit.document()->characterCount() - 1;

    tmp.setPosition(pos);

    // Aggiorno vettore dei cursori degli utenti online
    usersCursors[userId] = pos;

    QPoint position = QPoint (textEdit.cursorRect(tmp).topLeft().x(), textEdit.cursorRect(tmp).topLeft().y() + textEdit.verticalScrollBar()->value());
    emit updateCursorPosition(userId, position);
}


// receive the request to stop moving the cursor
void CRDT_controller::remoteStopCursor(){
    cursorMovable_sem++;
    if(cursorMovable_sem == 1)
        QObject::disconnect(&this->textEdit, &QTextEdit::cursorPositionChanged, this, &CRDT_controller::cursorMoved);
}

// receive the request to restart moving the cursor
void CRDT_controller::remoteStartCursor(int userId){
    crdt.processBuffer(userId);
    if(cursorMovable_sem == 1)
        QObject::connect(&this->textEdit, &QTextEdit::cursorPositionChanged, this, &CRDT_controller::cursorMoved);
    cursorMovable_sem--;

    cursorMoved();
}

// receive the request to change the alignment
void CRDT_controller::remoteChangeAlign(Qt::Alignment al){

    bool processingMessage_prev = processingMessage;
    processingMessage = true;

    if(crdt.getLength() == 0){
        if(al == Qt::AlignLeft)
            this->setLeft();
        else if(al == Qt::AlignRight)
            this->setRight();
        else if(al == Qt::AlignCenter)
            this->setCenter();
        else
            this->setJustified();
    }

    processingMessage = processingMessage_prev;
}

GIMPdocs* CRDT_controller::getGimpDocs(){
    return gimpDocs;
}
