#include "gui_editor.h"
#include "gimpdocs.h"
#include "gui_menu.h"
#include "gui_mytextedit.h"
#include <memory>
#include <QBitmap>
#include <QPainter>

#define MAX_ICONWIDGET_WIDTH 15

GUI_Editor::GUI_Editor(QWidget *parent, long documentId) : QWidget(parent), documentId(documentId)
{
    this->setObjectName(GUI_Editor::getObjectName());
    gimpParent = static_cast<GIMPdocs*>(parent);
    ui = new Ui::GUI_Editor();
    ui->setupUi(this);

    setUsersBar();
    GUI_MyTextEdit *textEdit = new GUI_MyTextEdit(this);
    ui->textWidget->layout()->addWidget(textEdit);

    //debug purpose only
    timer = new QTimer(this);
    timer->start(5000);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerSlot()));
}

GUI_Editor::~GUI_Editor(){
    delete ui;
}

void GUI_Editor::setUsersBar(){
    //ottengo l'elenco degli utenti che al momento stanno guardando il mio stesso document, li salvo nella map e creo le icone
    std::shared_ptr<QSet<long>> users = Stub::getWorkingUsersOnDocument(this->documentId);
    ui->numberUsersLabel->setNum(users->size());
    for (QSet<long>::iterator userId = users->begin(); userId != users->end(); userId++){
        QLabel *iconLabel = getUserIcon(*userId);
        usersIconMap.insert(*userId, iconLabel);
        ui->iconsWidget->layout()->addWidget(iconLabel);
    }

    updateIconsWidgetSize();
}

QLabel *GUI_Editor::getUserIcon(long userId){
    long iconId = Stub::getIconId(userId);
    QPixmap *image = new QPixmap(GUI_Icons::getIconPath(iconId));
    QPixmap *background = new QPixmap(image->height(), image->width());
    background->fill(Qt::red);
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

void GUI_Editor::updateIconsWidgetSize(){
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

void GUI_Editor::addUserIcon(long userId){
    if(this->usersIconMap.find(userId) != usersIconMap.end())
        return;

    QLabel *iconLabel = getUserIcon(userId);
    usersIconMap.insert(userId, iconLabel);
    ui->iconsWidget->layout()->addWidget(iconLabel);
    ui->numberUsersLabel->setNum(usersIconMap.size());
    if(usersIconMap.size() < MAX_ICONWIDGET_WIDTH+1)
        updateIconsWidgetSize();
}

void GUI_Editor::removeUserIcon(long userId){
    if(this->usersIconMap.find(userId) == usersIconMap.end())
        return;

    usersIconMap[userId]->close();
    usersIconMap.remove(userId);
    ui->numberUsersLabel->setNum(usersIconMap.size());
    if(usersIconMap.size() < MAX_ICONWIDGET_WIDTH + 1)
        updateIconsWidgetSize();
}

//serve solo per il debug
void GUI_Editor::timerSlot(){

    GUI_MyTextEdit *textEditor = this->findChild<GUI_MyTextEdit*>(GUI_MyTextEdit::getObjectName());
    if(! textEditor->hasFocus())
        return;

    QPoint position(textEditor->cursorRect().x(), textEditor->cursorRect().y());
    textEditor->addUserCursor(1, position);
}
