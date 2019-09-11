#include "gimpdocs.h"
#include "gui_login.h"


GIMPdocs::GIMPdocs(QWidget *parent) : QMainWindow(parent), userid(-1)
{
    ui = new Ui::GIMPdocs;
    ui->setupUi(this);
    centralWidget = nullptr;

    //layout = new QHBoxLayout(this);
    //this->setLayout(layout);

    GUI_Login *loginWidget = new GUI_Login(this);
    loadCentralWidget(loginWidget);
}

GIMPdocs::~GIMPdocs(){
    delete ui;
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
