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

    inline static int getMaxUsersIconsNumber(){return 10;}
    //il 2 bilancia il margin sotto, un 17 sta al posto della scrollbar e l'altro 17 sta sopra e bilancia la scrollbar per avere simmetria
    inline static int getFixedHeight(){return GUI_Icons::iconSize + (2+17) + 17;}
};

#endif // GUI_MYSCROLLAREA_H
