/********************************************************************************
** Form generated from reading UI file 'gui_uri.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_URI_H
#define UI_GUI_URI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GUI_URI
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QWidget *backgroundWidget;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *URILabel;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *copyPushButton;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QDialog *GUI_URI)
    {
        if (GUI_URI->objectName().isEmpty())
            GUI_URI->setObjectName(QString::fromUtf8("GUI_URI"));
        GUI_URI->resize(301, 184);
        GUI_URI->setStyleSheet(QString::fromUtf8("QDialog{\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(122, 158, 126, 255), stop:1 rgba(198, 255, 194, 255));\n"
"}\n"
"\n"
"QWidget#backgroundWidget{\n"
"	background-color: qlineargradient(spread:reflect, x1:0.5, y1:0, x2:0.5, y2:0.49, stop:0 rgba(207, 245, 236, 255), stop:0.17 rgba(215, 255, 245, 255), stop:1 rgba(230, 255, 249, 255));\n"
"	border-width: 1px;\n"
"	border-style: solid;\n"
"	border-color: hsv(165, 55, 205);\n"
"}\n"
"\n"
"QPushButton {\n"
"	min-height: 20px;\n"
"	min-width: 65px;\n"
"	padding: 5px;	\n"
"	padding-left: 10px;\n"
"	padding-right: 10px;\n"
"    background-color: hsv(165, 55, 255);\n"
"    border-width: 1px;\n"
"	border-style: outset;\n"
"	border-color: hsv(165, 55, 205);\n"
"}\n"
"\n"
"QPushButton:hover:!pressed{\n"
"	border-color: hsv(165, 255, 255);\n"
"	border-top-color: hsv(165, 200, 255);	\n"
"	border-left-color: hsv(165, 200, 255);\n"
"}\n"
"\n"
"QPushButton:pressed,QPushButton:checked {\n"
"    border-style: inset;\n"
"	background-co"
                        "lor: hsv(165, 55, 220);\n"
"}"));
        gridLayout = new QGridLayout(GUI_URI);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(-1, 5, -1, 5);
        horizontalSpacer_2 = new QSpacerItem(89, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(94, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        backgroundWidget = new QWidget(GUI_URI);
        backgroundWidget->setObjectName(QString::fromUtf8("backgroundWidget"));
        verticalLayout_3 = new QVBoxLayout(backgroundWidget);
        verticalLayout_3->setSpacing(25);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(30, 23, 30, 18);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(25);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(backgroundWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setCursor(QCursor(Qt::IBeamCursor));
        label->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);

        verticalLayout->addWidget(label);

        URILabel = new QLabel(backgroundWidget);
        URILabel->setObjectName(QString::fromUtf8("URILabel"));
        URILabel->setCursor(QCursor(Qt::IBeamCursor));
        URILabel->setAlignment(Qt::AlignCenter);
        URILabel->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);

        verticalLayout->addWidget(URILabel);


        verticalLayout_3->addLayout(verticalLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        copyPushButton = new QPushButton(backgroundWidget);
        copyPushButton->setObjectName(QString::fromUtf8("copyPushButton"));

        horizontalLayout->addWidget(copyPushButton);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        verticalLayout_3->addLayout(horizontalLayout);


        gridLayout->addWidget(backgroundWidget, 0, 1, 1, 1);

        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 9);
        gridLayout->setColumnStretch(2, 1);

        retranslateUi(GUI_URI);

        QMetaObject::connectSlotsByName(GUI_URI);
    } // setupUi

    void retranslateUi(QDialog *GUI_URI)
    {
        GUI_URI->setWindowTitle(QApplication::translate("GUI_URI", "Dialog", nullptr));
        label->setText(QApplication::translate("GUI_URI", "Share this URI:", nullptr));
        URILabel->setText(QApplication::translate("GUI_URI", "TextLabel", nullptr));
        copyPushButton->setText(QApplication::translate("GUI_URI", "Copy URI", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GUI_URI: public Ui_GUI_URI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_URI_H
