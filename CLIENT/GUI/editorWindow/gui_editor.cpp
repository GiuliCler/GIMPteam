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


GUI_Editor::GUI_Editor(QWidget *parent, long documentId) : QWidget(parent), documentId(documentId)
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
    crdtController = new CRDT_controller(this, *childMyTextEdit);

    //ottengo l'elenco degli utenti che al momento stanno guardando il mio stesso document e ne creo icona e cursore
    std::shared_ptr<QSet<long>> users = Stub::getWorkingUsersOnDocument(documentId);
    for (QSet<long>::iterator userId = users->begin(); userId != users->end(); userId++)
        addUserToEditorGUI(*userId);

    //creo l'icona per gli user che hanno contribuito al document
    std::shared_ptr<QSet<long>> contributors = Stub::getContributorsUsersOnDocument(documentId);
    for (QSet<long>::iterator userId = contributors->begin(); userId != contributors->end(); userId++)
        addContributorToCurrentDocument(*userId);

    //childMyTextEdit->setupTextEdit();
}

GUI_Editor::~GUI_Editor(){
    delete ui;
}

/*************ACTIONS*********************************/

void GUI_Editor::connectMenuBarActions(){
    connect(this->gimpParent->ui2->closeDocumentAction, &QAction::triggered, this, &GUI_Editor::launchSetUi1);
    connect(gimpParent->ui2->getURIAction, &QAction::triggered, [this](){
        GUI_URI *box = new GUI_URI(this, Stub::getDocumentURI(documentId));
        box->setVisible(true);
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

//sto faceno una funzione wrapper giusto per renderlo più ordinato
void GUI_Editor::setupTextEdit(){
    //non posso metterlo nel costruttore perchè forse le actions non sono ancora pronte per essere modificate a checke, come verrei fare coll'action dell'align
    childMyTextEdit->setupTextEdit();
}

void GUI_Editor::launchSetUi1(){
    Stub::closeDocument(this->gimpParent->userid, documentId);

    GUI_Menu *widget = new GUI_Menu(this->gimpParent);
    static_cast<GIMPdocs*>(this->gimpParent)->setUi1(widget);
}

void GUI_Editor::on_actionApplyUsersColors(){
    this->gimpParent->ui2->actionApplyTextColors->setEnabled(true);
    this->gimpParent->ui2->actionApplyUsersColors->setEnabled(false);
}

void GUI_Editor::on_actionApplyTextColors(){
    this->gimpParent->ui2->actionApplyUsersColors->setEnabled(true);
    this->gimpParent->ui2->actionApplyTextColors->setEnabled(false);
}


void GUI_Editor::on_actionUndo(){
    menuTools_event(UNDO);
}

void GUI_Editor::on_actionRedo(){
    menuTools_event(REDO);
}

void GUI_Editor::on_actionCut(){
    menuTools_event(CUT);
}

void GUI_Editor::on_actionCopy(){
    menuTools_event(COPY);
}

void GUI_Editor::on_actionPaste(){
    menuTools_event(PASTE);
}

void GUI_Editor::on_actionBold(){
    menuTools_event(BOLD_ON);
}

void GUI_Editor::on_actionItalic(){
    menuTools_event(ITALIC_ON);
}

void GUI_Editor::on_actionUnderlined(){

    menuTools_event(UNDERLINED_ON);

    //questo serve a counterare il fatto che in caso di click il button cambia automaticamente stato da chechek ad unchechek e viceversa, ma voglio essere io a decidere quando cambiare stato
    //childToolsBar->ui->underlinedPushButton->setChecked(!childToolsBar->ui->boldPushButton->isChecked());

    //non so se devo cambiare lo stato di checked o no, quindi lo chiedo al text editor
    //childToolsBar->ui->underlinedPushButton->setChecked(Stub::isGenericFontAttributeActivated(childToolsBar->ui->boldPushButton->isChecked()));
    //setMenuToolStatus(UNDERLINED_ON);
}

void GUI_Editor::on_actionStrikethrough(){

    menuTools_event(STRIKETHROUGH_ON);

    //questo serve a counterare il fatto che in caso di click il button cambia automaticamente stato da chechek ad unchechek e viceversa, ma voglio essere io a decidere quando cambiare stato
    //childToolsBar->ui->strikethroughPushButton->setChecked(!childToolsBar->ui->boldPushButton->isChecked());

    //non so se devo cambiare lo stato di checked o no, quindi lo chiedo al text editor
    //childToolsBar->ui->strikethroughPushButton->setChecked(Stub::isGenericFontAttributeActivated(childToolsBar->ui->boldPushButton->isChecked()));
    //setMenuToolStatus(UNDERLINED_OFF);
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
    case UNDO:
        //do nothing, ma almeno rimuovo il warning
        break;

    case REDO:
        //do nothing
        break;

    case CUT:
        //do nothing
        break;

    case COPY:
        //do nothing
        break;

    case PASTE:
        //do nothing
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


void GUI_Editor::addUserToEditorGUI(long userid){
    //ottengo un colore per cursore e icona
    QColor *color = getUserColor(userid);

    //nota: la findChild è ricorsiva e funziona anche coi nipoti
    findChild<GUI_UsersBar*>(GUI_UsersBar::getObjectName())->addOnlineUserIcon(userid, *color);
    GUI_MyTextEdit *son = findChild<GUI_MyTextEdit*>(GUI_MyTextEdit::getObjectName());

    //TODO: per ora sto mettendo delle posizioni a caso ma più avanti dovrò mettere quelle reali
    QPoint p = QPoint (son->cursorRect().topLeft().x(), son->cursorRect().topLeft().y() + son->verticalScrollBar()->value());
    findChild<GUI_MyTextEdit*>(GUI_MyTextEdit::getObjectName())->addUserCursor(userid, p, *color);
}

void GUI_Editor::removeUserFromEditorGUI(long userid){
    findChild<GUI_MyTextEdit*>(GUI_MyTextEdit::getObjectName())->removeUserCursor(userid);
    findChild<GUI_UsersBar*>(GUI_UsersBar::getObjectName())->removeOnlineUserIcon(userid);
    //se l'utente non è un contributor e non è più online gli tolgo il colore associato per poterlo assegnare a qualcun altro
    if(!findChild<GUI_UsersBar*>(GUI_UsersBar::getObjectName())->isContributor(userid))
        forgetUserColor(userid);
}

void GUI_Editor::addContributorToCurrentDocument(long userid){
    QColor *color = getUserColor(userid);
    findChild<GUI_UsersBar*>(GUI_UsersBar::getObjectName())->addContributorUserIcon(userid, *color);
}

void GUI_Editor::removeContributorFromCurrentDocument(long userid){
    findChild<GUI_UsersBar*>(GUI_UsersBar::getObjectName())->removeContributorUserIcon(userid);
    if(!findChild<GUI_UsersBar*>(GUI_UsersBar::getObjectName())->isOnline(userid))
        forgetUserColor(userid);
}

QColor *GUI_Editor::getUserColor(long userId){
    QColor *color;
    //controllo che l'user non abbia già un colore assegnato, o perchè si è disconnesso e riconnesso o perchè è già presente fra i contributors
    if(userColorMap.find(userId) == userColorMap.end() ){
        color = colorsManager.takeColor();
        userColorMap.insert(userId, color);
    }
    else
        color = userColorMap[userId];

    return color;
}

void GUI_Editor::forgetUserColor(long userId){
    if(userColorMap.find(userId) == userColorMap.end())
        return;

    colorsManager.returnColor(userColorMap[userId]);
    userColorMap.remove(userId);
}
