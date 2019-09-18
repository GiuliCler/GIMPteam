#ifndef GUI_EDITOR_H
#define GUI_EDITOR_H

#include <QWidget>
#include "ui_gui_editor.h"
#include <QTimer>

class GUI_Editor : public QWidget
{
    Q_OBJECT
public:
    long documentId;

    explicit GUI_Editor(QWidget *parent, long documentId);
    ~GUI_Editor();
    inline static QString getObjectName(){ return "GUI_Editor";}

    //se serve posso metterci un codice di ritorno
    void addUserIcon(long userId);
    void removeUserIcon(long userId);

private slots:
    //debug
    void timerSlot();

private:
    Ui::GUI_Editor *ui;
    QMap<long, QLabel*> usersIconMap;
    //debug
    QTimer *timer;

    void setUsersBar();
    QLabel *getUserIcon(long userId);
    //adatto la size del widget in base a quanti users ci sono, ma solo fino ad un certo punto
    void updateIconsWidgetSize();
};

#endif // GUI_EDITOR_H
