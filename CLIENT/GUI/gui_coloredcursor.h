#ifndef GUI_COLOREDCURSOR_H
#define GUI_COLOREDCURSOR_H

#include <QWidget>
#include <QPaintEvent>
#include <QPoint>

class GUI_ColoredCursor : public QWidget
{
    Q_OBJECT
public:
    explicit GUI_ColoredCursor(QWidget *parent, QPoint position);
    //TODO: un costruttore che prenda un QRect
    void triggerPaintEvent(QPaintEvent *event);

private:
    QRect *cursorRec;
    //TODO: bisogna decidere se lasciarlo lampeggiare o no
    //QTimer *timer;
    bool cursorVisible;

protected:
    virtual void paintEvent(QPaintEvent *pEvent) override;

public slots:
    void updatePosition(int x0, int y0);
    void timerSlot();
};

#endif // GUI_COLOREDCURSOR_H
