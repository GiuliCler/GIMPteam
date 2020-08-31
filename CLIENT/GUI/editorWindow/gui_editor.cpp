#include "gui_editor.h"
#include "../gui_menu.h"
#include "../gui_uri.h"
#include "gui_mytextedit.h"
#include "gui_usersbar.h"
#include "gui_toolsbar.h"
#include "gui_myscrollarea.h"
#include "../../CRDT/crdt_controller.h"
#include <QMessageBox>
#include <QScrollBar>

#include <QPrinter>
#include <QFileDialog>
#include <QFileInfo>

GUI_Editor::GUI_Editor(QWidget *parent, int documentId, QString docName) : QWidget(parent), documentId(documentId), docName(docName)
{
    this->setObjectName(GUI_Editor::getObjectName());
    gimpParent = static_cast<GIMPdocs*>(parent);

    ui = new Ui::GUI_Editor();
    ui->setupUi(this);

    childMyTextEdit = new GUI_MyTextEdit(this);
    ui->textWidget->layout()->addWidget(childMyTextEdit);
    childUsersBar = new GUI_UsersBar(this);
    ui->usersBarWidget->layout()->addWidget(childUsersBar);
    childToolsBar = new GUI_ToolsBar(this);
    ui->toolsBarWidget->layout()->addWidget(childToolsBar);

    fillOnlineUsersList();
    fillContibutorUsersList();

    //richiedo l'uri del documento, perchè se mi chiede l'URI mentre ci lavoro non posso contattare la connection_to_server
    QString uri = GUI_ConnectionToServerWrapper::requestUriWrapper(gimpParent, documentId);
    if(uri.compare("errore") == 0)
        uri = "Error, URI unavailable";
    this->uri = uri;

    //Per gli online users ed i contributors
    connect(gimpParent->getConnection(), &connection_to_server::sigOnlineUser, this, &GUI_Editor::addUserToEditorGUI);
    connect(gimpParent->getConnection(), &connection_to_server::sigOfflineUser, this, &GUI_Editor::removeUserFromEditorGUI);
    connect(gimpParent->getConnection(), &connection_to_server::sigNewContributor, this, &GUI_Editor::addContributorToCurrentDocument);

    QString codedParameters = GUI_ConnectionToServerWrapper::requestOpenDocumentWrapper(gimpParent, gimpParent->userid, documentId);
    if(codedParameters.compare("errore") == 0)
        throw GUI_GenericException("");

    int siteCounter = codedParameters.split("_").at(1).toInt();
    crdtController = new CRDT_controller(gimpParent, this, *childMyTextEdit, gimpParent->userid, siteCounter);

    //devo fare qui queste connect perchè devo aspettare che la crdtController sia creata
    connect(crdtController, &CRDT_controller::updateCursorPosition, childMyTextEdit, &GUI_MyTextEdit::on_updateCursorPosition_emitted);
    connect(crdtController, &CRDT_controller::notifyDeletedStack, childToolsBar, &GUI_ToolsBar::compromisedUndoStack);

    //avvio la connessione speciale per l'editor. D'ora in poi la connection_to_server è off-limits
    if(GUI_ConnectionToServerWrapper::requestStartEditorConnection(gimpParent) < 0)
        //se non riesco a far partire l'editor devo chiudere tutto
        throw GUI_GenericException("");

    gimpParent->isEditorConnected = true;
}

GUI_Editor::~GUI_Editor(){
    delete ui;
    delete crdtController;
}

/*************ACTIONS*********************************/

