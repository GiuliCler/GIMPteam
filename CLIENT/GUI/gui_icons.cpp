#include "gui_icons.h"
#include <QDirIterator>

//è la dimensione in pixels
int GUI_Icons::iconSize = 28;
bool GUI_Icons::loaded = false;
// lo inizializzo qui perchè è static
QVector<QString> GUI_Icons::icons;

void GUI_Icons::load(){
    //itero su tutte le risorse che ho registrato nell'index "icons" del file di risorse .qrc
    QDirIterator it(":/icons", QDirIterator::Subdirectories);
    int i = 0;

    while (it.hasNext()) {
        GUI_Icons::icons.insert(i, it.next());
        i++;
    }

    loaded = true;
}

QVector<QString> *GUI_Icons::getIconPaths(){
    if(!loaded)
        load();
    return &GUI_Icons::icons;
}

QString GUI_Icons::getIconPath(long iconId){
    if(!loaded)
        load();

    if(iconId < 0 || icons.length() <= iconId)
        return "";

    return icons[iconId];
}
