#ifndef GUI_FORGETDOC_H
#define GUI_FORGETDOC_H

#include <QWidget>
#include "gimpdocs.h"
#include "ui_gui_forgetdoc.h"

class GUI_Forgetdoc : public QWidget
{
    Q_OBJECT
public:
    GIMPdocs *gimpParent;

    explicit GUI_Forgetdoc(QWidget *parent = nullptr);
    ~GUI_Forgetdoc();
    static QString getObjectName() {return QString("GUI_Forgetdoc");}

private slots:
    void on_forgetPushButton_clicked();

private:
    Ui::GUI_ForgetDoc *ui;

    void fillList();
};

#endif // GUI_FORGETDOC_H
