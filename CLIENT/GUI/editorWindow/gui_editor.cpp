#include "gui_editor.h"
#include "../gimpdocs.h"
#include "../gui_menu.h"
#include "gui_mytextedit.h"
#include "gui_usersbar.h"
#include "../gui_uri.h"
#include "gui_toolsbar.h"
#include <memory>
#include <QBitmap>
#include <QPainter>
#include <QTime>
#include <QMessageBox>
#include <QTabBar>


GUI_Editor::GUI_Editor(QWidget *parent, long documentId) : QWidget(parent), documentId(documentId)
{
    this->setObjectName(GUI_Editor::getObjectName());
    gimpParent = static_cast<GIMPdocs*>(parent);
    ui = new Ui::GUI_Editor();
    ui->setupUi(this);

    //questo serve a togliere quel fastidioso bordino bianco attorno alle labels del tabwidget
    ui->tabWidget->tabBar()->setStyleSheet(ui->tabWidget->tabBar()->styleSheet().append("background: rgb(240,240,240);"));

    GUI_MyTextEdit *textEdit = new GUI_MyTextEdit(this);
    ui->textWidget->layout()->addWidget(textEdit);
    GUI_UsersBar *usersbar = new GUI_UsersBar(this);
    ui->usersBarWidget->layout()->addWidget(usersbar);
    GUI_ToolsBar *toolsbar = new GUI_ToolsBar(this);
    ui->toolsBarWidget->layout()->addWidget(toolsbar);

    //ottengo l'elenco degli utenti che al momento stanno guardando il mio stesso document e ne creo icona e cursore
    std::shared_ptr<QSet<long>> users = Stub::getWorkingUsersOnDocument(documentId);
    for (QSet<long>::iterator userId = users->begin(); userId != users->end(); userId++){
        addUserToEditorGUI(*userId);
    }

    //creo l'icona per gli user che hanno contribuito al document
    std::shared_ptr<QSet<long>> contributors = Stub::getContributorsUsersOnDocument(documentId);
    for (QSet<long>::iterator userId = contributors->begin(); userId != contributors->end(); userId++){
        addContributorToCurrentDocument(*userId);
    }

    /*
    //debug purpose only
    timer = new QTimer(this);
    timer->start(3000);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerSlot()));*/
}

GUI_Editor::~GUI_Editor(){
    delete ui;
}

void GUI_Editor::connectMenuBarActions(){
    connect(this->gimpParent->ui2->closeDocumentAction, &QAction::triggered, this, &GUI_Editor::launchSetUi1);
    connect(gimpParent->ui2->getURIAction, &QAction::triggered, [this](){
        GUI_URI *box = new GUI_URI(this, Stub::getDocumentURI(documentId));
        box->setVisible(true);
    });
}

void GUI_Editor::launchSetUi1(){
    Stub::closeDocument(this->gimpParent->userid, documentId);

    GUI_Menu *widget = new GUI_Menu(this->gimpParent);
    static_cast<GIMPdocs*>(this->gimpParent)->setUi1(widget);
}

void GUI_Editor::addUserToEditorGUI(long userid){

    //ottengo un colore per cursore e icona
    QColor *color;
    //controllo che l'user non abbia già u colore assegnato, o perchè si è disconnesso e riconnesso o perchè è già presente fra i contributors
    if(userColorMap.find(userid) == userColorMap.end() ){
        color = colorsManager.takeColor();
        userColorMap.insert(userid, color);
    }
    else{
        color = userColorMap[userid];
    }

    //nota: la findChild è ricorsiva e funziona anche coi nipoti
    findChild<GUI_UsersBar*>(GUI_UsersBar::getObjectName())->addOnlineUserIcon(userid, *color);
    findChild<GUI_MyTextEdit*>(GUI_MyTextEdit::getObjectName())->addUserCursor(userid, QPoint(userid *2, 4), *color);
}

void GUI_Editor::removeUserFromEditorGUI(long userid){
    findChild<GUI_UsersBar*>(GUI_UsersBar::getObjectName())->removeOnlineUserIcon(userid);
    findChild<GUI_MyTextEdit*>(GUI_MyTextEdit::getObjectName())->removeUserCursor(userid);
}

void GUI_Editor::addContributorToCurrentDocument(long userid){
    //nota, il CLIENT può comparire fra i contributors

    //ottengo un colore per cursore e icona
    QColor *color;
    //controllo che l'user non abbia già u colore assegnato, o perchè si è disconnesso e riconnesso o perchè è già presente fra i contributors
    if(userColorMap.find(userid) == userColorMap.end() ){
        color = colorsManager.takeColor();
        userColorMap.insert(userid, color);
    }
    else{
        color = userColorMap[userid];
    }

    //nota: la findChild è ricorsiva e funziona anche coi nipoti
    findChild<GUI_UsersBar*>(GUI_UsersBar::getObjectName())->addContributorUserIcon(userid, *color);
}

void GUI_Editor::removeContributorFromCurrentDocument(long userid){
    findChild<GUI_UsersBar*>(GUI_UsersBar::getObjectName())->removeContributorUserIcon(userid);
}

//serve solo per il debug
void GUI_Editor::timerSlot(){

    //addUserToEditorGUI(QRandomGenerator::global()->bounded(2000));
}
