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
}

GUI_Opendoc::~GUI_Opendoc(){
    delete ui;
}



void GUI_Opendoc::on_openDocsPushButton_clicked(){
    QListWidgetItem *currentItem = getSelectedItem();

    if(currentItem == nullptr){
        QMessageBox::information(this, "", "Please, select a document");
        return;
    }

    int docId = currentItem->data(GUI_OPENDOC_WIDGETLIST_DOCID).toInt();
    Stub::openKnownDocument(docId);

    GUI_Editor *widget = new GUI_Editor(gimpParent, docId);
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
    std::shared_ptr<QTextDocument> docp = GUI_ConnectionToServerWrapper::getDocumentTextWrapper(gimpParent, docId);
    if( docp == nullptr)
        return;

    docp->setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
    docp->print(&printer);
}

//TODO: l'eliminazione di un documento deve avvertire il possessore del documento che anche tutti i collaboratori
//non potranno più accedervi (messaggio ulteriore di notifica). L'eliminazione del documento da parte dei collaboratori elimina
//solamente la corrispondenza con quel documento nel db.
void GUI_Opendoc::on_forgetPushButton_clicked(){
    QListWidgetItem *currentItem = getSelectedItem();

    if(currentItem == nullptr){
        QMessageBox::information(this, "", "Please, select a document");
        return;
    }

    QString docName = currentItem->data(GUI_OPENDOC_WIDGETLIST_DOCNAME).toString();
    if(QMessageBox::question(this, "", "Do you really want to forget \"" + docName + "\" document?") == QMessageBox::No)
        return;

    int docId = currentItem->data(GUI_OPENDOC_WIDGETLIST_DOCID).toInt();
    int result = GUI_ConnectionToServerWrapper::forgetKnownDocumentWrapper(gimpParent, gimpParent->userid, docId);
    if(result == -1)
        return;

    removeSelectedItem();
}

void GUI_Opendoc::on_ownedDocsListWidget_itemClicked(){
    ui->sharedDocsListWidget->setCurrentRow(-1);
}

void GUI_Opendoc::on_sharedDocsListWidget_itemClicked(){
    ui->ownedDocsListWidget->setCurrentRow(-1);
}



void GUI_Opendoc::fillList(){
    std::shared_ptr<QMap<QString, int>> vp = GUI_ConnectionToServerWrapper::getKnownDocumentsWrapper(gimpParent, gimpParent->userid);
    if(vp == nullptr)
        return;

    int debugCounter = 0;

    for(auto pair = vp->begin(); pair != vp->end(); pair++){
        //lo inizializzo per togliere il warning
        QListWidgetItem* item = new QListWidgetItem;
        item->setData(GUI_OPENDOC_WIDGETLIST_DOCNAME, pair.key());
        item->setData(GUI_OPENDOC_WIDGETLIST_DOCID, pair.value());

        //TODO chiamare la funzione per controllare il vero owner
        if(debugCounter % 2 == 0)
            ui->ownedDocsListWidget->addItem(item);
        else
            ui->sharedDocsListWidget->addItem(item);

        debugCounter++;
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
    if(ui->ownedDocsListWidget->currentRow() != -1)
        ui->ownedDocsListWidget->takeItem(ui->ownedDocsListWidget->currentRow());
    if(ui->sharedDocsListWidget->currentRow() != -1)
        ui->sharedDocsListWidget->takeItem(ui->sharedDocsListWidget->currentRow());
}
