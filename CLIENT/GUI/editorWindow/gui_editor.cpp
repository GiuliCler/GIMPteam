#include "gui_editor.h"
#include "../gui_menu.h"
#include "../gui_uri.h"
#include "gui_mytextedit.h"
#include "gui_usersbar.h"
#include "gui_toolsbar.h"
#include "gui_myscrollarea.h"
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

    //questo serve a togliere quel fastidioso bordino bianco attorno alle labels del tabwidget
    //ui->tabWidget->tabBar()->setStyleSheet(ui->tabWidget->tabBar()->styleSheet().append("background: rgb(240,240,240);"));
    //la toolsbar è più bassa, quindi ne eguaglio la height alla height della users bar
    //toolsbar->setMinimumHeight(GUI_MyScrollArea::getFixedHeight());


    //ottengo l'elenco degli utenti che al momento stanno guardando il mio stesso document e ne creo icona e cursore
    std::shared_ptr<QSet<long>> users = Stub::getWorkingUsersOnDocument(documentId);
    for (QSet<long>::iterator userId = users->begin(); userId != users->end(); userId++)
        addUserToEditorGUI(*userId);

    //creo l'icona per gli user che hanno contribuito al document
    std::shared_ptr<QSet<long>> contributors = Stub::getContributorsUsersOnDocument(documentId);
    for (QSet<long>::iterator userId = contributors->begin(); userId != contributors->end(); userId++)
        addContributorToCurrentDocument(*userId);

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

void GUI_Editor::on_actionBold(){
    //questo serve a counterare il fatto che in caso di click il button cambia automaticamente stato da chechek ad unchechek e viceversa, ma voglio essere io a decidere quando cambiare stato
    childToolsBar->ui->boldPushButton->setChecked(!childToolsBar->ui->boldPushButton->isChecked());

    //non so se devo cambiare lo stato di checked o no, quindi lo chiedo al text editor
    childToolsBar->ui->boldPushButton->setChecked(Stub::isGenericFontAttributeActivated(childToolsBar->ui->boldPushButton->isChecked()));
}

void GUI_Editor::on_actionItalic(){
    /*childToolsBar->ui->italicPushButton->setChecked(!childToolsBar->ui->boldPushButton->isChecked());

    childToolsBar->ui->italicPushButton->setChecked(Stub::isGenericFontAttributeActivated(childToolsBar->ui->boldPushButton->isChecked()));
    */
    childToolsBar->ui->italicPushButton->setDown(!childToolsBar->ui->italicPushButton->isDown());
    //childToolsBar->ui->strikethroughPushButton->setDown(true);
}

void GUI_Editor::on_actionUnderlined(){
    //questo serve a counterare il fatto che in caso di click il button cambia automaticamente stato da chechek ad unchechek e viceversa, ma voglio essere io a decidere quando cambiare stato
    childToolsBar->ui->underlinedPushButton->setChecked(!childToolsBar->ui->boldPushButton->isChecked());

    //non so se devo cambiare lo stato di checked o no, quindi lo chiedo al text editor
    childToolsBar->ui->underlinedPushButton->setChecked(Stub::isGenericFontAttributeActivated(childToolsBar->ui->boldPushButton->isChecked()));
}

void GUI_Editor::on_actionStrikethrough(){
    //questo serve a counterare il fatto che in caso di click il button cambia automaticamente stato da chechek ad unchechek e viceversa, ma voglio essere io a decidere quando cambiare stato
    childToolsBar->ui->strikethroughPushButton->setChecked(!childToolsBar->ui->boldPushButton->isChecked());

    //non so se devo cambiare lo stato di checked o no, quindi lo chiedo al text editor
    childToolsBar->ui->strikethroughPushButton->setChecked(Stub::isGenericFontAttributeActivated(childToolsBar->ui->boldPushButton->isChecked()));

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
