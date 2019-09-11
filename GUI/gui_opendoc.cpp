#include "gui_opendoc.h"
#include "gimpdocs.h"
#include "gui_menu.h"

GUI_Opendoc::GUI_Opendoc(QWidget *parent) : QWidget(parent)
{
    ui = new Ui::GUI_Opendoc;
    ui->setupUi(this);
}

GUI_Opendoc::~GUI_Opendoc(){
    delete ui;
}
