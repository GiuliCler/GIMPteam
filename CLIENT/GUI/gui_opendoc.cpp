#include "gui_opendoc.h"
#include "gimpdocs.h"
#include "editorWindow/gui_editor.h"
#include "gui_menu.h"
#include "gui_uri.h"
#include <QMessageBox>

#include <QPrinter>
#include <QFileDialog>
#include <QFileInfo>

#define GUI_OPENDOC_WIDGETLIST_DOCNAME 0
#define GUI_OPENDOC_WIDGETLIST_DOCID 1

GUI_Opendoc::GUI_Opendoc(QWidget *parent) : QWidget(parent)
{
    this->setObjectName(GUI_Opendoc::getObjectName());
    gimpParent = static_cast<GUI_Menu*>(parent)->gimpParent;
    ui = new Ui::GUI_Opendoc;
    ui->setupUi(this);

    fillList();

    //imposto la connect per il doppio click ed aprire il doc
    connect(ui->ownedDocsListWidget, &QListWidget::doubleClicked, this, &GUI_Opendoc::on_openDocsPushButton_clicked);
    connect(ui->sharedDocsListWidget, &QListWidget::doubleClicked, this, &GUI_Opendoc::on_openDocsPushButton_clicked);
    //questo mi serve per avere al massimo un item selezionato alla volta
    connect(ui->ownedDocsListWidget, &QListWidget::itemClicked, this, &GUI_Opendoc::on_ownedDocsListWidget_itemClicked);
    connect(ui->sharedDocsListWidget, &QListWidget::itemClicked, this, &GUI_Opendoc::on_sharedDocsListWidget_itemClicked);
    //questa connect è per rimuovere dall'elenco un documento appena eliminato da qualcun altro
    connect(gimpParent->getConnection(), &connection_to_server::unavailableSharedDocument, this, &GUI_Opendoc::unavailableSharedDocument_emitted);
}

GUI_Opendoc::~GUI_Opendoc(){
    delete ui;
}


/*SLOTS*/

void GUI_Opendoc::on_openDocsPushButton_clicked(){
    QListWidgetItem *currentItem = getSelectedItem();

    if(currentItem == nullptr){
        QMessageBox::information(this, "", "Please, select a document");
        return;
    }
    int docId = currentItem->data(GUI_OPENDOC_WIDGETLIST_DOCID).toInt();
    QString docName = currentItem->data(GUI_OPENDOC_WIDGETLIST_DOCNAME).toString().split("(")[0];
    QString codedParameters = GUI_ConnectionToServerWrapper::requestOpenDocumentWrapper(gimpParent, gimpParent->userid, docId);
    if(codedParameters.compare("errore") == 0)
        return;

    int siteCounter = codedParameters.split("_").at(1).toInt();

    GUI_Editor *widget = new GUI_Editor(gimpParent, docId, docName, siteCounter);
    static_cast<GIMPdocs*>(gimpParent)->setUi2(widget);
}

void GUI_Opendoc::on_getURIPushButton_clicked(){
    QListWidgetItem *currentItem = getSelectedItem();

    if(currentItem == nullptr){
        QMessageBox::information(this, "", "Please, select a document");
        return;
    }

    int documentId = currentItem->data(GUI_OPENDOC_WIDGETLIST_DOCID).toInt();
    QString uri = GUI_ConnectionToServerWrapper::requestUriWrapper(gimpParent, documentId);
    if(uri.compare("errore") == 0)
        return;

    GUI_URI *box = new GUI_URI(this, uri);
    box->setVisible(true);
}

void GUI_Opendoc::on_exportPDFPushButton_clicked(){
    QListWidgetItem *currentItem = getSelectedItem();

    if(currentItem == nullptr){
        QMessageBox::information(this, "", "Please, select a document");
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this, "Export PDF", "", "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty())
        fileName.append(".pdf");

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);


    int docId = currentItem->data(GUI_OPENDOC_WIDGETLIST_DOCID).toInt();
    std::shared_ptr<QTextEdit> docp = GUI_ConnectionToServerWrapper::getDocumentTextWrapper(gimpParent, docId, gimpParent->userid);

    if( docp == nullptr)
        return;
    docp->document()->setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
    docp->print(&printer);
}

