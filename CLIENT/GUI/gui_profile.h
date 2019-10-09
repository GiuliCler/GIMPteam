#ifndef GUI_PROFILE_H
#define GUI_PROFILE_H

#include "ui_gui_profile.h"
#include "gimpdocs.h"
#include <QWidget>

class GUI_Profile : public QWidget
{
    Q_OBJECT
public:
    GIMPdocs *gimpParent;

    explicit GUI_Profile(QWidget *parent);
    ~GUI_Profile();
    static QString getObjectName() {return QString("GUI_Profile");}

private slots:
    //serve per riempire il form quando sto accedendo alla window per modificare un account già esistente
    void fillForm();
    //questa serve solo a riempire la combobox
    void loadIcons();

    void on_savePushButton_clicked();
    void on_backPushButton_clicked();

private:
    Ui::GUI_Profile *ui;
};



#endif // GUI_PROFILE_H
