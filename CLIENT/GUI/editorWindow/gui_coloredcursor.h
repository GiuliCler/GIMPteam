#ifndef GUI_COLOREDCURSOR_H
#define GUI_COLOREDCURSOR_H

#include <QWidget>
#include <QTextEdit>

class GUI_ColoredCursor : public QObject
{
    Q_OBJECT
public:
    explicit GUI_ColoredCursor(QWidget *parent, QPoint position, QColor color);
    void paint();

private:
    QTextEdit *textEditParent;
    QPoint cursorPosition;
    QColor cursorColor;

public slots:
    void updatePosition(QPoint position);
};

#endif // GUI_COLOREDCURSOR_H
