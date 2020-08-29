#ifndef GUI_RECONNECTION_H
#define GUI_RECONNECTION_H

//#include "../gimpdocs.h"
#include "ui_gui_reconnection.h"
#include <QDialog>
class GIMPdocs;

class GUI_Reconnection : public QDialog
{
    Q_OBJECT

    enum Reconnection_Results {Success, Failure};
    //typedef Reconnection_Results Reconnection_Results;

public:
    static void GUI_ReconnectionWrapper(QWidget *parent);

    ~GUI_Reconnection();

private slots:

    void on_exitPushButton_clicked();
    Reconnection_Results on_retryPushButton_clicked();

public:
    Ui::GUI_Reconnection *ui;
    explicit GUI_Reconnection(QWidget *parent);

};

#endif // GUI_RECONNECTION_H
