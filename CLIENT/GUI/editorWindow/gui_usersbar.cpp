#include "gui_usersbar.h"
#include "gui_editor.h"
#include <QPainter>

#define MAX_ICONWIDGET_WIDTH 15

GUI_UsersBar::GUI_UsersBar(QWidget *parent) : QWidget(parent){
    this->setObjectName(GUI_UsersBar::getObjectName());
    editorParent = static_cast<GUI_Editor*>(parent);
    ui = new Ui::GUI_UsersBar();
    ui->setupUi(this);
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
    label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);
    label->setMaximumSize(GUI_Icons::iconSize,GUI_Icons::iconSize);
    label->setToolTip(QString("<font color = \"" + Stub::getUserColor(userId) + "\">") + Stub::getNickname(userId) + "</font>");
    //label->setFrameShape(QFrame::Box);

    return label;
}

void GUI_UsersBar::updateIconsWidgetSize(){
    /*non potevo mettere policy Fixed perchè le icone sono Ignored ed il fixed non avendo un valore fisso interno si azzera, quindi lo fixo settando a mano max e min
     * la policy del widget è expanding perchè altrimenti viene schiacciato dall'altro expanding. Devo mettere almeno un expanding o per riempire lo spazio mi aumenta lo spacing fra i widget senza chiedermi il permesso
     * ho anche dato proporzioni diverse ai 2 expanding (20,1) per dire che il widget delle icone ha diritto a tutto quello di cui ha bisogno
     * */
    //ho deciso che fino a 10 gli do lo spazio giusto giusto, oltre i 10 utenti comprimo le icone e si fanno bastare lo spazio che hanno
    int number = usersIconMap.size() <= MAX_ICONWIDGET_WIDTH ? usersIconMap.size() : MAX_ICONWIDGET_WIDTH;
    //il +1 è perchè li lascio un po' più larghi
    ui->iconsWidget->setMaximumWidth((number+1)*GUI_Icons::iconSize);
    ui->iconsWidget->setMinimumWidth((number+1)*GUI_Icons::iconSize);
}

void GUI_UsersBar::addUserIcon(long userId, QColor color){
    if(this->usersIconMap.find(userId) != usersIconMap.end())
        return;

    QLabel *iconLabel = getUserIcon(userId, color);
    usersIconMap.insert(userId, iconLabel);
    ui->iconsWidget->layout()->addWidget(iconLabel);
    ui->numberUsersLabel->setNum(usersIconMap.size());
    if(usersIconMap.size() < MAX_ICONWIDGET_WIDTH+1)
        updateIconsWidgetSize();
}

void GUI_UsersBar::removeUserIcon(long userId){
    if(this->usersIconMap.find(userId) == usersIconMap.end())
        return;

    usersIconMap[userId]->close();
    usersIconMap.remove(userId);
    ui->numberUsersLabel->setNum(usersIconMap.size());
    if(usersIconMap.size() < MAX_ICONWIDGET_WIDTH + 1)
        updateIconsWidgetSize();
}
