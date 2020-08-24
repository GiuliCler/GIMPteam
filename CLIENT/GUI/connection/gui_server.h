#ifndef GUI_SERVER_H
#define GUI_SERVER_H

#include "../gimpdocs.h"
#include "ui_gui_server.h"
#include <QWidget>

class GUI_Server : public QWidget
{
    Q_OBJECT
public:
    GIMPdocs *gimpParent;

    explicit GUI_Server(QWidget *parent);
    ~GUI_Server();

private slots:
    void on_confirmPushButton_clicked();
    bool checkAddressValidity(QString address);
    bool checkPortValidity(QString port);

private:
    Ui::GUI_Server *ui;
};

#endif // GUI_SERVER_H
