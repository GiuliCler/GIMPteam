#include "gui_opendoc.h"
#include "editorWindow/gui_editor.h"
#include "gui_menu.h"
#include "gui_uri.h"

#include <QMessageBox>
#include <QPrinter>
#include <QFileDialog>
#include <QList>

#define GUI_OPENDOC_WIDGETLIST_DOCNAME 0
#define GUI_OPENDOC_WIDGETLIST_DOCID 1

GUI_Opendoc::GUI_Opendoc(QWidget *parent) : QWidget(parent)
{
    this->setObjectName(GUI_Opendoc::getObjectName());
    gimpParent = static_cast<GUI_Menu*>(parent)->gimpParent;
    ui.reset(new Ui::GUI_Opendoc);
    ui->setupUi(this);

    fillList();

    //imposto la connect per il doppio click ed aprire il doc
    connect(ui->ownedDocsListWidget, &QListWidget::itemActivated, this, &GUI_Opendoc::on_openDocsPushButton_clicked);
    connect(ui->sharedDocsListWidget, &QListWidget::itemActivated, this, &GUI_Opendoc::on_openDocsPushButton_clicked);
    //questo mi serve per avere al massimo un item selezionato alla volta
    connect(ui->ownedDocsListWidget, &QListWidget::itemClicked, this, &GUI_Opendoc::on_ownedDocsListWidget_itemClicked);
    connect(ui->sharedDocsListWidget, &QListWidget::itemClicked, this, &GUI_Opendoc::on_sharedDocsListWidget_itemClicked);
    //questa connect è per rimuovere dall'elenco un documento appena eliminato da qualcun altro
    connect(gimpParent->getConnection(), &connection_to_server::unavailableSharedDocument, this, &GUI_Opendoc::unavailableSharedDocument_emitted);
}


/*SLOTS*/

void GUI_Opendoc::on_openDocsPushButton_clicked(){
    int docId = getSelectedItemId();
    QString docName;

    if(docId == -1){
        QMessageBox::information(this, "", "Please, select a document");
        return;
    }

    docName = getSelectedItemName();

    GUI_Editor *widget = nullptr;
    try {
        widget = new GUI_Editor(gimpParent, docId, docName, true);
    } catch (GUI_GenericException &exception) {
        delete widget;
        return;
    }

    static_cast<GIMPdocs*>(gimpParent)->setUi2(widget);
}

void GUI_Opendoc::on_getURIPushButton_clicked(){
    int docId = getSelectedItemId();

    if(docId == -1){
        QMessageBox::information(this, "", "Please, select a document");
        return;
    }

    QString uri = GUI_ConnectionToServerWrapper::requestUriWrapper(gimpParent, docId);
    if(uri.compare("errore") == 0)
        return;

    GUI_URI *box = new GUI_URI(this, uri);
    box->setVisible(true);
}

void GUI_Opendoc::on_exportPDFPushButton_clicked(){
    int docId = getSelectedItemId();
    QString docName;

    if(docId == -1){
        QMessageBox::information(this, "", "Please, select a document");
        return;
    }

    docName = getSelectedItemName();
    if(docName.compare("") == 0)
        //non dovrebbe mai verificarsi, ma non si sa mai
        docName = "Default";
    QString fileName = QFileDialog::getSaveFileName(this, "Export PDF", docName, "*.pdf");
    //se l'utente non seleziona nulla mi ritorna una stringa vuota, quindi non so distinguere se l'utente ha annullato l'operazione o se vuole dargli un nome vuoto. Nel dubbio glielo impedisco.
    //Forse però la getSaveFileName impedisce di salvare un nome vuoto, a meno che non sia il nome di default
    if(fileName.compare("") == 0)
        return;
    if (QFileInfo(fileName).suffix().isEmpty())
        fileName.append(".pdf");

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);


    std::shared_ptr<QTextEdit> docp = GUI_ConnectionToServerWrapper::getDocumentTextWrapper(gimpParent, docId, gimpParent->userid);
    if( docp == nullptr)
        return;

    docp->print(&printer);
}

