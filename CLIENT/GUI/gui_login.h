#ifndef GUI_LOGIN_H
#define GUI_LOGIN_H

#include "ui_gui_login.h"
#include "gimpdocs.h"
#include <QWidget>

class GUI_Login : public QWidget
{
    Q_OBJECT

public:
    explicit GUI_Login(QWidget *parent);
    //faccio una funzione statica anzichè una normale stringa perchè non posso assegnare qui il valore alla stringa
    inline static QString getObjectName(){ return "GUI_Login";}

private slots:
    void on_newAccountButton_clicked();
    void on_loginButton_clicked();

private:
    GIMPdocs *gimpParent;
    std::unique_ptr<Ui::GUI_Login> ui;

    bool checkFieldValidity(QString value, QString name);
};

#endif // GUI_LOGIN_H
