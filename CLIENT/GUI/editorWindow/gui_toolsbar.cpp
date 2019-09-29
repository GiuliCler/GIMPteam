#include "gui_toolsbar.h"
#include <QColorDialog>

GUI_ToolsBar::GUI_ToolsBar(QWidget *parent) : QWidget(parent){
    ui = new Ui::GUI_ToolsBar();
    ui->setupUi(this);

    //TODO: devo mettere 'ste istruzioni in una funzione apposta
    QPixmap p(16,16);
    p.fill(Stub::getCurrentTextColor());
    const QIcon ic(p);
    ui->colorPushButton->setIcon(ic);
}

GUI_ToolsBar::~GUI_ToolsBar(){
    delete ui;
}

void GUI_ToolsBar::on_colorPushButton_clicked(){
    QColor chosenColor = QColorDialog::getColor(); //return the color chosen by user
    QPixmap p(16,16);
    p.fill(chosenColor);
    const QIcon ic(p);
    ui->colorPushButton->setIcon(ic);

    //TODO:qualche stregoneria per cambiare colore al testo
}
