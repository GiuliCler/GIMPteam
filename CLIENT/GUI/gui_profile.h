#ifndef GUI_PROFILE_H
#define GUI_PROFILE_H

#include "ui_gui_profile.h"
#include "gimpdocs.h"
#include <QWidget>

class GUI_Profile : public QWidget
{
    Q_OBJECT
public:
    explicit GUI_Profile(QWidget *parent);
    inline static QString getObjectName() {return QString("GUI_Profile");}

private slots:
    void on_savePushButton_clicked();
    void on_backPushButton_clicked();

private:
    GIMPdocs *gimpParent;
    std::unique_ptr<Ui::GUI_Profile> ui;

    void fillForm();
    //questa serve solo a riempire la combobox
    void loadIcons();
    bool checkFieldValidity(QString value, QString name);
    bool checkPasswordSecurity(QString password, QString repeatPassword);
};



#endif // GUI_PROFILE_H
