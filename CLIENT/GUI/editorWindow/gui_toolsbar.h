#ifndef GUI_TOOLSBAR_H
#define GUI_TOOLSBAR_H

#include "ui_gui_toolsbar.h"
#include "../gimpdocs.h"
#include <QWidget>
#include "gui_editor.h"

class GUI_ToolsBar : public QWidget
{
    Q_OBJECT
public:
    GUI_Editor *editorParent;
    Ui::GUI_ToolsBar *ui;

    explicit GUI_ToolsBar(QWidget *parent);
    ~GUI_ToolsBar();

private slots:
    void on_colorPushButton_clicked();

private:


    void setTextColorIconColor(const QColor color);
};

#endif // GUI_TOOLSBAR_H
