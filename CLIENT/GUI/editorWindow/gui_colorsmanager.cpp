#include "gui_colorsmanager.h"

GUI_ColorsManager::GUI_ColorsManager(){
    //metto questi valori per iniziare dal rosso
    h = 0;
    sFlag = 2;
    vFlag = 1;
}

QColor GUI_ColorsManager::newColor(){
    QColor color = QColor();
    color.setHsv(h*12, 105 + 75 * sFlag, 205 + 50*vFlag, 180);

    //genero 29*2*3 colori diversi. Poi si ripetono
    h = (h +11)%29;
    sFlag = (sFlag +1) %3;
    vFlag = (vFlag +1) %2;

    return color;
}
