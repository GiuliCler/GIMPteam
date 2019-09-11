#ifndef ICONS_H
#define ICONS_H

#include <QVector>

class GUI_Icons{
public:

    static QString getIconPath(int id);
    static QVector<QString> *getIconPaths();

    static bool loaded, a;
    static QVector<QString> icons;

    static void load();
};

#endif // ICONS_H
