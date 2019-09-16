#ifndef GUI_MYTEXTEDIT_H
#define GUI_MYTEXTEDIT_H

#include <QTextEdit>
#include <QTimer>

class GUI_MyTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit GUI_MyTextEdit(QWidget *parent = nullptr);

private:
    QTimer *timer;
    //QPainter *painter;
    bool cursorVisible;

protected:
    virtual void paintEvent(QPaintEvent *pEvent) override;
/*
signals:
    void sendUpdate();*/

public slots:
    void timerSlot();
};

#endif // GUI_MYTEXTEDIT_H
