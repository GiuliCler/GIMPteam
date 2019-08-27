#ifndef GUI_LOGIN_H
#define GUI_LOGIN_H

#include <QWidget>
#include <QVBoxLayout>
#include "ui_gui_login.h"

class GUI_Login : public QWidget
{
    Q_OBJECT
public:
    explicit GUI_Login(QWidget *parent = nullptr);

private slots:
    void on_newAccountButton_clicked();

    void on_loginButton_clicked();

private:
    Ui::GUI_Login *ui;
};

#endif // GUI_LOGIN_H
