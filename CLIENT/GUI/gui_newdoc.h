#ifndef GUI_NEWDOC_H
#define GUI_NEWDOC_H

#include <QWidget>
#include "ui_gui_newdoc.h"
#include "gimpdocs.h"

class GUI_Newdoc: public QWidget{
    Q_OBJECT
public:
    GIMPdocs *gimpParent;

    explicit GUI_Newdoc(QWidget *parent);
    ~GUI_Newdoc();
    static QString getObjectName() {return QString("GUI_Newdoc");}

private slots:
    void on_createPushButton_clicked();

private:
    Ui::GUI_Newdoc *ui;
};

#endif // GUI_NEWDOC_H
