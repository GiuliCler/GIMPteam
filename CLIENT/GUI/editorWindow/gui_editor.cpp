#include "gui_editor.h"
#include "../gimpdocs.h"
#include "../gui_menu.h"
#include "gui_mytextedit.h"
#include "gui_usersbar.h"
#include <memory>
#include <QBitmap>
#include <QPainter>

GUI_Editor::GUI_Editor(QWidget *parent, long documentId) : QWidget(parent), documentId(documentId)
{
    this->setObjectName(GUI_Editor::getObjectName());
    gimpParent = static_cast<GIMPdocs*>(parent);
    ui = new Ui::GUI_Editor();
    ui->setupUi(this);

    GUI_UsersBar *usersbar = new GUI_UsersBar(this);
    ui->usersBarWidget->layout()->addWidget(usersbar);
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


//serve solo per il debug
void GUI_Editor::timerSlot(){

    GUI_MyTextEdit *textEditor = this->findChild<GUI_MyTextEdit*>(GUI_MyTextEdit::getObjectName());
    if(! textEditor->hasFocus())
        return;

    QPoint position(textEditor->cursorRect().x(), textEditor->cursorRect().y());
    textEditor->addUserCursor(1, position);
}
