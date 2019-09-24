#include "gimpdocs.h"
#include "gui_login.h"
#include "gui_menu.h"
#include "editorWindow/gui_editor.h"

#include <iostream>
#include <QWindow>

GIMPdocs::GIMPdocs(QWidget *parent) : QMainWindow(parent), userid(-1)
{
    ui1 = new Ui::GIMPdocs;
    ui2 = new Ui::GUI_EditWindow;

    setUi1(new GUI_Login(this));
}

GIMPdocs::~GIMPdocs(){
    delete ui1;
    delete ui2;
}

void GIMPdocs::setUi1(QWidget *widget){
    //serve ad annullare showMaximized
    showNormal();
    ui1->setupUi(this);
    this->setCentralWidget(widget);

}

void GIMPdocs::setUi2(QWidget *widget){

    ui2->setupUi(this);
    this->setCentralWidget(widget);
    //è importante che showMaximized venga lanciato dopo il cambio di ui perchè sì, atrimenti fa casini
    showMaximized();

    connect(ui2->closeDocumentAction, SIGNAL(triggered()), this, SLOT(launchSetUi2()));
}

void GIMPdocs::launchSetUi2(){
    long docId = this->findChild<GUI_Editor*>(GUI_Editor::getObjectName())->documentId;
    Stub::closeDocument(this->userid, docId);

    GUI_Menu *widget = new GUI_Menu(this);
    this->setUi1(widget);
}

