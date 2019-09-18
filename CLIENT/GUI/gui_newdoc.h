#ifndef GUI_NEWDOC_H
#define GUI_NEWDOC_H

#include <QWidget>
#include "ui_gui_newdoc.h"

class GUI_Newdoc: public QWidget{
    Q_OBJECT
public:
    explicit GUI_Newdoc(QWidget *parent);
    ~GUI_Newdoc();
    static QString getObjectName() {return QString("GUI_Newdoc");}

private slots:
    void on_createPushButton_clicked();

private:
    Ui::GUI_Newdoc *ui;
    //me lo salvo qui perchè il normale pointer al padre viene modificato
    QWidget *gimpParent;
};

#endif // GUI_NEWDOC_H
