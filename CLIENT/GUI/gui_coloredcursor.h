#ifndef GUI_COLOREDCURSOR_H
#define GUI_COLOREDCURSOR_H

#include <QWidget>
#include <QPaintEvent>
#include <QPoint>

class GUI_ColoredCursor : public QWidget
{
    Q_OBJECT
public:
    //TODO: devo lasciar selezionare il colore... forse potrei farmi una tabella hardcoded e deciderlo io in base a quanti sono nella mappa
    explicit GUI_ColoredCursor(QWidget *parent, QPoint position);
    void paint();

private:
    QPoint cursorPosition;
    QColor cursorColor;

public slots:
    void updatePosition(QPoint position);
};

#endif // GUI_COLOREDCURSOR_H
