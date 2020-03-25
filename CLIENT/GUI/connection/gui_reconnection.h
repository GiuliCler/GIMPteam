#ifndef GUI_RECONNECTION_H
#define GUI_RECONNECTION_H

#include "../gimpdocs.h"
#include "ui_gui_reconnection.h"
#include <QDialog>

class GUI_Reconnection : public QDialog
{
    Q_OBJECT
public:
    explicit GUI_Reconnection(QWidget *parent);
    ~GUI_Reconnection();

private slots:


    void on_exitPushButton_clicked();

    void on_retryPushButton_clicked();

private:
    Ui::GUI_Reconnection *ui;
};

#endif // GUI_RECONNECTION_H
