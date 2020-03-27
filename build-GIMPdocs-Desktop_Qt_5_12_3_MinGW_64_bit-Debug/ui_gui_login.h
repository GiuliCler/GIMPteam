/********************************************************************************
** Form generated from reading UI file 'gui_login.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_LOGIN_H
#define UI_GUI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GUI_Login
{
public:
    QGridLayout *gridLayout;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_5;
    QLineEdit *usernameLineEdit;
    QLineEdit *passwordLineEdit;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_7;
    QLabel *titleLabel;
    QSpacerItem *horizontalSpacer_8;
    QLabel *label;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout;
    QPushButton *loginButton;
    QSpacerItem *verticalSpacer;
    QPushButton *newAccountButton;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *GUI_Login)
    {
        if (GUI_Login->objectName().isEmpty())
            GUI_Login->setObjectName(QString::fromUtf8("GUI_Login"));
        GUI_Login->resize(623, 407);
        GUI_Login->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	min-height: 25px;\n"
"	min-width: 75px;\n"
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
"	background-color: hsv(165, 55, 220);\n"
"}\n"
"\n"
"QLineEdit{\n"
"    border-width: 2px;\n"
"	border-style: inset;\n"
"	border-color: hsv(165, 55, 205);\n"
"}\n"
"\n"
"QLineEdit:focus{\n"
"	border-color: hsv(165, 105, 205);\n"
"}"));
        gridLayout = new QGridLayout(GUI_Login);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setVerticalSpacing(10);
        label_2 = new QLabel(GUI_Login);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setCursor(QCursor(Qt::IBeamCursor));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_2->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);

        gridLayout->addWidget(label_2, 4, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(109, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 4, 0, 1, 1);

        usernameLineEdit = new QLineEdit(GUI_Login);
        usernameLineEdit->setObjectName(QString::fromUtf8("usernameLineEdit"));
        usernameLineEdit->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(usernameLineEdit, 3, 2, 1, 1);

        passwordLineEdit = new QLineEdit(GUI_Login);
        passwordLineEdit->setObjectName(QString::fromUtf8("passwordLineEdit"));
        passwordLineEdit->setMinimumSize(QSize(0, 25));
        passwordLineEdit->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(passwordLineEdit, 4, 2, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(164, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 3, 3, 2, 1);

        verticalSpacer_2 = new QSpacerItem(20, 60, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 0, 2, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_7);

        titleLabel = new QLabel(GUI_Login);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setCursor(QCursor(Qt::IBeamCursor));
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);

        horizontalLayout_3->addWidget(titleLabel);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_8);


        gridLayout->addLayout(horizontalLayout_3, 1, 2, 1, 1);

        label = new QLabel(GUI_Login);
        label->setObjectName(QString::fromUtf8("label"));
        label->setCursor(QCursor(Qt::IBeamCursor));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);

        gridLayout->addWidget(label, 3, 1, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 60, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 6, 2, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 61, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_4, 2, 2, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        loginButton = new QPushButton(GUI_Login);
        loginButton->setObjectName(QString::fromUtf8("loginButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(loginButton->sizePolicy().hasHeightForWidth());
        loginButton->setSizePolicy(sizePolicy);
        loginButton->setAutoDefault(true);

        verticalLayout->addWidget(loginButton);

        verticalSpacer = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        newAccountButton = new QPushButton(GUI_Login);
        newAccountButton->setObjectName(QString::fromUtf8("newAccountButton"));

        verticalLayout->addWidget(newAccountButton);


        horizontalLayout->addLayout(verticalLayout);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        gridLayout->addLayout(horizontalLayout, 5, 2, 1, 1);

        gridLayout->setRowStretch(0, 2);
        gridLayout->setRowStretch(2, 3);
        gridLayout->setRowStretch(6, 4);
        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 1);
        gridLayout->setColumnStretch(3, 2);

        retranslateUi(GUI_Login);

        loginButton->setDefault(true);


        QMetaObject::connectSlotsByName(GUI_Login);
    } // setupUi

    void retranslateUi(QWidget *GUI_Login)
    {
        GUI_Login->setWindowTitle(QApplication::translate("GUI_Login", "Form", nullptr));
        label_2->setText(QApplication::translate("GUI_Login", "Password", nullptr));
        usernameLineEdit->setText(QApplication::translate("GUI_Login", "I'm", nullptr));
        passwordLineEdit->setText(QApplication::translate("GUI_Login", "lazy", nullptr));
        titleLabel->setText(QApplication::translate("GUI_Login", "GIMPdocs", nullptr));
        label->setText(QApplication::translate("GUI_Login", "Username", nullptr));
        loginButton->setText(QApplication::translate("GUI_Login", "Log in", nullptr));
        newAccountButton->setText(QApplication::translate("GUI_Login", "New account", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GUI_Login: public Ui_GUI_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_LOGIN_H
