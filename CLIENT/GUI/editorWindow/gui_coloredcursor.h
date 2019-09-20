#ifndef GUI_COLOREDCURSOR_H
#define GUI_COLOREDCURSOR_H

#include <QWidget>
#include <QPaintEvent>
#include <QPoint>

class GUI_ColoredCursor : public QWidget
{
    Q_OBJECT
public:
    //DEBUG: il campo position è da togliere. Bisogna settare un valore iniziale di default
    explicit GUI_ColoredCursor(QWidget *parent, QPoint position, QColor color);
    void paint();

private:
    QPoint cursorPosition;
    QColor cursorColor;

public slots:
    void updatePosition(QPoint position);
};

#endif // GUI_COLOREDCURSOR_H
