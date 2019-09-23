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
    void addOnlineUserIcon(long userId, QColor color);
    void removeOnlineUserIcon(long userId);
    void addContributorUserIcon(long userId, QColor color);
    void removeContributorUserIcon(long userId);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_showColorsPushButton_clicked();

    void on_hideColorsPushButton_clicked();

private:
    Ui::GUI_UsersBar *ui;
    QMap<long, QLabel*> usersIconMap;

    //serve per ritrovare i figli. Avrei anche potuto salvarmi direttamente un pointer ai figli
    static QString getOnlineAreaName() {return QString("onlineIconsScrollArea");}
    static QString getContributorsAreaName() {return QString("contributorIconsScrollArea");}
    QLabel *getUserIcon(long userId, QColor color);
};

#endif // GUI_USERSBAR_H