void GUI_Editor::connectMenuBarActions(){
    connect(this->gimpParent->ui2->closeDocumentAction, &QAction::triggered, this, &GUI_Editor::closeDocument);
    //per la chiusura forzata causata da un document cancellato
    connect(gimpParent->getConnection(), &connection_to_server::forceCloseEditor, this, &GUI_Editor::forcedCloseDocument);
    connect(gimpParent->ui2->getURIAction, &QAction::triggered, [this](){
        GUI_URI *box = new GUI_URI(this, this->uri);
        box->setVisible(true);
    });

    connect(gimpParent->ui2->exportPDFAction, &QAction::triggered, [this](){
        QString fileDoceName = docName;
        if(fileDoceName.compare("") == 0)
            //non dovrebbe mai verificarsi, ma non si sa mai
            fileDoceName = "Default";
        QString fileName = QFileDialog::getSaveFileName(this, "Export PDF", fileDoceName, "*.pdf");
        //se l'utente non seleziona nulla mi ritorna una stringa vuota, quindi non so distinguere se l'utente ha annullato l'operazione o se vuole dargli un nome vuoto. Nel dubbio glielo impedisco.
        //Forse però la getSaveFileName impedisce di salvare un nome vuoto, a meno che non sia il nome di default
        if(fileName.compare("") == 0)
            return;
        if (QFileInfo(fileName).suffix().isEmpty())
            fileName.append(".pdf");

        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPaperSize(QPrinter::A4);
        printer.setOutputFileName(fileName);

        QTextDocument *doc = this->childMyTextEdit->document();
        doc->setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
        doc->print(&printer);
    });

    //ho connesso le 2 action in modo da alternarsi l'un l'altra ed in modo da comportarsi come se avessi premuto un pulsante
    connect(gimpParent->ui2->actionApplyUsersColors, &QAction::triggered, this, &GUI_Editor::on_actionApplyUsersColors);
    connect(gimpParent->ui2->actionApplyUsersColors, &QAction::triggered, findChild<GUI_UsersBar*>(GUI_UsersBar::getObjectName()), &GUI_UsersBar::on_showColorsPushButton_clicked);
    connect(gimpParent->ui2->actionApplyTextColors, &QAction::triggered, this, &GUI_Editor::on_actionApplyTextColors);
    connect(gimpParent->ui2->actionApplyTextColors, &QAction::triggered, findChild<GUI_UsersBar*>(GUI_UsersBar::getObjectName()), &GUI_UsersBar::on_hideColorsPushButton_clicked);



    connect(gimpParent->ui2->actionUndo, &QAction::triggered, this, &GUI_Editor::on_actionUndo);
    connect(gimpParent->ui2->actionRedo, &QAction::triggered, this, &GUI_Editor::on_actionRedo);
    connect(gimpParent->ui2->actionCut, &QAction::triggered, this, &GUI_Editor::on_actionCut);
    connect(gimpParent->ui2->actionCopy, &QAction::triggered, this, &GUI_Editor::on_actionCopy);
    connect(gimpParent->ui2->actionPaste, &QAction::triggered, this, &GUI_Editor::on_actionPaste);
    connect(gimpParent->ui2->actionBold, &QAction::triggered, this, &GUI_Editor::on_actionBold);
    connect(gimpParent->ui2->actionItalic, &QAction::triggered, this, &GUI_Editor::on_actionItalic);
    connect(gimpParent->ui2->actionUnderlined, &QAction::triggered, this, &GUI_Editor::on_actionUnderlined);
    connect(gimpParent->ui2->actionStrikethrough, &QAction::triggered, this, &GUI_Editor::on_actionStrikethrough);
    connect(gimpParent->ui2->actionLeft, &QAction::triggered, this, &GUI_Editor::on_actionLeft);
    connect(gimpParent->ui2->actionCenter, &QAction::triggered, this, &GUI_Editor::on_actionCenter);
    connect(gimpParent->ui2->actionRight, &QAction::triggered, this, &GUI_Editor::on_actionRight);
    connect(gimpParent->ui2->actionJustified, &QAction::triggered, this, &GUI_Editor::on_actionJustified);

}

void GUI_Editor::setUpEditor(){
    //modifico il nome della finestra
    gimpParent->setWindowTitle("GIMPdocs - " + docName);
    childMyTextEdit->setupTextEdit();
}

void GUI_Editor::closeDocument(){
    if(GUI_ConnectionToServerWrapper::requestCloseDocumentWrapper(gimpParent, gimpParent->userid, documentId) == -1)
        return;

    launchSetUi1();
}

