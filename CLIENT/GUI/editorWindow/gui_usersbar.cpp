#include "gui_usersbar.h"
#include "gui_editor.h"
#include "gui_myscrollarea.h"
#include <QPainter>
#include <QScrollArea>
#include <QAbstractScrollArea>
#include <QPushButton>
#include <QScrollBar>



GUI_UsersBar::GUI_UsersBar(QWidget *parent) : QWidget(parent){
    this->setObjectName(GUI_UsersBar::getObjectName());
    editorParent = static_cast<GUI_Editor*>(parent);
    ui = new Ui::GUI_UsersBar();
    ui->setupUi(this);

    GUI_MyScrollArea *onlineIconsScrollArea = new GUI_MyScrollArea(this);
    onlineIconsScrollArea->setObjectName(getOnlineAreaName());
    static_cast<QVBoxLayout*>(this->layout())->insertWidget(2, onlineIconsScrollArea);

    //TODO: anche coi contributors, per i quali ti serve uno Stub
    /*GUI_MyScrollArea *onlineIconsScrollArea = new GUI_MyScrollArea(this);
    onlineIconsScrollArea->setObjectName(getOnlineAreaName());
    static_cast<QVBoxLayout*>(this->layout())->insertWidget(2, onlineIconsScrollArea);*/
}

GUI_UsersBar::~GUI_UsersBar(){
    delete ui;
}

QLabel *GUI_UsersBar::getUserIcon(long userId, QColor color){
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
    //label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);
    //label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    label->setMaximumSize(GUI_Icons::iconSize,GUI_Icons::iconSize);
    label->setMinimumSize(GUI_Icons::iconSize,GUI_Icons::iconSize);
    label->setToolTip(QString("<font color = \"" + Stub::getUserColor(userId) + "\">") + Stub::getNickname(userId) + "</font>");
    //label->setFrameShape(QFrame::Box);

    return label;
}

void GUI_UsersBar::updateOnlineAreatSize(){


}

void GUI_UsersBar::addUserIcon(long userId, QColor color){
    if(this->usersIconMap.find(userId) != usersIconMap.end())
        return;

    QLabel *iconLabel = getUserIcon(userId, color);
    usersIconMap.insert(userId, iconLabel);
    ui->numberUsersLabel->setNum(usersIconMap.size());

    this->findChild<GUI_MyScrollArea*>(getOnlineAreaName())->widget()->layout()->addWidget(iconLabel);
    this->findChild<GUI_MyScrollArea*>(getOnlineAreaName())->updateSize(usersIconMap.size());
}

void GUI_UsersBar::removeUserIcon(long userId){
    if(this->usersIconMap.find(userId) == usersIconMap.end())
        return;

    usersIconMap[userId]->close();
    usersIconMap.remove(userId);
    ui->numberUsersLabel->setNum(usersIconMap.size());
    this->findChild<GUI_MyScrollArea*>(getOnlineAreaName())->updateSize(usersIconMap.size());
}

//serve solo per il debug
void GUI_UsersBar::on_pushButton_clicked()
{
    editorParent->addUserToEditorGUI(QRandomGenerator::global()->bounded(2000));
}

void GUI_UsersBar::on_pushButton_2_clicked()
{
    editorParent->removeUserFromEditorGUI(usersIconMap.keys().first());
}
