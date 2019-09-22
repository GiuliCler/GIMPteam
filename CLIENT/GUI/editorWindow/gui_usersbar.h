#ifndef GUI_USERSBAR_H
#define GUI_USERSBAR_H

#include <QWidget>
#include "ui_gui_usersbar.h"
#include "../gimpdocs.h"
#include "gui_editor.h"

class GUI_UsersBar : public QWidget
{
    Q_OBJECT
public:
    GUI_Editor *editorParent;

    explicit GUI_UsersBar(QWidget *parent);
    ~GUI_UsersBar();
    static QString getObjectName() {return QString("GUI_UsersBar");}


    //se serve posso metterci un codice di ritorno
    void addUserIcon(long userId, QColor color);
    void removeUserIcon(long userId);

private:
    Ui::GUI_UsersBar *ui;
    QMap<long, QLabel*> usersIconMap;
    static QString getOnlineAreaName() {return QString("onlineIconsScrollArea");}
    static QString getContributorsAreaName() {return QString("contributorIconsScrollArea");}

    QLabel *getUserIcon(long userId, QColor color);
    //adatto la size del widget in base a quanti users ci sono, ma solo fino ad un certo punto
    void updateIconsWidgetSize();
};

#endif // GUI_USERSBAR_H
