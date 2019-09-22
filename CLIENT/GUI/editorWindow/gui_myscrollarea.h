#ifndef GUI_MYSCROLLAREA_H
#define GUI_MYSCROLLAREA_H

#include <QWidget>
#include <QScrollArea>

class GUI_MyScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    QWidget *content;

    explicit GUI_MyScrollArea(QWidget *parent = nullptr);
    virtual void resizeEvent(QResizeEvent *event) override;
    void updateSize(int numberOfUsers);
};

#endif // GUI_MYSCROLLAREA_H
