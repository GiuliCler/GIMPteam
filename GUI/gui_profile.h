#ifndef GUI_PROFILE_H
#define GUI_PROFILE_H

#include <QWidget>
#include "ui_gui_profile.h"


class GUI_Profile : public QWidget
{
    Q_OBJECT
public:
    explicit GUI_Profile(QWidget *parent = nullptr);

    //faccio una funzione statica anzichè una normale stringa perchè non posso assegnare qui il valore alla stringa
    static QString getObjectName() {return QString("gui_profile");}

private slots:
    void fillForm();
    void on_savePushButton_clicked();
    void on_backPushButton_clicked();

private:
    Ui::GUI_Profile *ui;
};



#endif // GUI_PROFILE_H