void GUI_Editor::forcedCloseDocument(){
    QMessageBox::warning(this, "", "This file has been deleted by its owner.\nIt no longer exists.");

    launchSetUi1();
}

//questo serve ad essere chiamato direttamente quando faccio la chiusura forzata
void GUI_Editor::launchSetUi1(){
    gimpParent->isEditorConnected = false;

    GUI_Menu *widget = new GUI_Menu(this->gimpParent);
    static_cast<GIMPdocs*>(this->gimpParent)->setUi1(widget);
}

void GUI_Editor::on_actionApplyUsersColors(){
    this->gimpParent->ui2->actionApplyTextColors->setEnabled(true);
    this->gimpParent->ui2->actionApplyUsersColors->setEnabled(false);
    findChild<GUI_ToolsBar*>(GUI_ToolsBar::getObjectName())->enterCompromizedModeUndoStack();
}

void GUI_Editor::on_actionApplyTextColors(){
    this->gimpParent->ui2->actionApplyUsersColors->setEnabled(true);
    this->gimpParent->ui2->actionApplyTextColors->setEnabled(false);
    findChild<GUI_ToolsBar*>(GUI_ToolsBar::getObjectName())->exitCompromizedModeUndoStack();
}


void GUI_Editor::on_actionUndo(){
    menuTools_event(UNDO_ON);
}

void GUI_Editor::on_actionRedo(){
    menuTools_event(REDO_ON);
}

void GUI_Editor::on_actionCut(){
    menuTools_event(CUT_ON);
}

void GUI_Editor::on_actionCopy(){
    menuTools_event(COPY_ON);
}

void GUI_Editor::on_actionPaste(){
    menuTools_event(PASTE_ON);
}

void GUI_Editor::on_actionBold(){
    menuTools_event(BOLD_ON);
}

void GUI_Editor::on_actionItalic(){
    menuTools_event(ITALIC_ON);
}

void GUI_Editor::on_actionUnderlined(){
    menuTools_event(UNDERLINED_ON);
}

void GUI_Editor::on_actionStrikethrough(){
    menuTools_event(STRIKETHROUGH_ON);
}

void GUI_Editor::on_actionLeft(){
    menuTools_event(A_LEFT);
    this->childMyTextEdit->setFocus();
}

void GUI_Editor::on_actionCenter(){
    menuTools_event(A_CENTER);
    this->childMyTextEdit->setFocus();
}

void GUI_Editor::on_actionRight(){
    menuTools_event(A_RIGHT);
    this->childMyTextEdit->setFocus();
}

void GUI_Editor::on_actionJustified(){
    menuTools_event(A_JUSTIFIED);
    this->childMyTextEdit->setFocus();
}

