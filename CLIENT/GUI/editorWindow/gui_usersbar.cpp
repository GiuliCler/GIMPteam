#include "gui_usersbar.h"
#include "gui_editor.h"
#include "gui_myscrollarea.h"
#include "../../CRDT/crdt_controller.h"

#include <QPainter>

GUI_UsersBar::GUI_UsersBar(QWidget *parent) : QWidget(parent){
    this->setObjectName(GUI_UsersBar::getObjectName());
    editorParent = static_cast<GUI_Editor*>(parent);
    ui.reset(new Ui::GUI_UsersBar());
    ui->setupUi(this);

    ui->hideColorsPushButton->hide();
    ui->contributorUsersWidget->hide();

    GUI_MyScrollArea *onlineIconsScrollArea = new GUI_MyScrollArea(ui->onlineIgnoredWrapper);
    onlineIconsScrollArea->setObjectName(getOnlineAreaName());
    ui->onlineIgnoredWrapper->layout()->addWidget(onlineIconsScrollArea);

    GUI_MyScrollArea *contributorIconsScrollArea = new GUI_MyScrollArea(ui->contributorsIgnoredWrapper);
    contributorIconsScrollArea->setObjectName(getContributorsAreaName());
    ui->contributorsIgnoredWrapper->layout()->addWidget(contributorIconsScrollArea);

    ui->showColorsPushButton->installEventFilter(editorParent->childEventFilter);
    ui->hideColorsPushButton->installEventFilter(editorParent->childEventFilter);

    //connetto le signals dei pulsanti per fare alternare i pulsanti nella menù bar
    connect(ui->showColorsPushButton, &QPushButton::clicked, this->editorParent, &GUI_Editor::on_actionApplyUsersColors);
    connect(ui->hideColorsPushButton, &QPushButton::clicked, this->editorParent, &GUI_Editor::on_actionApplyTextColors);
}

QLabel *GUI_UsersBar::getUserIcon(QColor color, QString nickname, QString iconId){
    //carico l'icona e le metto uno sfondo
    QString iconPath = GUI_Icons::getIconPath(iconId);
    if(iconPath.compare("") == 0)
        //non dovrebbe mai succedere, a meno che il server non elimini delle icone senza avvisare gli user che avevano scelto quell'icona
        return nullptr;

    QPixmap *image = new QPixmap(iconPath);
    QPixmap *background = new QPixmap(image->height(), image->width());
    background->fill(color);
    QPainter painter(background);
    const QRect rect(image->rect());
    //disegno la pixmap sopra il background
    painter.drawPixmap(rect, *image);

    QLabel *label = new QLabel(this);

    label->setPixmap(*background);
    label->setScaledContents(true);
    label->setMaximumSize(GUI_Icons::iconSize,GUI_Icons::iconSize);
    label->setMinimumSize(GUI_Icons::iconSize,GUI_Icons::iconSize);
    label->setToolTip(nickname);

    return label;
}

void GUI_UsersBar::addOnlineUserIcon(int userId, QColor color, QString nickname, QString iconId){
    //questo non dovrebbe succedere, ma non si sa mai
    if(onlineUsersIconMap.find(userId) != onlineUsersIconMap.end())
        return;

    QLabel *iconLabel = getUserIcon(color, nickname, iconId);
    if(iconLabel == nullptr)
        return;
    onlineUsersIconMap.insert(userId, iconLabel);
    ui->numberOnlineUsersLabel->setNum(onlineUsersIconMap.size());
    this->findChild<GUI_MyScrollArea*>(getOnlineAreaName())->widget()->layout()->addWidget(iconLabel);

    /*faccio l'update sia se devo allargare la size, sia se devo modificare i margini per aggiungere la scrollbar. Per questo ho messo il +1
     * Poi potrei anche lanciarlo sempre per comodità, tanto i controlli interni ci sono, ma è uno spreco di operzioni evitabile
     */
    if(onlineUsersIconMap.size() <= GUI_MyScrollArea::getMaxUsersIconsNumber()+1)
        this->findChild<GUI_MyScrollArea*>(getOnlineAreaName())->updateSize(onlineUsersIconMap.size());
}

