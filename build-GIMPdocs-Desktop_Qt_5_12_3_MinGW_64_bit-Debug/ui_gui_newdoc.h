/********************************************************************************
** Form generated from reading UI file 'gui_newdoc.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_NEWDOC_H
#define UI_GUI_NEWDOC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GUI_Newdoc
{
public:
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QLabel *newDocumentTitleLabel;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *nameLineEdit;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *createPushButton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_3;
    QFrame *line_1;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_4;
    QLabel *uriDocumentTitleLabel;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *URILineEdit;
    QPushButton *openURIPushButton;
    QSpacerItem *verticalSpacer_4;

    void setupUi(QWidget *GUI_Newdoc)
    {
        if (GUI_Newdoc->objectName().isEmpty())
            GUI_Newdoc->setObjectName(QString::fromUtf8("GUI_Newdoc"));
        GUI_Newdoc->resize(572, 338);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GUI_Newdoc->sizePolicy().hasHeightForWidth());
        GUI_Newdoc->setSizePolicy(sizePolicy);
        GUI_Newdoc->setStyleSheet(QString::fromUtf8("#line_1{\n"
"background-color: rgb(203, 240, 251);\n"
"}"));
        verticalLayout_4 = new QVBoxLayout(GUI_Newdoc);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 0, -1, -1);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        newDocumentTitleLabel = new QLabel(GUI_Newdoc);
        newDocumentTitleLabel->setObjectName(QString::fromUtf8("newDocumentTitleLabel"));
        newDocumentTitleLabel->setCursor(QCursor(Qt::IBeamCursor));

        horizontalLayout_3->addWidget(newDocumentTitleLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer_2 = new QSpacerItem(20, 43, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(GUI_Newdoc);
        label->setObjectName(QString::fromUtf8("label"));
        label->setCursor(QCursor(Qt::IBeamCursor));
        label->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);

        horizontalLayout->addWidget(label);

        nameLineEdit = new QLineEdit(GUI_Newdoc);
        nameLineEdit->setObjectName(QString::fromUtf8("nameLineEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(nameLineEdit->sizePolicy().hasHeightForWidth());
        nameLineEdit->setSizePolicy(sizePolicy1);
        nameLineEdit->setMinimumSize(QSize(0, 25));

        horizontalLayout->addWidget(nameLineEdit);

        horizontalSpacer_3 = new QSpacerItem(36, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        createPushButton = new QPushButton(GUI_Newdoc);
        createPushButton->setObjectName(QString::fromUtf8("createPushButton"));

        horizontalLayout->addWidget(createPushButton);

        horizontalSpacer_2 = new QSpacerItem(156, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_3 = new QSpacerItem(20, 225, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(2, 1);
        verticalLayout->setStretch(4, 2);

        verticalLayout_4->addLayout(verticalLayout);

        line_1 = new QFrame(GUI_Newdoc);
        line_1->setObjectName(QString::fromUtf8("line_1"));
        QPalette palette;
        QBrush brush(QColor(169, 200, 192, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(203, 240, 251, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        QBrush brush2(QColor(120, 120, 120, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        line_1->setPalette(palette);
        line_1->setFrameShadow(QFrame::Plain);
        line_1->setFrameShape(QFrame::HLine);

        verticalLayout_4->addWidget(line_1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(10);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(-1, 0, -1, -1);
        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        uriDocumentTitleLabel = new QLabel(GUI_Newdoc);
        uriDocumentTitleLabel->setObjectName(QString::fromUtf8("uriDocumentTitleLabel"));
        uriDocumentTitleLabel->setCursor(QCursor(Qt::IBeamCursor));

        horizontalLayout_4->addWidget(uriDocumentTitleLabel);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        URILineEdit = new QLineEdit(GUI_Newdoc);
        URILineEdit->setObjectName(QString::fromUtf8("URILineEdit"));
        URILineEdit->setMinimumSize(QSize(0, 25));

        horizontalLayout_2->addWidget(URILineEdit);

        openURIPushButton = new QPushButton(GUI_Newdoc);
        openURIPushButton->setObjectName(QString::fromUtf8("openURIPushButton"));

        horizontalLayout_2->addWidget(openURIPushButton);


        verticalLayout_3->addLayout(horizontalLayout_2);

        verticalSpacer_4 = new QSpacerItem(20, 38, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_4);

        verticalLayout_3->setStretch(0, 1);
        verticalLayout_3->setStretch(3, 3);

        verticalLayout_4->addLayout(verticalLayout_3);

        verticalLayout_4->setStretch(0, 1);
        verticalLayout_4->setStretch(1, 1);
        verticalLayout_4->setStretch(2, 1);

        retranslateUi(GUI_Newdoc);

        QMetaObject::connectSlotsByName(GUI_Newdoc);
    } // setupUi

    void retranslateUi(QWidget *GUI_Newdoc)
    {
        GUI_Newdoc->setWindowTitle(QApplication::translate("GUI_Newdoc", "Form", nullptr));
        newDocumentTitleLabel->setText(QApplication::translate("GUI_Newdoc", "Create a new document from scratch", nullptr));
        label->setText(QApplication::translate("GUI_Newdoc", "Document name", nullptr));
        nameLineEdit->setText(QApplication::translate("GUI_Newdoc", "Default", nullptr));
        createPushButton->setText(QApplication::translate("GUI_Newdoc", "Create", nullptr));
        uriDocumentTitleLabel->setText(QApplication::translate("GUI_Newdoc", "Access existing document with URI", nullptr));
        URILineEdit->setPlaceholderText(QApplication::translate("GUI_Newdoc", "Insert the URI here", nullptr));
        openURIPushButton->setText(QApplication::translate("GUI_Newdoc", "Open", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GUI_Newdoc: public Ui_GUI_Newdoc {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_NEWDOC_H
