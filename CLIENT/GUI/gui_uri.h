#ifndef GUI_URI_H
#define GUI_URI_H

#include "gimpdocs.h"
#include "ui_gui_uri.h"
#include <QDialog>

class GUI_URI : public QDialog
{
    Q_OBJECT
public:
    explicit GUI_URI(QWidget *parent, QString uri);
    ~GUI_URI();

private slots:
    void on_copyPushButton_clicked();

private:
    Ui::GUI_URI *ui;
};

#endif // GUI_URI_H
