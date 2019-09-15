#include "gui_texteditorwidget.h"
#include "gimpdocs.h"

GUI_TextEditorWidget::GUI_TextEditorWidget(QWidget *parent) : QWidget(parent)
{
    ui = new Ui::GUI_TextEditorWidget;
    ui->setupUi(this);
}

GUI_TextEditorWidget::~GUI_TextEditorWidget(){
    delete ui;
}

