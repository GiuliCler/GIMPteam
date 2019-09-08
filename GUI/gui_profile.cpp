#include "gui_profile.h"
#include "gimpdocs.h"
#include "ui_gui_login.h"

GUI_Profile::GUI_Profile(QWidget *parent, double id) : QWidget(parent)
{
    ui = new Ui::GUI_Profile;
    ui->setupUi(this);
    if(id != -1){
        //TODO fare una getMapOfUser(id) ed impostare tutti i parametri, oppure prenderli uno a uno tipo get nickname
    }
}

void GUI_Profile::on_pushButton_clicked()
{
    GUI_Login *widget = new GUI_Login(static_cast<QWidget*>(this->parent()));
    static_cast<GIMPdocs*>(this->parent())->loadCentralWidget(widget);
}
