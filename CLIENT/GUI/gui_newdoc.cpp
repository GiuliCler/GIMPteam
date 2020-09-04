#include "gui_newdoc.h"
#include "gui_menu.h"
#include "editorWindow/gui_editor.h"

#include "ui_gui_editorwindow.h"
#include <QMessageBox>

GUI_Newdoc::GUI_Newdoc(QWidget *parent) : QWidget(parent)
{
    this->setObjectName(GUI_Newdoc::getObjectName());
    gimpParent = static_cast<GUI_Menu*>(parent)->gimpParent;
    ui.reset(new Ui::GUI_Newdoc);
    ui->setupUi(this);

    //imposto la connect per premere invio
    connect(ui->nameLineEdit, &QLineEdit::returnPressed, this, &GUI_Newdoc::on_createPushButton_clicked);
    connect(ui->URILineEdit, &QLineEdit::returnPressed, this, &GUI_Newdoc::on_openURIPushButton_clicked);
}

void GUI_Newdoc::on_createPushButton_clicked()
{
    if(!checkFieldValidity(ui->nameLineEdit->text(), "Name"))
        return;

    QString docName = ui->nameLineEdit->text();
    //qui mi arriva una serie di parametri codificati in qualche modo in un'unica stringa
    QString codedParameters = GUI_ConnectionToServerWrapper::requestCreateDocumentWrapper(gimpParent, static_cast<GIMPdocs*>(gimpParent)->userid, docName);
    if(codedParameters.compare("errore") == 0)
        return;

    int documentId = codedParameters.split("_").at(2).toInt();

    GUI_Editor *widget = nullptr;
    try {
        widget = new GUI_Editor(static_cast<GIMPdocs*>(gimpParent), documentId, docName, false);
    } catch (GUI_GenericException &exception) {
        delete widget;
        return;
    }

    static_cast<GIMPdocs*>(gimpParent)->setUi2(widget);
}

void GUI_Newdoc::on_openURIPushButton_clicked()
{
    if(!checkFieldValidity(ui->URILineEdit->text(), "URI"))
        return;

    QString codedParameters = GUI_ConnectionToServerWrapper::requestDocumentDatoUriWrapper(gimpParent, gimpParent->userid, ui->URILineEdit->text());
    if(codedParameters.compare("errore") == 0)
        return;

    int documentId = codedParameters.split("_").at(1).toInt();

    QString docName = GUI_ConnectionToServerWrapper::requestDocumentNameWrapper(gimpParent, documentId);
    if(docName.compare("errore") == 0)
        docName = "document_name_error";

    GUI_Editor *widget = nullptr;
    try {
        widget = new GUI_Editor(static_cast<GIMPdocs*>(gimpParent), documentId, docName, true);
    } catch (GUI_GenericException &exception) {
        delete widget;
        return;
    }

    static_cast<GIMPdocs*>(gimpParent)->setUi2(widget);
}


bool GUI_Newdoc::checkFieldValidity(QString value, QString name){
    if(value.isEmpty()){
        QMessageBox::information(this, "", "\"" + name + "\" field is empty");
        return false;
    }
    if(value.contains('\\') || value.contains('_')){
        QMessageBox::information(this, "", "An invalid character \"\\\", \"_\" is present in \"" + name + "\" field");
        return false;
    }
    if(value.contains("error")){
        QMessageBox::information(this, "", "Invalid string \"error\" is present in \"" + name + "\" field");
        return false;
    }

    return true;
}
