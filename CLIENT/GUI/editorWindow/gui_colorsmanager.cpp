#include "gui_colorsmanager.h"
#include <QDebug>

GUI_ColorsManager::GUI_ColorsManager(){
    //metto questi valori per iniziare dal rosso
    h = 0;
    sFlag = 2;
    vFlag = 1;
}

/*QColor *GUI_ColorsManager::takeColor(){
    //se qualcuno ha restituito dei colori creati in precedenza gli do uno di quelli, altrimenti ne creo uno nuovo
    if(availableColors.size() != 0){
        QColor *color = availableColors.top();
        availableColors.pop();
        return color;
    }

   return newColor();
}

void GUI_ColorsManager::returnColor(QColor *color){
    availableColors.push_back(color);
}*/

QColor *GUI_ColorsManager::newColor(){
    QColor *color = new QColor();
    color->setHsv(h*12, 105 + 75 * sFlag, 205 + 50*vFlag, 180);

    //genero 29*2*3 colori diversi. Poi si ripetono, ma se riesco ad usare lo stack potrei evitarlo
    h = (h +11)%29;
    sFlag = (sFlag +1) %3;
    vFlag = (vFlag +1) %2;

    return color;
}
