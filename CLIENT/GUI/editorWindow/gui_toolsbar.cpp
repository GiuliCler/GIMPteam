#include "gui_toolsbar.h"
#include "gui_fadinglabel.h"
#include "../../CRDT/crdt_controller.h"

#include <QColorDialog>

GUI_ToolsBar::GUI_ToolsBar(QWidget *parent) : QWidget(parent){
    this->setObjectName(GUI_ToolsBar::getObjectName());
    editorParent = static_cast<GUI_Editor*>(parent);
    ui = new Ui::GUI_ToolsBar();
    ui->setupUi(this);

    fadingLabel = new GUI_FadingLabel(this);
    ui->bewareLabelWidget->layout()->addWidget(fadingLabel);

    connect(ui->undoPushButton, &QPushButton::clicked, editorParent, &GUI_Editor::on_actionUndo);
    connect(ui->redoPushButton, &QPushButton::clicked, editorParent, &GUI_Editor::on_actionRedo);
    connect(ui->cutPushButton, &QPushButton::clicked, editorParent, &GUI_Editor::on_actionCut);
    connect(ui->copyPushButton, &QPushButton::clicked, editorParent, &GUI_Editor::on_actionCopy);
    connect(ui->pastePushButton, &QPushButton::clicked, editorParent, &GUI_Editor::on_actionPaste);
    connect(ui->boldPushButton, &QPushButton::clicked, editorParent, &GUI_Editor::on_actionBold);
    connect(ui->italicPushButton, &QPushButton::clicked, editorParent, &GUI_Editor::on_actionItalic);
    connect(ui->underlinedPushButton, &QPushButton::clicked, editorParent, &GUI_Editor::on_actionUnderlined);
    connect(ui->strikethroughPushButton, &QPushButton::clicked, editorParent, &GUI_Editor::on_actionStrikethrough);
    connect(ui->alignLeftPushButton, &QPushButton::clicked, editorParent, &GUI_Editor::on_actionLeft);
    connect(ui->alignCenterPushButton, &QPushButton::clicked, editorParent, &GUI_Editor::on_actionCenter);
    connect(ui->alignRightPushButton, &QPushButton::clicked, editorParent, &GUI_Editor::on_actionRight);
    connect(ui->alignJustifiedPushButton, &QPushButton::clicked, editorParent, &GUI_Editor::on_actionJustified);

    connect(ui->closePushButton, &QPushButton::clicked, editorParent, &GUI_Editor::closeDocument);

    fadingLabel->fadingLabelSetUp("Beware: this operation has compromized undo chronology", 4000, 0.75f);
}

GUI_ToolsBar::~GUI_ToolsBar(){
    delete ui;
}

void GUI_ToolsBar::on_colorPushButton_clicked(){
    QColor chosenColor = QColorDialog::getColor(); //return the color chosen by user
    editorParent->crdtController->setCurrentTextColor(chosenColor);

    compromisedUndoStack();
}

void GUI_ToolsBar::enterCompromizedModeUndoStack(){
    fadingLabel->setPermanentText("Contributor mode compromizes undo chronology");
}

void GUI_ToolsBar::exitCompromizedModeUndoStack(){
    fadingLabel->removePermanentText();
}



void GUI_ToolsBar::setTextColorIconColor(const QColor color){
    QPixmap p(16,16);
    p.fill(color);
    const QIcon ic(p);
    ui->colorPushButton->setIcon(ic);
}

void GUI_ToolsBar::compromisedUndoStack(){
    fadingLabel->startFadingText("This action compromized undo chronology");
}