void GUI_Opendoc::on_forgetPushButton_clicked(){
    int docId = getSelectedItemId();
    QString docName;

    if(docId == -1){
        QMessageBox::information(this, "", "Please, select a document");
        return;
    }

    docName = getSelectedItemName();
    //if the current user is the owner of the forgetted document
    if(ui->ownedDocsListWidget->currentRow() != -1){
        if(QMessageBox::question(this, "", "The document \"" + docName + "\" may be shared with other users. Do you really want to forget it?") == QMessageBox::No)
            return;
    }
    else{
        if(QMessageBox::question(this, "", "Do you really want to forget \"" + docName + "\" document?") == QMessageBox::No)
            return;
    }

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

//ricorda: si è deciso di rimuovere un file non più esistente solo quando l'utente prova a farci qualcosa. Altrimenti rimane in elenco (finchè non ricaricherò il widget)
void GUI_Opendoc::unavailableSharedDocument_emitted(int docId){
    //in pratica questa funzione fa da wrapper che fa qualche controllo. Non vedo come possa fallire, ma non si sa mai
    int currentDocId = getSelectedItemId();

    //anche questo non dovrebbe mai succedere
    if(currentDocId != docId)
        return;

    removeSelectedItem();
}




void GUI_Opendoc::fillList(){
    std::shared_ptr<QMap<int, QString>> knownDocuments = GUI_ConnectionToServerWrapper::requestGetKnownDocumentsWrapper(gimpParent, gimpParent->userid);
    if(knownDocuments == nullptr)
        return;

    QList<QPair<int, QString>> knownDocumentsList = QList<QPair<int, QString>>();

    for(auto pair = knownDocuments->begin(); pair != knownDocuments->end(); pair++)
        knownDocumentsList.append(QPair<int, QString>(pair.key(), pair.value()));

    std::sort(knownDocumentsList.begin(), knownDocumentsList.end(), [](QPair<int, QString> a, QPair<int, QString> b) {
        return a.second < b.second;
    });

    for(auto pair : knownDocumentsList)
        addItem(pair.first, pair.second);
}

void GUI_Opendoc::addItem(int docId, QString docName){
    QListWidgetItem* item = new QListWidgetItem;
    item->setData(GUI_OPENDOC_WIDGETLIST_DOCNAME, docName);
    item->setData(GUI_OPENDOC_WIDGETLIST_DOCID, docId);

    if(knownDocuments.find(docId) != knownDocuments.end())
        return;

    int ownerId = GUI_ConnectionToServerWrapper::requestDocumentOwnerWrapper(gimpParent, item->data(GUI_OPENDOC_WIDGETLIST_DOCID).toInt());
    if(ownerId == -1)
        return; 

    if(gimpParent->userid == ownerId)
        ui->ownedDocsListWidget->addItem(item);
    else{
        QString newdocName = docName;
        newdocName.append(" (");
        QString result = GUI_ConnectionToServerWrapper::requestGetNicknameWrapper(gimpParent, ownerId);
        if(result.compare("errore") != 0)
            newdocName.append(result);
        newdocName.append(")");

        item->setData(GUI_OPENDOC_WIDGETLIST_DOCNAME, newdocName);
        ui->sharedDocsListWidget->addItem(item);
    }

    //lo aggiungo solo lla fine, quando sono sicuro che non possano più esserci fallimenti causa connection_to_server che possano causare asimmetrie tra widget e mappa
    //volendo potrei fare un'ulteriore funzione senza controlli, da chiamare dopo aver fatto i controlli fuori, solo per sinccronizzare mappa e widget
    knownDocuments.insert(docId, docName);

}

int GUI_Opendoc::getSelectedItemId(){
    QListWidgetItem* currentItem = nullptr;

    if(ui->ownedDocsListWidget->currentRow() != -1)
        currentItem = ui->ownedDocsListWidget->currentItem();
    if(ui->sharedDocsListWidget->currentRow() != -1)
        currentItem = ui->sharedDocsListWidget->currentItem();

    if(currentItem == nullptr)
        return -1;

    return currentItem->data(GUI_OPENDOC_WIDGETLIST_DOCID).toInt();
}

QString GUI_Opendoc::getSelectedItemName(){
    int docId = getSelectedItemId();

    if(knownDocuments.find(docId) == knownDocuments.end())
        return "";

    return knownDocuments[docId];
}

void GUI_Opendoc::removeSelectedItem(){
    int docId = getSelectedItemId();

    if(knownDocuments.find(docId) == knownDocuments.end())
        return;

    knownDocuments.remove(docId);

    //non so da quale tabella devo eliminarlo, ma so che è selezionato
    if(ui->ownedDocsListWidget->currentRow() != -1)
        ui->ownedDocsListWidget->takeItem(ui->ownedDocsListWidget->currentRow());
    if(ui->sharedDocsListWidget->currentRow() != -1)
        ui->sharedDocsListWidget->takeItem(ui->sharedDocsListWidget->currentRow());
}
