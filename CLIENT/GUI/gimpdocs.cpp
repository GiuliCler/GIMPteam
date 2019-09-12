#include "gimpdocs.h"
#include "gui_login.h"

#include <iostream>

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
    ui1->setupUi(this);
    this->setCentralWidget(widget);
}

void GIMPdocs::setUi2(QWidget *widget){
    ui2->setupUi(this);
    this->setCentralWidget(widget);
}
