#ifndef GUI_MENU_H
#define GUI_MENU_H

#include "ui_gui_menu.h"
#include "gimpdocs.h"
#include <QWidget>

class GUI_Menu : public QWidget
{
    Q_OBJECT
public:
    GIMPdocs *gimpParent;

    explicit GUI_Menu(QWidget *parent);
    ~GUI_Menu();
    inline static QString getObjectName(){ return "GUI_Menu";}

private slots:
    void on_editPushButton_clicked();
    void on_logoutPushButton_clicked();

private:
    Ui::GUI_Menu *ui;

    void setDocumentArea();
    void setProfileArea();
};

#endif // GUI_MENU_H
