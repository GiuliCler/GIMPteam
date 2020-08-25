#include "gui_toolsbar.h"
#include "../../CRDT/crdt_controller.h"
#include <QColorDialog>
#include <QGraphicsOpacityEffect>


GUI_ToolsBar::GUI_ToolsBar(QWidget *parent) : QWidget(parent){
    this->setObjectName(GUI_ToolsBar::getObjectName());
    editorParent = static_cast<GUI_Editor*>(parent);
    ui = new Ui::GUI_ToolsBar();
    ui->setupUi(this);

    // setTextColorIconColor(QColor(0,0,0)); //TODO:capire se è utile

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

    connect(ui->closePushButton, &QPushButton::clicked, editorParent, &GUI_Editor::launchSetUi1);

    fadingLabelSetUp();

    //connect()
}

GUI_ToolsBar::~GUI_ToolsBar(){
    delete ui;
}

void GUI_ToolsBar::on_colorPushButton_clicked(){
    QColor chosenColor = QColorDialog::getColor(); //return the color chosen by user
    editorParent->crdtController->setCurrentTextColor(chosenColor);

    compromisedUndoStack();
}

void GUI_ToolsBar::setFontComboBoxText(QFont font){
    //questa block sygnalserve ad evitare un loop infinito
    ui->fontComboBox->blockSignals(true);
    ui->fontComboBox->setCurrentFont(font);
    ui->fontComboBox->blockSignals(false);
}

void GUI_ToolsBar::setSpinBoxValue(int size){

    //questa block sygnalserve ad evitare un loop infinito
    ui->spinBox->blockSignals(true);
    ui->spinBox->setValue(size);
    ui->spinBox->blockSignals(false);
}

void GUI_ToolsBar::startFadingText(QString text){
    ui->bewareLabel->setText(text);
    fadingLabelAnimation->start();
}


void GUI_ToolsBar::fadingLabelSetUp(){
    QGraphicsOpacityEffect *fadingLabelEffect;
    QLabel *label = ui->bewareLabel;

    fadingLabelEffect = new QGraphicsOpacityEffect();
    fadingLabelEffect->setOpacity(0.0f);
    label->setGraphicsEffect(fadingLabelEffect);
    fadingLabelAnimation = new QPropertyAnimation(fadingLabelEffect, "opacity");
    fadingLabelAnimation->setStartValue(1.0f);
    fadingLabelAnimation->setEndValue(0.0f);

    fadingLabelAnimation->setDuration(4000);
    fadingLabelAnimation->setKeyValueAt(0.75, 1.0f);
}

void GUI_ToolsBar::setTextColorIconColor(const QColor color){
    QPixmap p(16,16);
    p.fill(color);
    const QIcon ic(p);
    ui->colorPushButton->setIcon(ic);
}

void GUI_ToolsBar::compromisedUndoStack(){
    startFadingText("Beware: this operation compromized undo chronology");
}
