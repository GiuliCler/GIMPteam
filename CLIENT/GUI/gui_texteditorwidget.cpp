#include "gui_texteditorwidget.h"
#include "gimpdocs.h"

GUI_TextEditorWidget::GUI_TextEditorWidget(QWidget *parent) : QWidget(parent)
{
    ui = new Ui::GUI_TextEditorWidget;
    ui->setupUi(this);

    //ui->textEdit->setStyleSheet("background-color: black;");
    ui->textEdit->setCursorWidth(6);
    ui->textEdit->setStyleSheet("QTextEdit{color: #ffff00; background-color: #303030; selection-background-color: #606060; selection-color: #ffffff;}");
    /*QTextCharFormat fmt;
    fmt.setForeground(QBrush(QColor(255,255,0)));
    ui->textEdit->mergeCurrentCharFormat(fmt);*/
}

GUI_TextEditorWidget::~GUI_TextEditorWidget(){
    delete ui;
}

