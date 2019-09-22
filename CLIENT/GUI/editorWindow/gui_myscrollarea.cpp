#include "gui_myscrollarea.h"
#include <QHBoxLayout>

GUI_MyScrollArea::GUI_MyScrollArea(QWidget *parent) : QScrollArea(parent){
    setWidgetResizable(true);
    content = new QWidget(this);
    content->setLayout(new QHBoxLayout(content));
    this->setWidget(content);
}

void GUI_MyScrollArea::resizeEvent(QResizeEvent *event){
    // Define content margins here
    //setViewportMargins(0, 0, 0, 0); // <<<<< SET MARGINS HERE
    QScrollArea::resizeEvent(event);
}
