#ifndef GUI_USERSBAR_H
#define GUI_USERSBAR_H

#include "ui_gui_usersbar.h"
#include "../gimpdocs.h"
#include "gui_editor.h"
#include <QWidget>

class GUI_UsersBar : public QWidget
{
    Q_OBJECT
public:
    GUI_Editor *editorParent;

    explicit GUI_UsersBar(QWidget *parent);
    ~GUI_UsersBar();
    static QString getObjectName() {return QString("GUI_UsersBar");}

    //se serve posso metterci un codice di ritorno
    void addOnlineUserIcon(int userId, QColor color);
    void removeOnlineUserIcon(int userId);
    void addContributorUserIcon(int userId, QColor color);
    void removeContributorUserIcon(int userId);

    bool isOnline(int userId);
    bool isContributor(int userId);

public slots:
    //questi 2 metodi non servono solo per la users bar, ma anche per attivare il comando che cambia colore al testo
    void on_showColorsPushButton_clicked();
    void on_hideColorsPushButton_clicked();

    //per il debug
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

private:
    Ui::GUI_UsersBar *ui;
    //mi serve quando devo fare la remove
    QMap<int, QLabel*> onlineUsersIconMap;
    QMap<int, QLabel*> contributorUsersIconMap;

    //serve per ritrovare i figli. Avrei anche potuto salvarmi direttamente un pointer ai figli
    inline static QString getOnlineAreaName() {return QString("onlineIconsScrollArea");}
    inline static QString getContributorsAreaName() {return QString("contributorIconsScrollArea");}
    QLabel *getUserIcon(int userId, QColor color);
};

#endif // GUI_USERSBAR_H
