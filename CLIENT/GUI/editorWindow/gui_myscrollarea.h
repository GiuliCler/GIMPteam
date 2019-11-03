#ifndef GUI_MYSCROLLAREA_H
#define GUI_MYSCROLLAREA_H

#include <QScrollArea>
#include "../gimpdocs.h"

class GUI_MyScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    QWidget *content;

    explicit GUI_MyScrollArea(QWidget *parent = nullptr);
    void updateSize(int numberOfUsers);

    inline static int getMaxUsersIconsNumber(){return 7;}
    inline static int getFixedScrollBarHeight(){return 12;}
    //il 2 bilancia il margin sotto, un 17 sta al posto della scrollbar e l'altro 17 sta sopra e bilancia la scrollbar per avere simmetria
    inline static int getFixedHeight(){return GUI_MyScrollArea::getFixedScrollBarHeight() + 1 + GUI_Icons::iconSize + 1 + GUI_MyScrollArea::getFixedScrollBarHeight();}
};

#endif // GUI_MYSCROLLAREA_H
