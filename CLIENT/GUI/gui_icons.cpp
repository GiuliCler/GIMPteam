#include "gui_icons.h"
#include <QDirIterator>

// li inizializzo qui perchè sono static
bool GUI_Icons::loaded = false;
QMap<QString, QString> GUI_Icons::icons;


void GUI_Icons::load(){
    //itero su tutte le risorse che ho registrato nell'index "icons" del file di risorse .qrc
    QDirIterator it(":/icons", QDirIterator::Subdirectories);

    QString path;
    while (it.hasNext()) {
        path =it.next();
        GUI_Icons::icons.insert(it.fileName(), path);
    }

    loaded = true;
}

QMap<QString, QString> *GUI_Icons::getIconPaths(){
    if(!loaded)
        load();
    return &GUI_Icons::icons;
}

QString GUI_Icons::getIconPath(QString iconId){
    if(!loaded)
        load();

    if(icons.find(iconId) == icons.end())
        return "";

    return icons.value(iconId);
}
