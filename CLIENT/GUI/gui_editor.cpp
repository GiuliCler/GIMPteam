#include "gui_editor.h"
#include "gimpdocs.h"
#include "gui_menu.h"

GUI_Editor::GUI_Editor(QWidget *parent, long documentId) : QWidget(parent), documentId(documentId)
{
    ui = new Ui::GUI_Editor();
    ui->setupUi(this);

    ui->iconsWidget->setLayout(new QHBoxLayout);
    //TODO c'è da fare ancora una funzione apposta
    for (int i = 0; i < 5; i++){
        ui->iconsWidget->layout()->addWidget(getUserIcon(i%5));
    }
}

GUI_Editor::~GUI_Editor(){
    delete ui;
}

void GUI_Editor::on_menuPushButton_clicked()
{
    GUI_Menu *widget = new GUI_Menu(static_cast<GIMPdocs*>(this->parent()));
    static_cast<GIMPdocs*>(this->parent())->setUi1(widget);
}

QLabel *GUI_Editor::getUserIcon(long userId){
    QPixmap *image = new QPixmap(GUI_Icons::getIconPath(userId));
    QLabel *label = new QLabel(this);
    //label->set
    label->setPixmap(*image);
    label->setScaledContents(true);
    label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    label->setMaximumSize(GUI_Icons::iconSize,GUI_Icons::iconSize);
    label->setToolTip(QString("<font color = \"red\">User ") + QString::number(userId) + "</font>");

    return label;
}
