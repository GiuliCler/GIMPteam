#ifndef GUI_RECONNECTION_H
#define GUI_RECONNECTION_H

#include "ui_gui_reconnection.h"
#include <QDialog>
#include <memory>

class GIMPdocs;

class GUI_Reconnection : public QDialog
{
    Q_OBJECT

public:
    enum Reconnection_Results {Success, Failure, KillApplication};

    static void GUI_ReconnectionWrapper(QWidget *parent);

private slots:
    void on_exitPushButton_clicked();
    void on_retryPushButton_clicked();

private:
    std::unique_ptr<Ui::GUI_Reconnection> ui;
    explicit GUI_Reconnection(QWidget *parent);

};

#endif // GUI_RECONNECTION_H
