#include "gimpdocs.h"
#include "ui_gimpdocs.h"
#include <QBoxLayout>

GIMPdocs::GIMPdocs(QWidget *parent) : QDialog(parent), userid(-1)
{
    ui = new Ui::GIMPdocs;
    ui->setupUi(this);
    centralWidget = nullptr;

    layout = new QHBoxLayout(this);
    this->setLayout(layout);

    GUI_Login *loginWidget = new GUI_Login(this);
    loadCentralWidget(loginWidget);
}

GIMPdocs::~GIMPdocs(){
    delete ui;
}

void GIMPdocs::loadCentralWidget(QWidget* widget){
    if(widget == nullptr){
        //todo: gestire in qualche modo
        return;
    }
    if(centralWidget != nullptr)
        centralWidget->close();

    centralWidget = widget;
    layout->addWidget(widget);
    widget->show();
}
