#ifndef ICONS_H
#define ICONS_H

#include <QVector>

class GUI_Icons{
public:
    //è la size dell'immagine nella myScrollArea
    static int iconSize;
    //è per caricare i path delle icone nel vettore una volta sola
    static bool loaded;
    static QVector<QString> icons;

    static QString getIconPath(long iconId);
    static QVector<QString> *getIconPaths();

    //riempe il vettore coi path
    static void load();
};

#endif // ICONS_H
