#include "gui_toolsbar.h"
#include <QColorDialog>

GUI_ToolsBar::GUI_ToolsBar(QWidget *parent) : QWidget(parent){
    editorParent = static_cast<GUI_Editor*>(parent);
    ui = new Ui::GUI_ToolsBar();
    ui->setupUi(this);

    setTextColorIconColor(Stub::getCurrentTextColor());

    connect(ui->boldPushButton, &QPushButton::clicked, editorParent, &GUI_Editor::on_actionBold);
    connect(ui->italicPushButton, &QPushButton::clicked, editorParent, &GUI_Editor::on_actionItalic);
    connect(ui->underlinedPushButton, &QPushButton::clicked, editorParent, &GUI_Editor::on_actionUnderlined);
    connect(ui->strikethroughPushButton, &QPushButton::clicked, editorParent, &GUI_Editor::on_actionStrikethrough);
    connect(ui->alignLeftPushButton, &QPushButton::clicked, editorParent, &GUI_Editor::on_actionLeft);
    connect(ui->alignCenterPushButton, &QPushButton::clicked, editorParent, &GUI_Editor::on_actionCenter);
    connect(ui->alignRightPushButton, &QPushButton::clicked, editorParent, &GUI_Editor::on_actionRight);
    connect(ui->alignJustifiedPushButton, &QPushButton::clicked, editorParent, &GUI_Editor::on_actionJustified);

    connect(ui->closePushButton, &QPushButton::clicked, editorParent, &GUI_Editor::launchSetUi1);
}

GUI_ToolsBar::~GUI_ToolsBar(){
    delete ui;
}

void GUI_ToolsBar::on_colorPushButton_clicked(){
    QColor chosenColor = QColorDialog::getColor(); //return the color chosen by user
    setTextColorIconColor(chosenColor);

    Stub::setCurrentTextColor(chosenColor);
}

void GUI_ToolsBar::setTextColorIconColor(const QColor color){
    QPixmap p(16,16);
    p.fill(color);
    const QIcon ic(p);
    ui->colorPushButton->setIcon(ic);
}
