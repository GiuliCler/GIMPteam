#include "gui_editor.h"
#include "../gimpdocs.h"
#include "../gui_menu.h"
#include "gui_mytextedit.h"
#include "gui_usersbar.h"
#include <memory>
#include <QBitmap>
#include <QPainter>
#include <QTime>

GUI_Editor::GUI_Editor(QWidget *parent, long documentId) : QWidget(parent), documentId(documentId)
{
    this->setObjectName(GUI_Editor::getObjectName());
    gimpParent = static_cast<GIMPdocs*>(parent);
    ui = new Ui::GUI_Editor();
    ui->setupUi(this);

    GUI_UsersBar *usersbar = new GUI_UsersBar(this);
    ui->usersBarWidget->layout()->addWidget(usersbar);
    //ottengo l'elenco degli utenti che al momento stanno guardando il mio stesso document e ne creo icona e cursore
    std::shared_ptr<QSet<long>> users = Stub::getWorkingUsersOnDocument(documentId);
    /*for (QSet<long>::iterator userId = users->begin(); userId != users->end(); userId++){
        addUserToEditorGUI(*userId);
    }*/

    GUI_MyTextEdit *textEdit = new GUI_MyTextEdit(this);
    ui->textWidget->layout()->addWidget(textEdit);

    //debug purpose only
    timer = new QTimer(this);
    timer->start(5000);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerSlot()));
}

GUI_Editor::~GUI_Editor(){
    delete ui;
}

void GUI_Editor::addUserToEditorGUI(long userid){
    //controllo che per qualche ragione l'user non sia già presente e non sia il CLIENT stesso che sta usando l'intefrfaccia
    if(userColorMap.find(userid) != userColorMap.find(userid) || userid == gimpParent->userid){
        //TODO: gestione intelligente
        return;
    }

    QColor *color = new QColor;
    QRandomGenerator rg;
    color->setHsv(rg.global()->bounded(32)*8, 255, 255, 150);

    findChild<GUI_UsersBar*>(GUI_UsersBar::getObjectName())->addUserIcon(userid, *color);
    findChild<GUI_MyTextEdit*>(GUI_MyTextEdit::getObjectName())->addUserCursor(userid, QPoint(userid *20, 4), *color);
}

void GUI_Editor::removeUserFromEditorGUI(long userid){
    findChild<GUI_UsersBar*>(GUI_UsersBar::getObjectName())->removeUserIcon(userid);
    findChild<GUI_MyTextEdit*>(GUI_MyTextEdit::getObjectName())->removeUserCursor(userid);
}

//serve solo per il debug
void GUI_Editor::timerSlot(){

    /*GUI_MyTextEdit *textEditor = this->findChild<GUI_MyTextEdit*>(GUI_MyTextEdit::getObjectName());
    if(! textEditor->hasFocus())
        return;*/

    addUserToEditorGUI(QRandomGenerator::global()->bounded(20));
}
