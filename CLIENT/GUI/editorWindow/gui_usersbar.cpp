#include "gui_usersbar.h"
#include "gui_editor.h"
#include "gui_myscrollarea.h"
#include <QPainter>
#include <QScrollArea>
#include <QAbstractScrollArea>
#include <QPushButton>
#include <QScrollBar>
#include <QRandomGenerator>

GUI_UsersBar::GUI_UsersBar(QWidget *parent) : QWidget(parent){
    this->setObjectName(GUI_UsersBar::getObjectName());
    editorParent = static_cast<GUI_Editor*>(parent);

    ui = new Ui::GUI_UsersBar();
    ui->setupUi(this);

    //carico gli users già online e l'elenco dei contributors
    GUI_MyScrollArea *onlineIconsScrollArea = new GUI_MyScrollArea(this);
    onlineIconsScrollArea->setObjectName(getOnlineAreaName());
    static_cast<QVBoxLayout*>(ui->onlineUsersWidget->layout())->insertWidget(2, onlineIconsScrollArea);

    ui->hideColorsPushButton->hide();
    ui->contributorUsersWidget->hide();

    GUI_MyScrollArea *contributorIconsScrollArea = new GUI_MyScrollArea(this);
    contributorIconsScrollArea->setObjectName(getContributorsAreaName());
    static_cast<QVBoxLayout*>(ui->contributorUsersWidget->layout())->insertWidget(2, contributorIconsScrollArea);

    //connetto le signals dei pulsanti per fare alternare i pulsanti nella menù bar
    connect(ui->showColorsPushButton, &QPushButton::clicked, this->editorParent, &GUI_Editor::on_actionApplyUsersColors);
    connect(ui->hideColorsPushButton, &QPushButton::clicked, this->editorParent, &GUI_Editor::on_actionApplyTextColors);

}

GUI_UsersBar::~GUI_UsersBar(){
    delete ui;
}

QLabel *GUI_UsersBar::getUserIcon(long userId, QColor color){
    //carico l'icona e le metto uno sfondo
    long iconId = Stub::getIconId(userId);
    QPixmap *image = new QPixmap(GUI_Icons::getIconPath(iconId));
    QPixmap *background = new QPixmap(image->height(), image->width());
    background->fill(color);
    QPainter painter(background);
    const QRect rect(image->rect());
    painter.drawPixmap(rect, *image);

    QLabel *label = new QLabel(this);

    label->setPixmap(*background);
    label->setScaledContents(true);
    label->setProperty("background-color", "#e1e1e1");
    label->setMaximumSize(GUI_Icons::iconSize,GUI_Icons::iconSize);
    label->setMinimumSize(GUI_Icons::iconSize,GUI_Icons::iconSize);
    label->setToolTip(Stub::getNickname(userId));

    return label;
}

void GUI_UsersBar::addOnlineUserIcon(long userId, QColor color){
    /*if(this->onlineUsersIconMap.find(userId) != onlineUsersIconMap.end())
        return;*/

    QLabel *iconLabel = getUserIcon(userId, color);
    onlineUsersIconMap.insert(userId, iconLabel);
    ui->numberOnlineUsersLabel->setNum(onlineUsersIconMap.size());

    this->findChild<GUI_MyScrollArea*>(getOnlineAreaName())->widget()->layout()->addWidget(iconLabel);
    /*faccio l'update sia se devo allargare e stringere la size, sia se devo modificare i margini per aggiungere la scrollbar. Per questo ho messo il +1
     * Poi potrei anche lancirlo sempre per comodità, tanto i controlli interni ci sono, ma è uno spreco di operzioni inutili
     */
    if(onlineUsersIconMap.size() <= GUI_MyScrollArea::getMaxUsersIconsNumber()+1)
        this->findChild<GUI_MyScrollArea*>(getOnlineAreaName())->updateSize(onlineUsersIconMap.size());
}

