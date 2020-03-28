#include "gui_usersbar.h"
#include "gui_editor.h"
#include "gui_myscrollarea.h"
#include <QPainter>
#include <QScrollBar>
//debug purpose
#include <QRandomGenerator>

GUI_UsersBar::GUI_UsersBar(QWidget *parent) : QWidget(parent){
    this->setObjectName(GUI_UsersBar::getObjectName());
    editorParent = static_cast<GUI_Editor*>(parent);
    ui = new Ui::GUI_UsersBar();
    ui->setupUi(this);

    GUI_MyScrollArea *onlineIconsScrollArea = new GUI_MyScrollArea(ui->onlineIgnoredWrapper);
    onlineIconsScrollArea->setObjectName(getOnlineAreaName());
    ui->onlineIgnoredWrapper->layout()->addWidget(onlineIconsScrollArea);

    ui->hideColorsPushButton->hide();
    ui->contributorUsersWidget->hide();

    GUI_MyScrollArea *contributorIconsScrollArea = new GUI_MyScrollArea(ui->contributorsIgnoredWrapper);
    contributorIconsScrollArea->setObjectName(getContributorsAreaName());
    ui->contributorsIgnoredWrapper->layout()->addWidget(contributorIconsScrollArea);
    //static_cast<QVBoxLayout*>(ui->contributorUsersWidget->layout())->insertWidget(2, contributorIconsScrollArea);

    //connetto le signals dei pulsanti per fare alternare i pulsanti nella menù bar
    connect(ui->showColorsPushButton, &QPushButton::clicked, this->editorParent, &GUI_Editor::on_actionApplyUsersColors);
    connect(ui->hideColorsPushButton, &QPushButton::clicked, this->editorParent, &GUI_Editor::on_actionApplyTextColors);
}

GUI_UsersBar::~GUI_UsersBar(){
    delete ui;
}

QLabel *GUI_UsersBar::getUserIcon(int userId, QColor color){
    //carico l'icona e le metto uno sfondo
    QString iconId;
    QString result = GUI_ConnectionToServerWrapper::requestIconIdWrapper(editorParent->gimpParent, userId);
    if(result.compare("errore") == 0)
        //non dovremmo mai entrare in questo if perchè in caso di errore di connessione si dovrebbe ricaricare il widget da capo
        return new QLabel;
    else
        iconId = result;

    QPixmap *image = new QPixmap(GUI_Icons::getIconPath(iconId));
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
    QString tooltip;
    result = GUI_ConnectionToServerWrapper::requestGetNicknameWrapper(editorParent->gimpParent, userId);
    if(result.compare("errore") == 0)
        //non dovremmo mai entrare in questo if perchè in caso di errore di connessione si dovrebbe ricaricare il widget da capo
        return new QLabel;
    else
        iconId = result;
    label->setToolTip(tooltip);

    return label;
}

void GUI_UsersBar::addOnlineUserIcon(int userId, QColor color){
    //questo non dovrebbe succedere, ma non si sa mai
    if(onlineUsersIconMap.find(userId) != onlineUsersIconMap.end())
        return;

    QLabel *iconLabel = getUserIcon(userId, color);
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

void GUI_UsersBar::addContributorUserIcon(int userId, QColor color){
    //questo non dovrebbe succedere, ma non si sa mai
    if(contributorUsersIconMap.find(userId) != contributorUsersIconMap.end())
        return;

    QLabel *iconLabel = getUserIcon(userId, color);
    contributorUsersIconMap.insert(userId, iconLabel);
    ui->numberContributorUsersLabel->setNum(contributorUsersIconMap.size());
    this->findChild<GUI_MyScrollArea*>(getContributorsAreaName())->widget()->layout()->addWidget(iconLabel);

    if(contributorUsersIconMap.size() <= GUI_MyScrollArea::getMaxUsersIconsNumber()+1)
        this->findChild<GUI_MyScrollArea*>(getContributorsAreaName())->updateSize(contributorUsersIconMap.size());
}

void GUI_UsersBar::removeContributorUserIcon(int userId){
    if(this->contributorUsersIconMap.find(userId) == contributorUsersIconMap.end())
        return;

    contributorUsersIconMap[userId]->close();
    contributorUsersIconMap.remove(userId);
    ui->numberContributorUsersLabel->setNum(contributorUsersIconMap.size());

    if(contributorUsersIconMap.size() <= GUI_MyScrollArea::getMaxUsersIconsNumber()+1)
        this->findChild<GUI_MyScrollArea*>(getContributorsAreaName())->updateSize(contributorUsersIconMap.size());
}

bool GUI_UsersBar::isOnline(int userId){
    return onlineUsersIconMap.find(userId) != onlineUsersIconMap.end();
}

bool GUI_UsersBar::isContributor(int userId){
    return contributorUsersIconMap.find(userId) != contributorUsersIconMap.end();
}

/******************SLOTS**************************************/

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

/**********************************DEBUG**********************************/

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
