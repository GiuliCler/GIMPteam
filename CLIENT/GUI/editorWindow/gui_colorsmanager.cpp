#include "gui_colorsmanager.h"
#include <QDebug>

GUI_ColorsManager::GUI_ColorsManager(){
    h = 0;
    sFlag = 2;
    vFlag = 1;
}

QColor *GUI_ColorsManager::takeColor(){
    //se qualcuno ha restituito dei colori creati in precedenza gli do quelli, altrimenti ne creo uno nuovo
    if(availableColors.size() != 0){
        QColor *color = availableColors.top();
        availableColors.pop();
        return color;
    }

   return newColor();
}

void GUI_ColorsManager::returnColor(QColor *color){
    availableColors.push_back(color);
}

QColor *GUI_ColorsManager::newColor(){
    qDebug() << h;
    QColor *color = new QColor();
    color->setHsv(h*8, 135 + 60* sFlag, 155 + 100*vFlag, 150);

    //genero 31*2*3 colori diversi. Poi si ripetono
    h = (h +7)%31;
    sFlag = (sFlag +1) %3;
    vFlag = (vFlag +1) %2;

    return color;
}
