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
    void on_copyPushButton_pressed();
    void on_copyPushButton_released();

private:
    std::unique_ptr<Ui::GUI_URI> ui;
};

#endif // GUI_URI_H