void GUI_Opendoc::on_forgetPushButton_clicked(){
    QListWidgetItem *currentItem = getSelectedItem();

    if(currentItem == nullptr){
        QMessageBox::information(this, "", "Please, select a document");
        return;
    }

    QString docName = currentItem->data(GUI_OPENDOC_WIDGETLIST_DOCNAME).toString();
    //if the current user is the owner of the forgetted document
    if(ui->ownedDocsListWidget->currentRow() != -1){
        if(QMessageBox::question(this, "", "The document \"" + docName + "\" may be shared with other users. Do you really want to forget it?") == QMessageBox::No)
            return;
    }
    else{
        if(QMessageBox::question(this, "", "Do you really want to forget \"" + docName + "\" document?") == QMessageBox::No)
            return;
    }

    int docId = currentItem->data(GUI_OPENDOC_WIDGETLIST_DOCID).toInt();

    if(GUI_ConnectionToServerWrapper::requestDeleteDocumentWrapper(gimpParent, gimpParent->userid, docId) == -1)
        return;

    removeSelectedItem();
}

void GUI_Opendoc::on_ownedDocsListWidget_itemClicked(){
    ui->sharedDocsListWidget->setCurrentRow(-1);
}

void GUI_Opendoc::on_sharedDocsListWidget_itemClicked(){
    ui->ownedDocsListWidget->setCurrentRow(-1);
}

void GUI_Opendoc::unavailableSharedDocument_emitted(int docId){
    //in pratica questa funzione fa da wrapper che fa qualche controllo. Non vedo come possa fallire, ma non si sa mai
    QListWidgetItem* currentItem = getSelectedItem();

    //in teoria non dovrebbe mai succedere
    if(currentItem == nullptr)
        return;

    //anche questo non dovrebbe mai succedere
    if(currentItem->data(GUI_OPENDOC_WIDGETLIST_DOCID).toInt() != docId)
        return;

    removeSelectedItem();
}




void GUI_Opendoc::fillList(){
    std::shared_ptr<QMap<int, QString>> vp = GUI_ConnectionToServerWrapper::requestGetKnownDocumentsWrapper(gimpParent, gimpParent->userid);
    if(vp == nullptr)
        return;

    for(auto pair = vp->begin(); pair != vp->end(); pair++){
        //lo inizializzo per togliere il warning
        QListWidgetItem* item = new QListWidgetItem;
        item->setData(GUI_OPENDOC_WIDGETLIST_DOCNAME, pair.value());
        item->setData(GUI_OPENDOC_WIDGETLIST_DOCID, pair.key());

        int ownerId = GUI_ConnectionToServerWrapper::requestDocumentOwnerWrapper(gimpParent, item->data(GUI_OPENDOC_WIDGETLIST_DOCID).toInt());
        if(ownerId != -1){
            if(gimpParent->userid == ownerId)
                ui->ownedDocsListWidget->addItem(item);
            else{
                QString docName = item->data(GUI_OPENDOC_WIDGETLIST_DOCNAME).toString();
                docName.append("(");
                QString result = GUI_ConnectionToServerWrapper::requestGetNicknameWrapper(gimpParent, ownerId);
                if(result.compare("errore") != 0)
                    docName.append(result);
                docName.append(")");

                item->setData(GUI_OPENDOC_WIDGETLIST_DOCNAME, docName);
                ui->sharedDocsListWidget->addItem(item);
            }
        }
    }
}

QListWidgetItem* GUI_Opendoc::getSelectedItem(){
    if(ui->ownedDocsListWidget->currentRow() != -1)
        return ui->ownedDocsListWidget->currentItem();
    if(ui->sharedDocsListWidget->currentRow() != -1)
        return ui->sharedDocsListWidget->currentItem();

    return nullptr;
}

void GUI_Opendoc::removeSelectedItem(){
    //non so da quale tabella devo eliminarlo, ma so che è selezionato
    if(ui->ownedDocsListWidget->currentRow() != -1)
        ui->ownedDocsListWidget->takeItem(ui->ownedDocsListWidget->currentRow());
    if(ui->sharedDocsListWidget->currentRow() != -1)
        ui->sharedDocsListWidget->takeItem(ui->sharedDocsListWidget->currentRow());
}
