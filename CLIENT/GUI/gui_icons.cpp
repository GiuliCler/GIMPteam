#include "gui_icons.h"
#include <QDirIterator>

//è la dimensione in pixels
int GUI_Icons::iconSize = 30;
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

QString GUI_Icons::getIconPath(long userId){
    if(!loaded)
        load();
    //TODO fare un check di sicurezza su id... ma forse non serve... aspetto di vedere come salviamo alla fine le immagini nel DB
    return icons[userId];
}
