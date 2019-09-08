#ifndef GUI_OPENDOC_H
#define GUI_OPENDOC_H

#include <QWidget>
#include "ui_gui_opendoc.h"

class GUI_Opendoc: public QWidget{
    Q_OBJECT
public:
    explicit GUI_Opendoc(QWidget *parent = nullptr);

private slots:
    void on_pushButton_clicked();

private:
    Ui::GUI_Opendoc *ui;
};

#endif // GUI_OPENDOC_H
