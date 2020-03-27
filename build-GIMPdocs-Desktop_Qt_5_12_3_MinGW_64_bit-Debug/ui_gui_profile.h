/********************************************************************************
** Form generated from reading UI file 'gui_profile.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_PROFILE_H
#define UI_GUI_PROFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GUI_Profile
{
public:
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *horizontalSpacer_9;
    QWidget *backgroundWidget;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_6;
    QLabel *titleLabel;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *verticalSpacer_2;
    QGridLayout *gridLayout;
    QLabel *iconLabel;
    QHBoxLayout *horizontalLayout;
    QComboBox *iconComboBox;
    QSpacerItem *horizontalSpacer_3;
    QLabel *nicknameLabel;
    QLineEdit *nicknameLineEdit;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_4;
    QLabel *usernameLabel;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *usernameLineEdit;
    QLabel *usernameLabelReadonly;
    QLabel *passwordLabel;
    QLineEdit *passwordLineEdit;
    QLabel *repeatLabel;
    QLineEdit *repeatLineEdit;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *backPushButton;
    QPushButton *savePushButton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *verticalSpacer_7;

    void setupUi(QWidget *GUI_Profile)
    {
        if (GUI_Profile->objectName().isEmpty())
            GUI_Profile->setObjectName(QString::fromUtf8("GUI_Profile"));
        GUI_Profile->resize(512, 436);
        GUI_Profile->setStyleSheet(QString::fromUtf8("QWidget#backgroundWidget{\n"
"	background-color: qlineargradient(spread:reflect, x1:0.5, y1:0, x2:0.5, y2:0.49, stop:0 rgba(207, 245, 236, 255), stop:0.17 rgba(215, 255, 245, 255), stop:1 rgba(230, 255, 249, 255));\n"
"	border-width: 3px;\n"
"	border-style: solid;\n"
"	border-color: hsv(165, 55, 205);\n"
"}\n"
"\n"
"QPushButton {\n"
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
"QLineEdit:"
                        "focus{\n"
"	border-color: hsv(165, 105, 205);\n"
"}\n"
"\n"
"QComboBox{\n"
"	background-color: hsv(165, 55, 255);\n"
"    border-width: 1px;\n"
"	border-style: outset;\n"
"	border-color: hsv(165, 55, 205);\n"
"}\n"
"\n"
"QComboBox QAbstractItemView {\n"
"    background-color: rgba(230, 255, 249, 255);\n"
"   /* border-width: 1px;\n"
"	border-style: outset;\n"
"	border-color: hsv(165, 55, 205);*/\n"
"}"));
        gridLayout_2 = new QGridLayout(GUI_Profile);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_8, 1, 2, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_9, 1, 0, 1, 1);

        backgroundWidget = new QWidget(GUI_Profile);
        backgroundWidget->setObjectName(QString::fromUtf8("backgroundWidget"));
        verticalLayout_2 = new QVBoxLayout(backgroundWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_6);

        titleLabel = new QLabel(backgroundWidget);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setCursor(QCursor(Qt::IBeamCursor));
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);

        horizontalLayout_5->addWidget(titleLabel);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_7);


        verticalLayout_2->addLayout(horizontalLayout_5);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setVerticalSpacing(10);
        iconLabel = new QLabel(backgroundWidget);
        iconLabel->setObjectName(QString::fromUtf8("iconLabel"));
        iconLabel->setCursor(QCursor(Qt::IBeamCursor));
        iconLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        iconLabel->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);

        gridLayout->addWidget(iconLabel, 0, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        iconComboBox = new QComboBox(backgroundWidget);
        iconComboBox->setObjectName(QString::fromUtf8("iconComboBox"));
        iconComboBox->setMaxVisibleItems(4);
        iconComboBox->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(iconComboBox);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        gridLayout->addLayout(horizontalLayout, 0, 2, 1, 1);

        nicknameLabel = new QLabel(backgroundWidget);
        nicknameLabel->setObjectName(QString::fromUtf8("nicknameLabel"));
        nicknameLabel->setCursor(QCursor(Qt::IBeamCursor));
        nicknameLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        nicknameLabel->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);

        gridLayout->addWidget(nicknameLabel, 1, 1, 1, 1);

        nicknameLineEdit = new QLineEdit(backgroundWidget);
        nicknameLineEdit->setObjectName(QString::fromUtf8("nicknameLineEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(nicknameLineEdit->sizePolicy().hasHeightForWidth());
        nicknameLineEdit->setSizePolicy(sizePolicy);
        nicknameLineEdit->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(nicknameLineEdit, 1, 2, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(135, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 2, 0, 2, 1);

        horizontalSpacer_4 = new QSpacerItem(134, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 2, 3, 2, 1);

        usernameLabel = new QLabel(backgroundWidget);
        usernameLabel->setObjectName(QString::fromUtf8("usernameLabel"));
        usernameLabel->setCursor(QCursor(Qt::IBeamCursor));
        usernameLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        usernameLabel->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);

        gridLayout->addWidget(usernameLabel, 3, 1, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        usernameLineEdit = new QLineEdit(backgroundWidget);
        usernameLineEdit->setObjectName(QString::fromUtf8("usernameLineEdit"));
        usernameLineEdit->setMinimumSize(QSize(0, 25));

        horizontalLayout_3->addWidget(usernameLineEdit);

        usernameLabelReadonly = new QLabel(backgroundWidget);
        usernameLabelReadonly->setObjectName(QString::fromUtf8("usernameLabelReadonly"));
        usernameLabelReadonly->setCursor(QCursor(Qt::IBeamCursor));
        usernameLabelReadonly->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);

        horizontalLayout_3->addWidget(usernameLabelReadonly);


        gridLayout->addLayout(horizontalLayout_3, 3, 2, 1, 1);

        passwordLabel = new QLabel(backgroundWidget);
        passwordLabel->setObjectName(QString::fromUtf8("passwordLabel"));
        passwordLabel->setCursor(QCursor(Qt::IBeamCursor));
        passwordLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        passwordLabel->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);

        gridLayout->addWidget(passwordLabel, 4, 1, 1, 1);

        passwordLineEdit = new QLineEdit(backgroundWidget);
        passwordLineEdit->setObjectName(QString::fromUtf8("passwordLineEdit"));
        passwordLineEdit->setMinimumSize(QSize(0, 25));
        passwordLineEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);
        passwordLineEdit->setClearButtonEnabled(false);

        gridLayout->addWidget(passwordLineEdit, 4, 2, 1, 1);

        repeatLabel = new QLabel(backgroundWidget);
        repeatLabel->setObjectName(QString::fromUtf8("repeatLabel"));
        repeatLabel->setCursor(QCursor(Qt::IBeamCursor));
        repeatLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        repeatLabel->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);

        gridLayout->addWidget(repeatLabel, 5, 1, 1, 1);

        repeatLineEdit = new QLineEdit(backgroundWidget);
        repeatLineEdit->setObjectName(QString::fromUtf8("repeatLineEdit"));
        repeatLineEdit->setMinimumSize(QSize(0, 25));
        repeatLineEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);

        gridLayout->addWidget(repeatLineEdit, 5, 2, 1, 1);

        verticalSpacer_5 = new QSpacerItem(82, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_5, 2, 2, 1, 1);

        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 1);
        gridLayout->setColumnStretch(3, 2);
        gridLayout->setColumnMinimumWidth(2, 250);

        verticalLayout_2->addLayout(gridLayout);

        verticalSpacer = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        backPushButton = new QPushButton(backgroundWidget);
        backPushButton->setObjectName(QString::fromUtf8("backPushButton"));
        backPushButton->setEnabled(true);
        backPushButton->setCheckable(false);

        horizontalLayout_2->addWidget(backPushButton);

        savePushButton = new QPushButton(backgroundWidget);
        savePushButton->setObjectName(QString::fromUtf8("savePushButton"));

        horizontalLayout_2->addWidget(savePushButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_4);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(2, 3);
        verticalLayout_2->setStretch(4, 2);
        verticalLayout_2->setStretch(6, 1);

        gridLayout_2->addWidget(backgroundWidget, 1, 1, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_6, 2, 1, 1, 1);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_7, 0, 1, 1, 1);

        gridLayout_2->setRowStretch(0, 1);
        gridLayout_2->setRowStretch(1, 100);
        gridLayout_2->setRowStretch(2, 1);
        gridLayout_2->setColumnStretch(0, 1);
        gridLayout_2->setColumnStretch(1, 4);
        gridLayout_2->setColumnStretch(2, 1);

        retranslateUi(GUI_Profile);

        savePushButton->setDefault(true);


        QMetaObject::connectSlotsByName(GUI_Profile);
    } // setupUi

    void retranslateUi(QWidget *GUI_Profile)
    {
        GUI_Profile->setWindowTitle(QApplication::translate("GUI_Profile", "Form", nullptr));
        titleLabel->setText(QApplication::translate("GUI_Profile", "User profile", nullptr));
        iconLabel->setText(QApplication::translate("GUI_Profile", "Icon:", nullptr));
        nicknameLabel->setText(QApplication::translate("GUI_Profile", "Nickname:", nullptr));
        usernameLabel->setText(QApplication::translate("GUI_Profile", "Username:", nullptr));
        usernameLabelReadonly->setText(QApplication::translate("GUI_Profile", "/Readonly", nullptr));
        passwordLabel->setText(QApplication::translate("GUI_Profile", "Password:", nullptr));
        repeatLabel->setText(QApplication::translate("GUI_Profile", "Repeat password:", nullptr));
        backPushButton->setText(QApplication::translate("GUI_Profile", "Back", nullptr));
        savePushButton->setText(QApplication::translate("GUI_Profile", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GUI_Profile: public Ui_GUI_Profile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_PROFILE_H
