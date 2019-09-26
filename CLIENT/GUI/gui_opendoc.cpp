#include "gui_opendoc.h"
#include "gimpdocs.h"
#include "editorWindow/gui_editor.h"
#include "gui_menu.h"
#include <QMessageBox>

GUI_Opendoc::GUI_Opendoc(QWidget *parent) : QWidget(parent)
{
    this->setObjectName(GUI_Opendoc::getObjectName());
    gimpParent = static_cast<GUI_Menu*>(parent)->gimpParent;
    ui = new Ui::GUI_Opendoc;
    ui->setupUi(this);

    fillList();

    //imposto la connect per premere invio ed aprire il doc
    connect(ui->URILineEdit, &QLineEdit::returnPressed, this, &GUI_Opendoc::on_openURIPushButton_clicked);
    connect(ui->docsListWidget, &QListWidget::doubleClicked, this, &GUI_Opendoc::on_openDocsPushButton_clicked);
}

GUI_Opendoc::~GUI_Opendoc(){
    delete ui;
}

void GUI_Opendoc::on_openDocsPushButton_clicked()
{
    if(ui->docsListWidget->currentItem() == nullptr){
        QMessageBox::information(this, "", "Please, select a document");
        return;
    }

    long id = Stub::openWithName(ui->docsListWidget->currentItem()->text());
    if(id < 0){
        QMessageBox::information(this, "", "PANIC! Il document non esiste");
        //TODO gestire più dettagliatamente
        return;
    }

    GUI_Editor *widget = new GUI_Editor(gimpParent, id);
    static_cast<GIMPdocs*>(gimpParent)->setUi2(widget);
}

void GUI_Opendoc::on_openURIPushButton_clicked()
{
    if(ui->URILineEdit->text().isEmpty()){
        QMessageBox::information(this, "", "\"URI\" field is empty");
        return;
    }

    long id = Stub::openWithURI(ui->URILineEdit->text());

    if(id < 0){
        QMessageBox::information(this, "", "Generic error opening with URI");
        //TODO gestire più dettagliatamente
        return;
    }

    GUI_Editor *widget = new GUI_Editor(gimpParent, id);
    static_cast<GIMPdocs*>(gimpParent)->setUi2(widget);
}

void GUI_Opendoc::fillList(){
    std::shared_ptr<QVector<QString>> vp = Stub::getDocuments(static_cast<GIMPdocs*>(gimpParent)->userid);

    for(QString *s = vp->begin(); s != vp->end(); s++){
        ui->docsListWidget->addItem(*s);
    }
}

void GUI_Opendoc::displayURI(long docId){
    //TODO
}
