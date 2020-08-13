#include "gui_newdoc.h"
#include "gui_menu.h"
#include "editorWindow/gui_editor.h"

#include "ui_gui_editorwindow.h"
#include <QMessageBox>

GUI_Newdoc::GUI_Newdoc(QWidget *parent) : QWidget(parent)
{
    this->setObjectName(GUI_Newdoc::getObjectName());
    gimpParent = static_cast<GUI_Menu*>(parent)->gimpParent;
    ui = new Ui::GUI_Newdoc;
    ui->setupUi(this);

    //imposto la connect per premere invio
    connect(ui->nameLineEdit, &QLineEdit::returnPressed, this, &GUI_Newdoc::on_createPushButton_clicked);
    connect(ui->URILineEdit, &QLineEdit::returnPressed, this, &GUI_Newdoc::on_openURIPushButton_clicked);

    //style
    QFont font = ui->newDocumentTitleLabel->font();
    font.setPixelSize(font.pixelSize() + 3);
    ui->newDocumentTitleLabel->setFont(font);

    font = ui->uriDocumentTitleLabel->font();
    font.setPixelSize(font.pixelSize() + 3);
    ui->uriDocumentTitleLabel->setFont(font);
}

GUI_Newdoc::~GUI_Newdoc(){
    delete ui;
}

void GUI_Newdoc::on_createPushButton_clicked()
{
    if(ui->nameLineEdit->text().isEmpty()){
        QMessageBox::information(this, "", "\"Name\" field is empty");
        return;
    }
    if(ui->nameLineEdit->text().contains('\\')){
        QMessageBox::information(this, "", "Invalid character \"\\\" is present in \"Name\"");
        return;
    }
    QString docName = ui->nameLineEdit->text();
    //qui mi arriva una serie di parametri codificati in qualche modo in unìunica stringa
    QString codedParameters = GUI_ConnectionToServerWrapper::requestCreateDocumentWrapper(gimpParent, static_cast<GIMPdocs*>(gimpParent)->userid, docName);
    if(codedParameters.compare("errore") == 0)
        return;

    int siteId = codedParameters.split("_").at(1).toInt();
    int siteCounter = codedParameters.split("_").at(2).toInt();
    int documentId = codedParameters.split("_").at(3).toInt();


    GUI_Editor *widget = new GUI_Editor(static_cast<GIMPdocs*>(gimpParent), documentId, docName, siteId, siteCounter);
    static_cast<GIMPdocs*>(gimpParent)->setUi2(widget);
}

void GUI_Newdoc::on_openURIPushButton_clicked()
{
    if(ui->URILineEdit->text().isEmpty()){
        QMessageBox::information(this, "", "\"URI\" field is empty");
        return;
    }
    if(ui->nameLineEdit->text().contains('\\')){
        QMessageBox::information(this, "", "Invalid character \"\\\" is present in \"URI\"");
        return;
    }

    QString codedParameters = GUI_ConnectionToServerWrapper::requestDocumentDatoUriWrapper(gimpParent, gimpParent->userid, ui->URILineEdit->text());
    if(codedParameters.compare("errore") == 0)
        return;

    int siteId = codedParameters.split("_").at(1).toInt();
    int siteCounter = codedParameters.split("_").at(2).toInt();
    int documentId = codedParameters.split("_").at(3).toInt();

    QString docName = GUI_ConnectionToServerWrapper::requestDocumentNameWrapper(gimpParent, documentId);

    GUI_Editor *widget = new GUI_Editor(static_cast<GIMPdocs*>(gimpParent), documentId, docName, siteId, siteCounter);
    static_cast<GIMPdocs*>(gimpParent)->setUi2(widget);
}
