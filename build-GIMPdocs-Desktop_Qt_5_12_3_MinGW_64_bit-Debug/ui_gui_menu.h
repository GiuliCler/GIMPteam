/********************************************************************************
** Form generated from reading UI file 'gui_menu.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_MENU_H
#define UI_GUI_MENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GUI_Menu
{
public:
    QGridLayout *gridLayout;
    QGroupBox *userGroupBox;
    QHBoxLayout *horizontalLayout;
    QLabel *iconLabel;
    QLabel *nicknameLabel;
    QSpacerItem *horizontalSpacer;
    QPushButton *editPushButton;
    QPushButton *logoutPushButton;
    QGroupBox *documentGroupBox;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *opendocTab;
    QGridLayout *gridLayout_2;
    QWidget *newdocTab;
    QGridLayout *gridLayout_3;

    void setupUi(QWidget *GUI_Menu)
    {
        if (GUI_Menu->objectName().isEmpty())
            GUI_Menu->setObjectName(QString::fromUtf8("GUI_Menu"));
        GUI_Menu->resize(515, 339);
        GUI_Menu->setStyleSheet(QString::fromUtf8("QWidget#opendocTab,QWidget#newdocTab{\n"
"	background-color: qlineargradient(spread:reflect, x1:0.5, y1:0, x2:0.5, y2:0.49, stop:0 rgba(207, 245, 236, 255), stop:0.17 rgba(215, 255, 245, 255), stop:1 rgba(230, 255, 249, 255));\n"
"}\n"
"\n"
"QTabWidget::pane {\n"
"    border: 1px solid hsv(165, 55, 205);\n"
"}\n"
"\n"
"QTabBar::tab {\n"
"    border: 2px solid hsv(165, 55, 205);\n"
"    /*min-width: 8ex;*/\n"
"    padding-left: 5px;\n"
"    padding-right: 5px;\n"
"    padding-top: 2px;\n"
"    padding-bottom: 2px;\n"
"}\n"
"\n"
"QTabBar::tab:selected {\n"
"	background: rgba(207, 245, 236, 255);\n"
"    border-color: hsv(165, 55, 205);\n"
"	border-bottom: 0px;\n"
"/* make use of negative margins for overlapping tabs */\n"
"	/*margin-left: -4px;\n"
"    margin-right: -4px;*/\n"
"}\n"
"\n"
"QTabBar::tab:!selected {\n"
"	background: hsv(165, 55, 205);\n"
"    margin-top: 2px; /* make non-selected tabs look smaller */\n"
"}\n"
"\n"
"QTabBar::tab:!selected:hover {\n"
"	background: hsv(165, 55, 225);\n"
"    border-co"
                        "lor: hsv(165, 55, 225);\n"
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
"QLineEdit:focus{\n"
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
"    background-color: rg"
                        "ba(230, 255, 249, 255);\n"
"   /* border-width: 1px;\n"
"	border-style: outset;\n"
"	border-color: hsv(165, 55, 205);*/\n"
"}"));
        gridLayout = new QGridLayout(GUI_Menu);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        userGroupBox = new QGroupBox(GUI_Menu);
        userGroupBox->setObjectName(QString::fromUtf8("userGroupBox"));
        horizontalLayout = new QHBoxLayout(userGroupBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 3, -1, 3);
        iconLabel = new QLabel(userGroupBox);
        iconLabel->setObjectName(QString::fromUtf8("iconLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(iconLabel->sizePolicy().hasHeightForWidth());
        iconLabel->setSizePolicy(sizePolicy);
        iconLabel->setMaximumSize(QSize(50, 50));
        iconLabel->setPixmap(QPixmap(QString::fromUtf8(":/icon/Mew.png")));
        iconLabel->setScaledContents(true);

        horizontalLayout->addWidget(iconLabel);

        nicknameLabel = new QLabel(userGroupBox);
        nicknameLabel->setObjectName(QString::fromUtf8("nicknameLabel"));
        nicknameLabel->setCursor(QCursor(Qt::IBeamCursor));
        nicknameLabel->setAlignment(Qt::AlignCenter);
        nicknameLabel->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);

        horizontalLayout->addWidget(nicknameLabel);

        horizontalSpacer = new QSpacerItem(174, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        editPushButton = new QPushButton(userGroupBox);
        editPushButton->setObjectName(QString::fromUtf8("editPushButton"));

        horizontalLayout->addWidget(editPushButton);

        logoutPushButton = new QPushButton(userGroupBox);
        logoutPushButton->setObjectName(QString::fromUtf8("logoutPushButton"));

        horizontalLayout->addWidget(logoutPushButton);


        gridLayout->addWidget(userGroupBox, 0, 0, 1, 1);

        documentGroupBox = new QGroupBox(GUI_Menu);
        documentGroupBox->setObjectName(QString::fromUtf8("documentGroupBox"));
        verticalLayout = new QVBoxLayout(documentGroupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(documentGroupBox);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        opendocTab = new QWidget();
        opendocTab->setObjectName(QString::fromUtf8("opendocTab"));
        opendocTab->setAutoFillBackground(false);
        gridLayout_2 = new QGridLayout(opendocTab);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(-1, -1, 0, -1);
        tabWidget->addTab(opendocTab, QString());
        newdocTab = new QWidget();
        newdocTab->setObjectName(QString::fromUtf8("newdocTab"));
        newdocTab->setAutoFillBackground(false);
        gridLayout_3 = new QGridLayout(newdocTab);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        tabWidget->addTab(newdocTab, QString());

        verticalLayout->addWidget(tabWidget);


        gridLayout->addWidget(documentGroupBox, 1, 0, 1, 1);


        retranslateUi(GUI_Menu);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(GUI_Menu);
    } // setupUi

    void retranslateUi(QWidget *GUI_Menu)
    {
        GUI_Menu->setWindowTitle(QApplication::translate("GUI_Menu", "Form", nullptr));
        userGroupBox->setTitle(QApplication::translate("GUI_Menu", "User", nullptr));
        iconLabel->setText(QString());
        nicknameLabel->setText(QApplication::translate("GUI_Menu", "<nickname>", nullptr));
        editPushButton->setText(QApplication::translate("GUI_Menu", "Edit profile", nullptr));
        logoutPushButton->setText(QApplication::translate("GUI_Menu", "Log out", nullptr));
        documentGroupBox->setTitle(QApplication::translate("GUI_Menu", "Documents", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(opendocTab), QApplication::translate("GUI_Menu", "Accessible documents", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(newdocTab), QApplication::translate("GUI_Menu", "New document", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GUI_Menu: public Ui_GUI_Menu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_MENU_H
