#include "gui_forgetdoc.h"
#include "gui_menu.h"
#include "editorWindow/gui_editor.h"
#include <QMessageBox>

GUI_Forgetdoc::GUI_Forgetdoc(QWidget *parent) : QWidget(parent){
    this->setObjectName(getObjectName());
    gimpParent = static_cast<GUI_Menu*>(parent)->gimpParent;

    ui = new Ui::GUI_ForgetDoc;
    ui->setupUi(this);

    fillList();

    connect(ui->docsListWidget, &QListWidget::doubleClicked, this, &GUI_Forgetdoc::on_forgetPushButton_clicked);
}

GUI_Forgetdoc::~GUI_Forgetdoc(){
    delete ui;
}

void GUI_Forgetdoc::on_forgetPushButton_clicked(){
    if(ui->docsListWidget->currentItem() == nullptr){
        QMessageBox::information(this, "", "Please, select a document");
        return;
    }

    if(QMessageBox::question(this, "", "Do you really want to forget \"" + ui->docsListWidget->currentItem()->text() + "\" document?") == QMessageBox::No)
        return;

    int id = Stub::forgetDocumentWithName(this->gimpParent->userid, ui->docsListWidget->currentItem()->text());
    if(id < 0){
        QMessageBox::information(this, "", "PANIC! Qualcosa è andato storto");
        //TODO gestire più dettagliatamente
        return;
    }

    ui->docsListWidget->takeItem(ui->docsListWidget->currentRow());
}

void GUI_Forgetdoc::fillList(){
    std::shared_ptr<QVector<QString>> vp = Stub::getDocuments(static_cast<GIMPdocs*>(gimpParent)->userid);

    for(QString *s = vp->begin(); s != vp->end(); s++){
        ui->docsListWidget->addItem(*s);
    }
}
