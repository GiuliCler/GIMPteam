#ifndef GUI_NEWDOC_H
#define GUI_NEWDOC_H

#include <QWidget>
#include "ui_gui_newdoc.h"

class GUI_Newdoc: public QWidget{
    Q_OBJECT
public:
    explicit GUI_Newdoc(QWidget *parent);

private slots:
    void on_pushButton_clicked();

private:
    Ui::GUI_Newdoc *ui;
};

#endif // GUI_NEWDOC_H
