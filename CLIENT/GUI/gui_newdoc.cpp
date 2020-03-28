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

    long documentId;
    long result = GUI_ConnectionToServerWrapper::requestCreateDocumentWrapper(gimpParent, static_cast<GIMPdocs*>(gimpParent)->userid, ui->nameLineEdit->text());
    if(result == -1)
        return;
    else
        documentId = result;

    GUI_Editor *widget = new GUI_Editor(static_cast<GIMPdocs*>(gimpParent), documentId);
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

    long documentId;
    if(long result = GUI_ConnectionToServerWrapper::requestDocDatoUriWrapper(gimpParent, ui->URILineEdit->text()) == -1)
        return;
    else
        documentId = result;

    GUI_Editor *widget = new GUI_Editor(gimpParent, documentId);
    static_cast<GIMPdocs*>(gimpParent)->setUi2(widget);
}
