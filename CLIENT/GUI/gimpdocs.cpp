#include "gimpdocs.h"
#include "gui_login.h"

#include <iostream>

GIMPdocs::GIMPdocs(QWidget *parent) : QMainWindow(parent), userid(-1)
{
    ui1 = new Ui::GIMPdocs;
    ui2 = new Ui::GUI_EditWindow;
    centralWidget = nullptr;

    setUi1(new GUI_Login(this));
}

GIMPdocs::~GIMPdocs(){
    delete ui1;
    delete ui2;
    //TODO gestire il puntatore a central widget
}

void GIMPdocs::setUi1(QWidget *widget){
    if(centralWidget != nullptr){
        centralWidget->close();
        centralWidget = nullptr;
    }
    ui1->setupUi(this);
    loadCentralWidget(widget);
}

void GIMPdocs::setUi2(QWidget *widget){
    if(centralWidget != nullptr){
        centralWidget->close();
        centralWidget = nullptr;
    }
    ui2->setupUi(this);
    loadCentralWidget(widget);
}

void GIMPdocs::loadCentralWidget(QWidget* widget){
    if(widget == nullptr){
        //TODO: gestire in qualche modo
        return;
    }
    if(centralWidget != nullptr)
        centralWidget->close();

    centralWidget = widget;
    this->setCentralWidget(widget);
    widget->show();
}
