#include "gui_mouseeventfilter.h"

#include <QDebug>


GUI_SetFilterStatus::GUI_SetFilterStatus(bool enabled) : QEvent(QEvent::User), enabled(enabled){
}

GUI_MouseEventFilter::GUI_MouseEventFilter(QObject *parent) : QObject(parent){
    this->setObjectName(GUI_MouseEventFilter::getObjectName());
}

bool GUI_MouseEventFilter::eventFilter(QObject *watched, QEvent *event){

    //if(watched == ui->hideColorsPushButton || event->type() == GUI_SetFilterStatus::eventType){
        //qDebug() << event->type();
    //}

    if(event->type() == GUI_SetFilterStatus::eventType)
        filter = static_cast<GUI_SetFilterStatus*>(event)->enabled;

    if(event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonDblClick){
        qDebug() << watched->objectName();
        qDebug() << filter;
        return filter;
    }

    return false;
}
