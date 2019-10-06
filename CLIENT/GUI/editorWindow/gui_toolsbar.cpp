#include "gui_toolsbar.h"
#include <QColorDialog>

GUI_ToolsBar::GUI_ToolsBar(QWidget *parent) : QWidget(parent){
    ui = new Ui::GUI_ToolsBar();
    ui->setupUi(this);

    setTextColorIconColor(Stub::getCurrentTextColor());
}

GUI_ToolsBar::~GUI_ToolsBar(){
    delete ui;
}

void GUI_ToolsBar::on_colorPushButton_clicked(){
    QColor chosenColor = QColorDialog::getColor(); //return the color chosen by user
    setTextColorIconColor(chosenColor);

    Stub::setCurrentTextColor(chosenColor);
}

void GUI_ToolsBar::setTextColorIconColor(const QColor color){
    QPixmap p(16,16);
    p.fill(color);
    const QIcon ic(p);
    ui->colorPushButton->setIcon(ic);
}
