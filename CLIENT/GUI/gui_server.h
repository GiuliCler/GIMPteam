#ifndef GUI_SERVER_H
#define GUI_SERVER_H

#include "gimpdocs.h"
#include "ui_gui_server.h"
#include <QDialog>

class GUI_Server : public QDialog
{
    Q_OBJECT
public:

    explicit GUI_Server(QWidget *parent);
    ~GUI_Server();

    connection_to_server *connection;

private slots:


    void on_connectPushButton_clicked();

private:
    Ui::GUI_Server *ui;
};

#endif // GUI_SERVER_H
