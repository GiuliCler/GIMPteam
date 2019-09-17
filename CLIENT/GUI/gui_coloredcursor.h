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

protected:
    //TODO: voglio verificare se viene mai chiamata: sembra di no
    //virtual void paintEvent(QPaintEvent *pEvent) override;

public slots:
    void updatePosition(QPoint position);
};

#endif // GUI_COLOREDCURSOR_H
