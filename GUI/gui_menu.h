#ifndef GUI_MENU_H
#define GUI_MENU_H

#include <QWidget>
#include "ui_gui_menu.h"

class GUI_Menu : public QWidget
{
    Q_OBJECT
public:
    explicit GUI_Menu(QWidget *parent);

private slots:
    void on_editPushButton_clicked();
    void on_logoutPushButton_clicked();

private:
    Ui::GUI_Menu *ui;

    void setDocumentArea();
    void setProfileArea();
};

#endif // GUI_MENU_H
