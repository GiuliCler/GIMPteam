#ifndef GUI_TOOLSBAR_H
#define GUI_TOOLSBAR_H

#include "ui_gui_toolsbar.h"
#include "../gimpdocs.h"
#include <QWidget>
#include "gui_editor.h"

class GUI_FadingLabel;

class GUI_ToolsBar : public QWidget
{
    Q_OBJECT
public:
    //deve rimanere pubblic operchè srver per delle connect
    Ui::GUI_ToolsBar *ui;

    explicit GUI_ToolsBar(QWidget *parent);
    ~GUI_ToolsBar();
    inline static QString getObjectName() {return QString("GUI_ToolsBar");}

    void setTextColorIconColor(const QColor color);
    void enterCompromizedModeUndoStack();
    void exitCompromizedModeUndoStack();

private:
    GUI_Editor *editorParent;
    GUI_FadingLabel *fadingLabel;

public slots:
    void on_colorPushButton_clicked();
    void compromisedUndoStack();
};

#endif // GUI_TOOLSBAR_H
