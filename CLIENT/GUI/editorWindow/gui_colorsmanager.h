#ifndef GUI_COLORSMANAGER_H
#define GUI_COLORSMANAGER_H

#include <QObject>
#include <QColor>

/*L'idea era di avere un allocatore di colori, ma poi gli utenti sono diventati contributors a vita*/

class GUI_ColorsManager : public QObject
{
    Q_OBJECT
public:
    explicit GUI_ColorsManager();
    QColor newColor();

private:
    //sfrutto il modello HSV
    int h;
    int sFlag;
    int vFlag;

};

#endif // GUI_COLORSMANAGER_H
