#include "gui_toolsbar.h"
#include "gui_fadinglabel.h"
#include "../../CRDT/crdt_controller.h"

#include <QColorDialog>

GUI_ToolsBar::GUI_ToolsBar(QWidget *parent) : QWidget(parent){
    this->setObjectName(GUI_ToolsBar::getObjectName());
    editorParent = static_cast<GUI_Editor*>(parent);
    ui.reset(new Ui::GUI_ToolsBar());
    ui->setupUi(this);

    fadingLabel = new GUI_FadingLabel(this);
    ui->bewareLabelWidget->layout()->addWidget(fadingLabel);

    addEventFilter();

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

void GUI_ToolsBar::on_colorPushButton_clicked(){
    QColor chosenColor = QColorDialog::getColor(); //return the color chosen by user

    editorParent->gimpParent->setCursor(Qt::WaitCursor);

    //serve ad attivare il filtro per impedire che l'utente prema pulsanti a raffica
    GUI_SetFilterStatus *event1 = new GUI_SetFilterStatus(true);
    qApp->sendEvent(ui->colorPushButton, event1);

    editorParent->crdtController->setCurrentTextColor(chosenColor);

    editorParent->gimpParent->setCursor(Qt::ArrowCursor);
    //serve a forzare l'eseguzione del mousePressedEvent e a filtrarlo colla eventFilter
    qApp->processEvents();

    GUI_SetFilterStatus *event2 = new GUI_SetFilterStatus(false);
    qApp->postEvent(ui->colorPushButton, event2);
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


/*******private***********/

void GUI_ToolsBar::addEventFilter(){

    /* aggiungo un event filter a tutti i pulsanti (tranne exit) perchè voglio impedire che quando
     * l'utente è in attesa per un'operazione pesante non si metta a pigiare tasti creando una lunga coda di eventi.
     * Per quanto riguarda i comandi da menù non dovrebbe esserci problema: se l'editor è bloccato i menù  tendina non si aprono
     * (poi volendo può andare alla cieca e riuscirci lo stesso)*/

    ui->undoPushButton->installEventFilter(editorParent->childEventFilter);
    ui->redoPushButton->installEventFilter(editorParent->childEventFilter);
    ui->cutPushButton->installEventFilter(editorParent->childEventFilter);
    ui->copyPushButton->installEventFilter(editorParent->childEventFilter);
    ui->pastePushButton->installEventFilter(editorParent->childEventFilter);
    ui->boldPushButton->installEventFilter(editorParent->childEventFilter);
    ui->italicPushButton->installEventFilter(editorParent->childEventFilter);
    ui->underlinedPushButton->installEventFilter(editorParent->childEventFilter);
    ui->strikethroughPushButton->installEventFilter(editorParent->childEventFilter);
    ui->alignLeftPushButton->installEventFilter(editorParent->childEventFilter);
    ui->alignCenterPushButton->installEventFilter(editorParent->childEventFilter);
    ui->alignRightPushButton->installEventFilter(editorParent->childEventFilter);
    ui->alignJustifiedPushButton->installEventFilter(editorParent->childEventFilter);
    ui->fontComboBox->installEventFilter(editorParent->childEventFilter);
    ui->spinBox->installEventFilter(editorParent->childEventFilter);
    ui->colorPushButton->installEventFilter(editorParent->childEventFilter);

}

