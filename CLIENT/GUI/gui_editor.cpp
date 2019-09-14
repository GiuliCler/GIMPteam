#include "gui_editor.h"
#include "gimpdocs.h"
#include "gui_menu.h"
#include <memory>

GUI_Editor::GUI_Editor(QWidget *parent, long documentId) : QWidget(parent), documentId(documentId)
{
    ui = new Ui::GUI_Editor();
    ui->setupUi(this);

    setUsersBar();
}

GUI_Editor::~GUI_Editor(){
    delete ui;
}

void GUI_Editor::on_menuPushButton_clicked()
{
    GUI_Menu *widget = new GUI_Menu(static_cast<GIMPdocs*>(this->parent()));
    static_cast<GIMPdocs*>(this->parent())->setUi1(widget);
}

void GUI_Editor::setUsersBar(){
    ui->iconsWidget->setLayout(new QHBoxLayout);
    ui->iconsWidget->layout()->setMargin(0);
    ui->iconsWidget->layout()->setSpacing(0);
    ui->iconsWidget->setMaximumWidth(20*GUI_Icons::iconSize);

    //ottengo l'elenco degli utenti che al momento stanno guardando il mio stesso document, li salvo nella map e creo le icone
    std::shared_ptr<QSet<long>> users = Stub::getWorkingUsersOnDocument(this->documentId);
    ui->numberUsersLabel->setNum(users->size());
    for (QSet<long>::iterator userId = users->begin(); userId != users->end(); userId++){

        //non dovrebbero esserci duplicati, ma per sicurezza controllo
        if(usersIconMap.find(*userId) == usersIconMap.end()){
            QLabel *iconLabel = getUserIcon(*userId);
            usersIconMap.insert(*userId, iconLabel);
            ui->iconsWidget->layout()->addWidget(iconLabel);
        }
    }
}

QLabel *GUI_Editor::getUserIcon(long userId){
    long iconId = Stub::getIconId(userId);
    QPixmap *image = new QPixmap(GUI_Icons::getIconPath(iconId));
    QLabel *label = new QLabel(this);

    label->setPixmap(*image);
    label->setScaledContents(true);
    label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);
    label->setMaximumSize(GUI_Icons::iconSize,GUI_Icons::iconSize);
    label->setToolTip(QString("<font color = \"red\">") + Stub::getNickname(userId) + "</font>");
    //label->setFrameShape(QFrame::Box);

    return label;
}
