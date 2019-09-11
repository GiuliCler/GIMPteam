#ifndef GUI_OPENDOC_H
#define GUI_OPENDOC_H

#include <QWidget>
#include "ui_gui_opendoc.h"

class GUI_Opendoc: public QWidget{
    Q_OBJECT
public:
    explicit GUI_Opendoc(QWidget *parent);
    ~GUI_Opendoc();

private slots:


private:
    Ui::GUI_Opendoc *ui;
};

#endif // GUI_OPENDOC_H