void GUI_UsersBar::removeOnlineUserIcon(long userId){
    if(this->onlineUsersIconMap.find(userId) == onlineUsersIconMap.end())
        return;

    onlineUsersIconMap[userId]->close();
    onlineUsersIconMap.remove(userId);
    ui->numberOnlineUsersLabel->setNum(onlineUsersIconMap.size());
    /*faccio l'update sia se devo allargare e stringere la size, sia se devo modificare i margini per aggiungere la scrollbar. Per questo ho messo il +1
     * Poi potrei anche lancirlo sempre per comodità, tanto i controlli interni ci sono, ma è uno spreco di operzioni inutili
     */
    if(onlineUsersIconMap.size() <= GUI_MyScrollArea::getMaxUsersIconsNumber()+1)
        this->findChild<GUI_MyScrollArea*>(getOnlineAreaName())->updateSize(onlineUsersIconMap.size());
}

void GUI_UsersBar::addContributorUserIcon(long userId, QColor color){
    //nota il CLIENT può essere un contributor

    QLabel *iconLabel = getUserIcon(userId, color);
    contributorUsersIconMap.insert(userId, iconLabel);
    ui->numberContributorUsersLabel->setNum(contributorUsersIconMap.size());

    this->findChild<GUI_MyScrollArea*>(getContributorsAreaName())->widget()->layout()->addWidget(iconLabel);
    /*faccio l'update sia se devo allargare e stringere la size, sia se devo modificare i margini per aggiungere la scrollbar. Per questo ho messo il +1
     * Poi potrei anche lancirlo sempre per comodità, tanto i controlli interni ci sono, ma è uno spreco di operzioni inutili
     */
    if(contributorUsersIconMap.size() <= GUI_MyScrollArea::getMaxUsersIconsNumber()+1)
        this->findChild<GUI_MyScrollArea*>(getContributorsAreaName())->updateSize(contributorUsersIconMap.size());
}

void GUI_UsersBar::removeContributorUserIcon(long userId){
    if(this->contributorUsersIconMap.find(userId) == contributorUsersIconMap.end())
        return;

    contributorUsersIconMap[userId]->close();
    contributorUsersIconMap.remove(userId);
    ui->numberContributorUsersLabel->setNum(contributorUsersIconMap.size());
    /*faccio l'update sia se devo allargare e stringere la size, sia se devo modificare i margini per aggiungere la scrollbar. Per questo ho messo il +1
     * Poi potrei anche lancirlo sempre per comodità, tanto i controlli interni ci sono, ma è uno spreco di operzioni inutili
     */
    if(contributorUsersIconMap.size() <= GUI_MyScrollArea::getMaxUsersIconsNumber()+1)
        this->findChild<GUI_MyScrollArea*>(getContributorsAreaName())->updateSize(contributorUsersIconMap.size());
}

void GUI_UsersBar::on_showColorsPushButton_clicked(){
    editorParent->usersColors = true;

    ui->hideColorsPushButton->show();
    ui->contributorUsersWidget->show();
    ui->showColorsPushButton->hide();
}

void GUI_UsersBar::on_hideColorsPushButton_clicked(){
    editorParent->usersColors = false;

    ui->showColorsPushButton->show();
    ui->contributorUsersWidget->hide();
    ui->hideColorsPushButton->hide();
}

//serve solo per il debug
void GUI_UsersBar::on_pushButton_clicked()
{
    editorParent->addUserToEditorGUI(QRandomGenerator::global()->bounded(2000));
}

void GUI_UsersBar::on_pushButton_2_clicked()
{
    editorParent->removeUserFromEditorGUI(onlineUsersIconMap.keys().first());
}

void GUI_UsersBar::on_pushButton_3_clicked()
{
    editorParent->addContributorToCurrentDocument(QRandomGenerator::global()->bounded(2000));
}

void GUI_UsersBar::on_pushButton_4_clicked(){
    editorParent->removeContributorFromCurrentDocument(contributorUsersIconMap.keys().first());
}
