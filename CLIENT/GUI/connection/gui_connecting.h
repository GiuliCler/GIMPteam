#ifndef GUI_CONNECTING_H
#define GUI_CONNECTING_H

//#include "../gimpdocs.h"
#include "ui_gui_connecting.h"
#include <QDialog>

class GUI_Connecting : public QDialog
{
    Q_OBJECT
public:

    //ne chiamo il costruttore (e subito dopo il distruttore) da qui perchè vorrei fargli lanciare la close() dal costruttore ma non posso
    static void GUI_ConnectingWrapper(QWidget *parent);

    ~GUI_Connecting();

private slots:

private:
    explicit GUI_Connecting(QWidget *parent);
    Ui::GUI_Connecting *ui;
};

#endif // GUI_CONNECTING_H
