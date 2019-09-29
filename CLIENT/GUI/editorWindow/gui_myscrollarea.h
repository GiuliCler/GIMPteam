#ifndef GUI_MYSCROLLAREA_H
#define GUI_MYSCROLLAREA_H

#include <QWidget>
#include <QScrollArea>
#include "../gui_icons.h"

class GUI_MyScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    QWidget *content;

    explicit GUI_MyScrollArea(QWidget *parent = nullptr);
//    virtual void resizeEvent(QResizeEvent *event) override;
    void updateSize(int numberOfUsers);
    inline static int getMaxUsersIconsNumber(){return 10;}
    inline static int getFixedHeight(){return GUI_Icons::iconSize + (2+17) + 17;}
};

#endif // GUI_MYSCROLLAREA_H
