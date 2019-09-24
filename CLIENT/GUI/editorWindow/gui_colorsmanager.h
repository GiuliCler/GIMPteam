#ifndef GUI_COLORSMANAGER_H
#define GUI_COLORSMANAGER_H

#include <QObject>
#include <QColor>
#include <QStack>

class GUI_ColorsManager : public QObject
{
    Q_OBJECT
public:
    explicit GUI_ColorsManager();
    QColor *takeColor();
    void returnColor(QColor *color);

private:
    QStack<QColor*> availableColors;
    //sfrutto il modello HSV
    int h;
    int sFlag;
    int vFlag;

    //genera nuovi colori quando lo stack è vuoto
    QColor *newColor();
};

#endif // GUI_COLORSMANAGER_H
