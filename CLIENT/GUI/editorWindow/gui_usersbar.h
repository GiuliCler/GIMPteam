#ifndef GUI_USERSBAR_H
#define GUI_USERSBAR_H

#include <QWidget>
#include "ui_gui_usersbar.h"
#include "../gimpdocs.h"

class GUI_UsersBar : public QWidget
{
    Q_OBJECT
public:
    explicit GUI_UsersBar(QWidget *parent);
    ~GUI_UsersBar();

    //se serve posso metterci un codice di ritorno
    void addUserIcon(long userId);
    void removeUserIcon(long userId);

private:
    Ui::GUI_UsersBar *ui;
    QMap<long, QLabel*> usersIconMap;

    QLabel *getUserIcon(long userId);
    //adatto la size del widget in base a quanti users ci sono, ma solo fino ad un certo punto
    void updateIconsWidgetSize();
};

#endif // GUI_USERSBAR_H
