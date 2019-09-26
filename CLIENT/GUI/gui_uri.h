#ifndef GUI_URI_H
#define GUI_URI_H

#include <QDialog>
#include "gimpdocs.h"
#include "ui_gui_uri.h"

class GUI_URI : public QDialog
{
    Q_OBJECT
public:
    explicit GUI_URI(QWidget *parent, QString uri);
    ~GUI_URI();

private:
    Ui::GUI_URI *ui;
};

#endif // GUI_URI_H
