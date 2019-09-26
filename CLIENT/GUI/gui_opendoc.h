#ifndef GUI_OPENDOC_H
#define GUI_OPENDOC_H

#include <QWidget>
#include "ui_gui_opendoc.h"
#include "gimpdocs.h"

class GUI_Opendoc: public QWidget{
    Q_OBJECT
public:
    GIMPdocs *gimpParent;

    explicit GUI_Opendoc(QWidget *parent);
    ~GUI_Opendoc();
    static QString getObjectName() {return QString("GUI_Opendoc");}

private slots:
    void on_openDocsPushButton_clicked();
    void on_openURIPushButton_clicked();


    void on_getURIPushButton_clicked();

private:
    Ui::GUI_Opendoc *ui;

    void fillList();
};

#endif // GUI_OPENDOC_H
