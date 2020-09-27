#ifndef GUI_USERSBAR_H
#define GUI_USERSBAR_H

#include "ui_gui_usersbar.h"
#include "../gimpdocs.h"
#include "gui_editor.h"
#include <QWidget>

class GUI_MyEvent : public QEvent{

public:
    explicit GUI_MyEvent();
    static const QEvent::Type myType = static_cast<QEvent::Type>(QEvent::User);

};

class GUI_UsersBar : public QWidget
{
    Q_OBJECT
public:
    explicit GUI_UsersBar(QWidget *parent);
    inline static QString getObjectName() {return QString("GUI_UsersBar");}

    void addOnlineUserIcon(int userId, QColor color, QString nickname, QString iconId);
    void removeOnlineUserIcon(int userId);
    void addContributorUserIcon(int userId, QColor color, QString nickname, QString iconId);

    virtual bool eventFilter(QObject *watched, QEvent *event) override;
    //virtual void childEvent(QChildEvent *event) override;

public slots:
    //questi 2 metodi non servono solo per la users bar, ma anche per attivare il comando che cambia colore al testo
    void on_showColorsPushButton_clicked();
    void on_hideColorsPushButton_clicked();

private:
    GUI_Editor *editorParent;
    std::unique_ptr<Ui::GUI_UsersBar> ui;
    QMap<int, QLabel*> onlineUsersIconMap;
    QMap<int, QLabel*> contributorUsersIconMap;

    //serve per ritrovare i figli. Avrei anche potuto salvarmi direttamente un pointer ai figli
    inline static QString getOnlineAreaName() {return QString("onlineIconsScrollArea");}
    inline static QString getContributorsAreaName() {return QString("contributorIconsScrollArea");}
    QLabel *getUserIcon(QColor color, QString nickname, QString iconId);

    bool filter = false;

signals:
    //void highlightingUsers(bool value);
};

#endif // GUI_USERSBAR_H
