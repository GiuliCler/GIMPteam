#include "gui_opendoc.h"
#include "gimpdocs.h"
#include "gui_menu.h"

GUI_Opendoc::GUI_Opendoc(QWidget *parent) : QWidget(parent)
{
    ui = new Ui::GUI_Opendoc;
    ui->setupUi(this);
}
void GUI_Opendoc::on_pushButton_clicked()
{
    //TODO devo collegare la editor window
    //GUI_Menu *widget = new GUI_Menu(static_cast<QWidget*>(this->parent()));
    //static_cast<GIMPdocs*>(this->parent())->loadCentralWidget(widget);
}