void GUI_UsersBar::removeOnlineUserIcon(int userId){
    if(this->onlineUsersIconMap.find(userId) == onlineUsersIconMap.end())
        return;

    onlineUsersIconMap[userId]->close();
    onlineUsersIconMap.remove(userId);
    ui->numberOnlineUsersLabel->setNum(onlineUsersIconMap.size());
    /*faccio l'update sia se devo stringere la size, sia se devo modificare i margini per togliere la scrollbar. Per questo ho messo il +1
     * Poi potrei anche lanciarlo sempre per comodità, tanto i controlli interni ci sono, ma è uno spreco di operzioni inutili
     */
    if(onlineUsersIconMap.size() <= GUI_MyScrollArea::getMaxUsersIconsNumber()+1)
        this->findChild<GUI_MyScrollArea*>(getOnlineAreaName())->updateSize(onlineUsersIconMap.size());
}

void GUI_UsersBar::addContributorUserIcon(int userId, QColor color, QString nickname, QString iconId){
    //questo non dovrebbe succedere, ma non si sa mai
    if(contributorUsersIconMap.find(userId) != contributorUsersIconMap.end())
        return;

    QLabel *iconLabel = getUserIcon(color, nickname, iconId);
    if(iconLabel == nullptr)
        return;
    contributorUsersIconMap.insert(userId, iconLabel);
    ui->numberContributorUsersLabel->setNum(contributorUsersIconMap.size());
    this->findChild<GUI_MyScrollArea*>(getContributorsAreaName())->widget()->layout()->addWidget(iconLabel);

    if(contributorUsersIconMap.size() <= GUI_MyScrollArea::getMaxUsersIconsNumber()+1)
        this->findChild<GUI_MyScrollArea*>(getContributorsAreaName())->updateSize(contributorUsersIconMap.size());
}



/******************SLOTS**************************************/

void GUI_UsersBar::on_showColorsPushButton_clicked(){
    editorParent->usersColors = true;

    //l'"enabled" ha solo funzione grafica in questo contesto
    ui->showColorsPushButton->setEnabled(false);
    ui->showColorsPushButton->repaint();
    editorParent->gimpParent->setCursor(Qt::WaitCursor);

    //serve ad attivare il filtro per impedire che l'utente prema pulsanti a raffica
    GUI_SetFilterStatus *event1 = new GUI_SetFilterStatus(true);
    qApp->sendEvent(ui->showColorsPushButton, event1);

    editorParent->crdtController->setUsersColors(true);

    ui->showColorsPushButton->setEnabled(true);
    editorParent->gimpParent->setCursor(Qt::ArrowCursor);
    editorParent->childMyTextEdit->setFocus();

    ui->hideColorsPushButton->show();
    ui->contributorUsersWidget->show();
    ui->showColorsPushButton->hide();

    //serve a forzare l'eseguzione del mousePressedEvent e a filtrarlo colla eventFilter
    qApp->processEvents();

    GUI_SetFilterStatus *event2 = new GUI_SetFilterStatus(false);
    qApp->postEvent(ui->showColorsPushButton, event2);
}

void GUI_UsersBar::on_hideColorsPushButton_clicked(){
    editorParent->usersColors = false;

    ui->hideColorsPushButton->setEnabled(false);
    ui->hideColorsPushButton->repaint();
    editorParent->gimpParent->setCursor(Qt::WaitCursor);

    GUI_SetFilterStatus *event1 = new GUI_SetFilterStatus(true);
    qApp->sendEvent(ui->hideColorsPushButton, event1);

    editorParent->crdtController->setUsersColors(false);

    ui->hideColorsPushButton->setEnabled(true);
    editorParent->gimpParent->setCursor(Qt::ArrowCursor);
    editorParent->childMyTextEdit->setFocus();

    ui->showColorsPushButton->show();
    ui->contributorUsersWidget->hide();
    ui->hideColorsPushButton->hide();

    qApp->processEvents();
    GUI_SetFilterStatus *event2 = new GUI_SetFilterStatus(false);
    qApp->postEvent(ui->hideColorsPushButton, event2);
}