void GUI_Editor::setMenuToolStatus(menuTools code){

    if(A_LEFT <= code && code <= A_JUSTIFIED){
        childToolsBar->ui->alignLeftPushButton->setChecked(false);
        gimpParent->ui2->actionLeft->setChecked(false);
        childToolsBar->ui->alignCenterPushButton->setChecked(false);
        gimpParent->ui2->actionCenter->setChecked(false);
        childToolsBar->ui->alignRightPushButton->setChecked(false);
        gimpParent->ui2->actionRight->setChecked(false);
        childToolsBar->ui->alignJustifiedPushButton->setChecked(false);
        gimpParent->ui2->actionJustified->setChecked(false);
    }

    switch(code){
    case UNDO_ON:
        childToolsBar->ui->undoPushButton->setEnabled(true);
        gimpParent->ui2->actionUndo->setEnabled(true);
        break;

    case UNDO_OFF:
        childToolsBar->ui->undoPushButton->setEnabled(false);
        gimpParent->ui2->actionUndo->setEnabled(false);
        break;

    case REDO_ON:
        childToolsBar->ui->redoPushButton->setEnabled(true);
        gimpParent->ui2->actionRedo->setEnabled(true);
        break;

    case REDO_OFF:
        childToolsBar->ui->redoPushButton->setEnabled(false);
        gimpParent->ui2->actionRedo->setEnabled(false);
        break;

    case CUT_ON:
        childToolsBar->ui->cutPushButton->setEnabled(true);
        gimpParent->ui2->actionCut->setEnabled(true);
        break;

    case CUT_OFF:
        childToolsBar->ui->cutPushButton->setEnabled(false);
        gimpParent->ui2->actionCut->setEnabled(false);
        break;

    case COPY_ON:
        childToolsBar->ui->copyPushButton->setEnabled(true);
        gimpParent->ui2->actionCopy->setEnabled(true);
        break;

    case COPY_OFF:
        childToolsBar->ui->copyPushButton->setEnabled(false);
        gimpParent->ui2->actionCopy->setEnabled(false);
        break;

    case PASTE_ON:
        childToolsBar->ui->pastePushButton->setEnabled(true);
        gimpParent->ui2->actionPaste->setEnabled(true);
        break;

    case PASTE_OFF:
        childToolsBar->ui->pastePushButton->setEnabled(false);
        gimpParent->ui2->actionPaste->setEnabled(false);
        break;

    case BOLD_ON:
        childToolsBar->ui->boldPushButton->setChecked(true);
        gimpParent->ui2->actionBold->setChecked(true);
        break;

    case BOLD_OFF:
        childToolsBar->ui->boldPushButton->setChecked(false);
        gimpParent->ui2->actionBold->setChecked(false);
        break;

    case ITALIC_ON:
        childToolsBar->ui->italicPushButton->setChecked(true);
        gimpParent->ui2->actionItalic->setChecked(true);
        break;

    case ITALIC_OFF:
        childToolsBar->ui->italicPushButton->setChecked(false);
        gimpParent->ui2->actionItalic->setChecked(false);
        break;

    case UNDERLINED_ON:
        childToolsBar->ui->underlinedPushButton->setChecked(true);
        gimpParent->ui2->actionUnderlined->setChecked(true);
        break;

    case UNDERLINED_OFF:
        childToolsBar->ui->underlinedPushButton->setChecked(false);
        gimpParent->ui2->actionUnderlined->setChecked(false);
        break;

    case STRIKETHROUGH_ON:
        childToolsBar->ui->strikethroughPushButton->setChecked(true);
        gimpParent->ui2->actionStrikethrough->setChecked(true);
        break;

    case STRIKETHROUGH_OFF:
        childToolsBar->ui->strikethroughPushButton->setChecked(false);
        gimpParent->ui2->actionStrikethrough->setChecked(false);
        break;

    case A_LEFT:
        childToolsBar->ui->alignLeftPushButton->setChecked(true);
        gimpParent->ui2->actionLeft->setChecked(true);
        break;

    case A_CENTER:
        childToolsBar->ui->alignCenterPushButton->setChecked(true);
        gimpParent->ui2->actionCenter->setChecked(true);
        break;

    case A_RIGHT:
        childToolsBar->ui->alignRightPushButton->setChecked(true);
        gimpParent->ui2->actionRight->setChecked(true);
        break;

    case A_JUSTIFIED:
        childToolsBar->ui->alignJustifiedPushButton->setChecked(true);
        gimpParent->ui2->actionJustified->setChecked(true);
        break;
    }
}


void GUI_Editor::addUserToEditorGUI(int userid, QString nickname, QString iconId){
    //ottengo un colore per cursore e icona
    QColor *color = getUserColor(userid);

    //nota: la findChild è ricorsiva e funziona anche coi nipoti
    //questo bruttissimo passaggio di parametri di funzione in funzione anzichè reperirli direttamente a basso livello chiamando il server è perchè mentre il CRDT è aperto non posso usare la connection_to_server
    findChild<GUI_UsersBar*>(GUI_UsersBar::getObjectName())->addOnlineUserIcon(userid, *color, nickname, iconId);
    GUI_MyTextEdit *son = findChild<GUI_MyTextEdit*>(GUI_MyTextEdit::getObjectName());

    if(userid != gimpParent->userid){
        QPoint p = QPoint (son->cursorRect().topLeft().x(), son->cursorRect().topLeft().y() + son->verticalScrollBar()->value());
        findChild<GUI_MyTextEdit*>(GUI_MyTextEdit::getObjectName())->addUserCursor(userid, p, *color);
    }
}

