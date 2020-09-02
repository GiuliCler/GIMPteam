#ifndef GUI_NEWDOC_H
#define GUI_NEWDOC_H

#include "ui_gui_newdoc.h"
#include "gimpdocs.h"
#include <QWidget>

class GUI_Newdoc: public QWidget{
    Q_OBJECT

public:
    explicit GUI_Newdoc(QWidget *parent);
    ~GUI_Newdoc();
    static QString getObjectName() {return QString("GUI_Newdoc");}

private slots:
    void on_createPushButton_clicked();
    void on_openURIPushButton_clicked();

private:
    GIMPdocs *gimpParent;
    Ui::GUI_Newdoc *ui;

    bool checkFieldValidity(QString value, QString name);
};

#endif // GUI_NEWDOC_H
