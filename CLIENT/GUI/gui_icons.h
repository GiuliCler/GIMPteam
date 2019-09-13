#ifndef ICONS_H
#define ICONS_H

#include <QVector>

class GUI_Icons{
public:
    static int iconSize;
    //è per caricare i path delle icone nel vettore una volta sola
    static bool loaded, a;
    static QVector<QString> icons;

    static QString getIconPath(long userId);
    static QVector<QString> *getIconPaths();

    //riempe il vettore coi path
    static void load();
};

#endif // ICONS_H