void GUI_Editor::removeUserFromEditorGUI(int userid){
    findChild<GUI_MyTextEdit*>(GUI_MyTextEdit::getObjectName())->removeUserCursor(userid);
    findChild<GUI_UsersBar*>(GUI_UsersBar::getObjectName())->removeOnlineUserIcon(userid);
    //se l'utente non è un contributor e non è più online gli tolgo il colore associato per poterlo assegnare a qualcun altro
    /*if(!findChild<GUI_UsersBar*>(GUI_UsersBar::getObjectName())->isContributor(userid))
        forgetUserColor(userid);*/
}

void GUI_Editor::addContributorToCurrentDocument(int userid, QString nickname, QString iconId){
    QColor *color = getUserColor(userid);
    findChild<GUI_UsersBar*>(GUI_UsersBar::getObjectName())->addContributorUserIcon(userid, *color, nickname, iconId);
}


QColor *GUI_Editor::getUserColor(int userId){
    QColor *color;
    //controllo che l'user non abbia già un colore assegnato, o perchè si è disconnesso e riconnesso o perchè è già presente fra i contributors
    if(userColorMap.find(userId) == userColorMap.end() ){
        color = colorsManager.newColor();
        userColorMap.insert(userId, color);
    }
    else
        color = userColorMap[userId];

    return color;
}

/*void GUI_Editor::forgetUserColor(int userId){
    if(userColorMap.find(userId) == userColorMap.end())
        return;

    userColorMap.remove(userId);
}*/

void GUI_Editor::fillOnlineUsersList(){
    //ottengo l'elenco degli utenti che al momento stanno guardando il mio stesso document e ne creo icona e cursore
    std::shared_ptr<QSet<int>> users = GUI_ConnectionToServerWrapper::getWorkingUsersOnDocumentWrapper(gimpParent, documentId);
    if(users == nullptr)
        return;

    for (QSet<int>::iterator userId = users->begin(); userId != users->end(); userId++){
        //questo bruttissimo passaggio di parametri di funzione in funzione anzichè reperirli direttamente a basso livello chiamando il server è perchè mentre il CRDT è aperto non posso usare la connection_to_server

        QString nickname = GUI_ConnectionToServerWrapper::requestGetNicknameWrapper(gimpParent, *userId);
        QString iconId = GUI_ConnectionToServerWrapper::requestGetIconIdWrapper(gimpParent, *userId);
        if(nickname.compare("errore") != 0 && iconId.compare("errore") != 0)
            addUserToEditorGUI(*userId, nickname, iconId);
    }
}

void GUI_Editor::fillContibutorUsersList(){
    //creo l'icona per gli user che hanno contribuito al document
    std::shared_ptr<QSet<int>> contributors = GUI_ConnectionToServerWrapper::getContributorsUsersOnDocumentWrapper(gimpParent, documentId);
    if(contributors == nullptr || contributors->size()==0)
        return;

    for (QSet<int>::iterator userId = contributors->begin(); userId != contributors->end(); userId++){
        //questo bruttissimo passaggio di parametri di funzione in funzione anzichè reperirli direttamente a basso livello chiamando il server è perchè mentre il CRDT è aperto non posso usare la connection_to_server

        QString nickname = GUI_ConnectionToServerWrapper::requestGetNicknameWrapper(gimpParent, *userId);
        QString iconId = GUI_ConnectionToServerWrapper::requestGetIconIdWrapper(gimpParent, *userId);
        if(nickname.compare("errore") != 0 && iconId.compare("errore") != 0)
            addContributorToCurrentDocument(*userId, nickname, iconId);
    }
}
