/********************************************************************************
** Form generated from reading UI file 'gui_editorwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_EDITORWINDOW_H
#define UI_GUI_EDITORWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GUI_EditWindow
{
public:
    QAction *closeDocumentAction;
    QAction *actionCopy;
    QAction *actionCut;
    QAction *actionPaste;
    QAction *getURIAction;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionLeft;
    QAction *actionCenter;
    QAction *actionRight;
    QAction *actionJustified;
    QAction *actionItalic;
    QAction *actionBold;
    QAction *actionUnderlined;
    QAction *actionStrikethrough;
    QAction *actionApplyUsersColors;
    QAction *actionApplyTextColors;
    QAction *exportPDFAction;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuAlign;
    QMenu *menuUsers;

    void setupUi(QMainWindow *GUI_EditWindow)
    {
        if (GUI_EditWindow->objectName().isEmpty())
            GUI_EditWindow->setObjectName(QString::fromUtf8("GUI_EditWindow"));
        GUI_EditWindow->resize(621, 436);
        closeDocumentAction = new QAction(GUI_EditWindow);
        closeDocumentAction->setObjectName(QString::fromUtf8("closeDocumentAction"));
        actionCopy = new QAction(GUI_EditWindow);
        actionCopy->setObjectName(QString::fromUtf8("actionCopy"));
        actionCut = new QAction(GUI_EditWindow);
        actionCut->setObjectName(QString::fromUtf8("actionCut"));
        actionPaste = new QAction(GUI_EditWindow);
        actionPaste->setObjectName(QString::fromUtf8("actionPaste"));
        getURIAction = new QAction(GUI_EditWindow);
        getURIAction->setObjectName(QString::fromUtf8("getURIAction"));
        actionUndo = new QAction(GUI_EditWindow);
        actionUndo->setObjectName(QString::fromUtf8("actionUndo"));
        actionRedo = new QAction(GUI_EditWindow);
        actionRedo->setObjectName(QString::fromUtf8("actionRedo"));
        actionLeft = new QAction(GUI_EditWindow);
        actionLeft->setObjectName(QString::fromUtf8("actionLeft"));
        actionLeft->setCheckable(false);
        actionCenter = new QAction(GUI_EditWindow);
        actionCenter->setObjectName(QString::fromUtf8("actionCenter"));
        actionCenter->setCheckable(false);
        actionRight = new QAction(GUI_EditWindow);
        actionRight->setObjectName(QString::fromUtf8("actionRight"));
        actionRight->setCheckable(false);
        actionJustified = new QAction(GUI_EditWindow);
        actionJustified->setObjectName(QString::fromUtf8("actionJustified"));
        actionItalic = new QAction(GUI_EditWindow);
        actionItalic->setObjectName(QString::fromUtf8("actionItalic"));
        actionItalic->setCheckable(true);
        actionBold = new QAction(GUI_EditWindow);
        actionBold->setObjectName(QString::fromUtf8("actionBold"));
        actionBold->setCheckable(true);
        actionUnderlined = new QAction(GUI_EditWindow);
        actionUnderlined->setObjectName(QString::fromUtf8("actionUnderlined"));
        actionUnderlined->setCheckable(true);
        actionStrikethrough = new QAction(GUI_EditWindow);
        actionStrikethrough->setObjectName(QString::fromUtf8("actionStrikethrough"));
        actionStrikethrough->setCheckable(true);
        actionApplyUsersColors = new QAction(GUI_EditWindow);
        actionApplyUsersColors->setObjectName(QString::fromUtf8("actionApplyUsersColors"));
        actionApplyTextColors = new QAction(GUI_EditWindow);
        actionApplyTextColors->setObjectName(QString::fromUtf8("actionApplyTextColors"));
        actionApplyTextColors->setEnabled(false);
        exportPDFAction = new QAction(GUI_EditWindow);
        exportPDFAction->setObjectName(QString::fromUtf8("exportPDFAction"));
        centralwidget = new QWidget(GUI_EditWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        GUI_EditWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(GUI_EditWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 621, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuAlign = new QMenu(menuEdit);
        menuAlign->setObjectName(QString::fromUtf8("menuAlign"));
        menuUsers = new QMenu(menubar);
        menuUsers->setObjectName(QString::fromUtf8("menuUsers"));
        GUI_EditWindow->setMenuBar(menubar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuUsers->menuAction());
        menuFile->addAction(getURIAction);
        menuFile->addAction(exportPDFAction);
        menuFile->addAction(closeDocumentAction);
        menuEdit->addAction(actionUndo);
        menuEdit->addAction(actionRedo);
        menuEdit->addSeparator();
        menuEdit->addAction(actionCut);
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionPaste);
        menuEdit->addSeparator();
        menuEdit->addAction(menuAlign->menuAction());
        menuEdit->addSeparator();
        menuEdit->addAction(actionBold);
        menuEdit->addAction(actionItalic);
        menuEdit->addAction(actionUnderlined);
        menuEdit->addAction(actionStrikethrough);
        menuAlign->addAction(actionLeft);
        menuAlign->addAction(actionCenter);
        menuAlign->addAction(actionRight);
        menuAlign->addAction(actionJustified);
        menuUsers->addAction(actionApplyUsersColors);
        menuUsers->addAction(actionApplyTextColors);

        retranslateUi(GUI_EditWindow);

        QMetaObject::connectSlotsByName(GUI_EditWindow);
    } // setupUi

    void retranslateUi(QMainWindow *GUI_EditWindow)
    {
        GUI_EditWindow->setWindowTitle(QApplication::translate("GUI_EditWindow", "GIMPdocs - Editor", nullptr));
        closeDocumentAction->setText(QApplication::translate("GUI_EditWindow", "Close document", nullptr));
        actionCopy->setText(QApplication::translate("GUI_EditWindow", "Copy", nullptr));
        actionCut->setText(QApplication::translate("GUI_EditWindow", "Cut", nullptr));
        actionPaste->setText(QApplication::translate("GUI_EditWindow", "Paste", nullptr));
        getURIAction->setText(QApplication::translate("GUI_EditWindow", "Get URI", nullptr));
        actionUndo->setText(QApplication::translate("GUI_EditWindow", "Undo", nullptr));
        actionRedo->setText(QApplication::translate("GUI_EditWindow", "Redo", nullptr));
        actionLeft->setText(QApplication::translate("GUI_EditWindow", "Left", nullptr));
        actionCenter->setText(QApplication::translate("GUI_EditWindow", "Center", nullptr));
        actionRight->setText(QApplication::translate("GUI_EditWindow", "Right", nullptr));
        actionJustified->setText(QApplication::translate("GUI_EditWindow", "Justified", nullptr));
        actionItalic->setText(QApplication::translate("GUI_EditWindow", "Italic", nullptr));
        actionBold->setText(QApplication::translate("GUI_EditWindow", "Bold", nullptr));
        actionUnderlined->setText(QApplication::translate("GUI_EditWindow", "Underlined", nullptr));
        actionStrikethrough->setText(QApplication::translate("GUI_EditWindow", "Strikethrough", nullptr));
        actionApplyUsersColors->setText(QApplication::translate("GUI_EditWindow", "Apply users colors", nullptr));
        actionApplyTextColors->setText(QApplication::translate("GUI_EditWindow", "Apply text colors", nullptr));
        exportPDFAction->setText(QApplication::translate("GUI_EditWindow", "Export to PDF", nullptr));
        menuFile->setTitle(QApplication::translate("GUI_EditWindow", "File", nullptr));
        menuEdit->setTitle(QApplication::translate("GUI_EditWindow", "Edit", nullptr));
        menuAlign->setTitle(QApplication::translate("GUI_EditWindow", "Align", nullptr));
        menuUsers->setTitle(QApplication::translate("GUI_EditWindow", "Users", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GUI_EditWindow: public Ui_GUI_EditWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_EDITORWINDOW_H
