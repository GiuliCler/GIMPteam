#ifndef GUI_TEXTEDITORWIDGET_H
#define GUI_TEXTEDITORWIDGET_H

#include <QWidget>
#include "ui_gui_texteditorwidget.h"


class GUI_TextEditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GUI_TextEditorWidget(QWidget *parent = nullptr);
    ~GUI_TextEditorWidget();

private:
    Ui::GUI_TextEditorWidget *ui;
};

#endif // GUI_TEXTEDITORWIDGET_H

