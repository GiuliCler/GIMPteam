#ifndef ICONS_H
#define ICONS_H

#include <QMap>

class GUI_Icons{
public:
    //è la size dell'immagine nella myScrollArea
    static int iconSize;

    static QString getIconPath(QString iconId);
    static QMap<QString, QString> *getIconPaths();    

private:
    //è per caricare i path delle icone nel vettore una volta sola
    static bool loaded;
    static QMap<QString, QString> icons;

    //riempe il vettore coi path
    static void load();
};

#endif // ICONS_H
