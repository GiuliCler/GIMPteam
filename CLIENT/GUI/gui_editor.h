#ifndef GUI_EDITOR_H
#define GUI_EDITOR_H

#include <QWidget>
#include "ui_gui_editor.h"

class GUI_Editor : public QWidget
{
    Q_OBJECT
public:
    explicit GUI_Editor(QWidget *parent = nullptr);
    ~GUI_Editor();
private slots:

    void on_menuPushButton_clicked();

private:
    Ui::GUI_Editor *ui;
};

#endif // GUI_EDITOR_H
