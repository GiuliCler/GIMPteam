#include "gui_toolsbar.h"

GUI_ToolsBar::GUI_ToolsBar(QWidget *parent) : QWidget(parent){
    ui = new Ui::GUI_ToolsBar();
    ui->setupUi(this);
}

GUI_ToolsBar::~GUI_ToolsBar(){
    delete ui;
}
