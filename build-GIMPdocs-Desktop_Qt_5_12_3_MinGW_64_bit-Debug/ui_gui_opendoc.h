/********************************************************************************
** Form generated from reading UI file 'gui_opendoc.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_OPENDOC_H
#define UI_GUI_OPENDOC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GUI_Opendoc
{
public:
    QGridLayout *gridLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_3;
    QPushButton *openDocsPushButton;
    QPushButton *getURIPushButton;
    QPushButton *exportPDFPushButton;
    QSpacerItem *verticalSpacer;
    QPushButton *forgetPushButton;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer_2;
    QListWidget *docsListWidget;

    void setupUi(QWidget *GUI_Opendoc)
    {
        if (GUI_Opendoc->objectName().isEmpty())
            GUI_Opendoc->setObjectName(QString::fromUtf8("GUI_Opendoc"));
        GUI_Opendoc->resize(485, 382);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GUI_Opendoc->sizePolicy().hasHeightForWidth());
        GUI_Opendoc->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(GUI_Opendoc);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, -1, 0, -1);
        widget = new QWidget(GUI_Opendoc);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(10);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_3 = new QSpacerItem(20, 85, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        openDocsPushButton = new QPushButton(widget);
        openDocsPushButton->setObjectName(QString::fromUtf8("openDocsPushButton"));

        verticalLayout->addWidget(openDocsPushButton);

        getURIPushButton = new QPushButton(widget);
        getURIPushButton->setObjectName(QString::fromUtf8("getURIPushButton"));

        verticalLayout->addWidget(getURIPushButton);

        exportPDFPushButton = new QPushButton(widget);
        exportPDFPushButton->setObjectName(QString::fromUtf8("exportPDFPushButton"));

        verticalLayout->addWidget(exportPDFPushButton);

        verticalSpacer = new QSpacerItem(20, 86, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        forgetPushButton = new QPushButton(widget);
        forgetPushButton->setObjectName(QString::fromUtf8("forgetPushButton"));

        verticalLayout->addWidget(forgetPushButton);

        verticalSpacer_2 = new QSpacerItem(20, 85, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        horizontalLayout->addLayout(verticalLayout);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout->addWidget(widget, 0, 1, 1, 1);

        docsListWidget = new QListWidget(GUI_Opendoc);
        docsListWidget->setObjectName(QString::fromUtf8("docsListWidget"));
        docsListWidget->setStyleSheet(QString::fromUtf8("QListWidget{\n"
"    border-width: 2px;\n"
"	border-style: inset;\n"
"	border-color: hsv(165, 55, 205);\n"
"}\n"
"\n"
"QListWidget:focus{\n"
"	border-color: hsv(165, 105, 205);\n"
"}"));
        docsListWidget->setSpacing(1);

        gridLayout->addWidget(docsListWidget, 0, 0, 6, 1);

        gridLayout->setColumnStretch(0, 3);
        gridLayout->setColumnStretch(1, 1);

        retranslateUi(GUI_Opendoc);

        QMetaObject::connectSlotsByName(GUI_Opendoc);
    } // setupUi

    void retranslateUi(QWidget *GUI_Opendoc)
    {
        GUI_Opendoc->setWindowTitle(QApplication::translate("GUI_Opendoc", "Form", nullptr));
        openDocsPushButton->setText(QApplication::translate("GUI_Opendoc", "Open", nullptr));
        getURIPushButton->setText(QApplication::translate("GUI_Opendoc", "Get URI", nullptr));
        exportPDFPushButton->setText(QApplication::translate("GUI_Opendoc", "Export PDF", nullptr));
        forgetPushButton->setText(QApplication::translate("GUI_Opendoc", "Forget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GUI_Opendoc: public Ui_GUI_Opendoc {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_OPENDOC_H
