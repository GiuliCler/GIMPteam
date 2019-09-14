#include "gui_icons.h"

#include <QDirIterator>

int GUI_Icons::iconSize = 30;
bool GUI_Icons::loaded = false;
QVector<QString> GUI_Icons::icons;

void GUI_Icons::load(){
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
    //TODO fare un check di sicurezza su id
    return icons[userId];
}
