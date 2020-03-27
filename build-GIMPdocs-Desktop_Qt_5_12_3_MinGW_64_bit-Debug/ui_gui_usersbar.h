/********************************************************************************
** Form generated from reading UI file 'gui_usersbar.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_USERSBAR_H
#define UI_GUI_USERSBAR_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GUI_UsersBar
{
public:
    QHBoxLayout *horizontalLayout_4;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_5;
    QWidget *onlineUsersWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *numberOnlineUsersLabel;
    QWidget *onlineIgnoredWrapper;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_5;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_6;
    QFrame *line_1;
    QWidget *contributorsWidget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_2;
    QPushButton *showColorsPushButton;
    QPushButton *hideColorsPushButton;
    QSpacerItem *verticalSpacer;
    QWidget *contributorUsersWidget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLabel *numberContributorUsersLabel;
    QWidget *contributorsIgnoredWrapper;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QGridLayout *gridLayout;
    QPushButton *pushButton_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_4;

    void setupUi(QWidget *GUI_UsersBar)
    {
        if (GUI_UsersBar->objectName().isEmpty())
            GUI_UsersBar->setObjectName(QString::fromUtf8("GUI_UsersBar"));
        GUI_UsersBar->resize(759, 90);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GUI_UsersBar->sizePolicy().hasHeightForWidth());
        GUI_UsersBar->setSizePolicy(sizePolicy);
        GUI_UsersBar->setStyleSheet(QString::fromUtf8("QWidget#widget{\n"
"	background-color: qlineargradient(spread:reflect, x1:0.5, y1:0, x2:0.5, y2:0.50, stop:0 rgba(207, 245, 236, 255), stop:0.20 rgba(215, 255, 245, 255), stop:1 rgba(230, 255, 249, 255));\n"
"}\n"
"\n"
"#line_1{\n"
"background-color: rgb(203, 240, 251);\n"
"}\n"
"\n"
"QPushButton {\n"
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
""));
        horizontalLayout_4 = new QHBoxLayout(GUI_UsersBar);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(GUI_UsersBar);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout_5 = new QHBoxLayout(widget);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        onlineUsersWidget = new QWidget(widget);
        onlineUsersWidget->setObjectName(QString::fromUtf8("onlineUsersWidget"));
        horizontalLayout_2 = new QHBoxLayout(onlineUsersWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 0, 0, 0);
        label = new QLabel(onlineUsersWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setCursor(QCursor(Qt::IBeamCursor));
        label->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);

        horizontalLayout_2->addWidget(label);

        numberOnlineUsersLabel = new QLabel(onlineUsersWidget);
        numberOnlineUsersLabel->setObjectName(QString::fromUtf8("numberOnlineUsersLabel"));
        numberOnlineUsersLabel->setMinimumSize(QSize(14, 0));
        numberOnlineUsersLabel->setCursor(QCursor(Qt::IBeamCursor));
        numberOnlineUsersLabel->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);

        horizontalLayout_2->addWidget(numberOnlineUsersLabel);

        onlineIgnoredWrapper = new QWidget(onlineUsersWidget);
        onlineIgnoredWrapper->setObjectName(QString::fromUtf8("onlineIgnoredWrapper"));
        sizePolicy.setHeightForWidth(onlineIgnoredWrapper->sizePolicy().hasHeightForWidth());
        onlineIgnoredWrapper->setSizePolicy(sizePolicy);
        horizontalLayout_7 = new QHBoxLayout(onlineIgnoredWrapper);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);

        horizontalLayout_2->addWidget(onlineIgnoredWrapper);

        horizontalSpacer_5 = new QSpacerItem(29, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);


        horizontalLayout_5->addWidget(onlineUsersWidget);

        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_6 = new QHBoxLayout(widget_2);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 5, 0, 5);
        line_1 = new QFrame(widget_2);
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
        line_1->setLineWidth(2);
        line_1->setFrameShape(QFrame::VLine);

        horizontalLayout_6->addWidget(line_1);


        horizontalLayout_5->addWidget(widget_2);

        contributorsWidget = new QWidget(widget);
        contributorsWidget->setObjectName(QString::fromUtf8("contributorsWidget"));
        horizontalLayout = new QHBoxLayout(contributorsWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget_3 = new QWidget(contributorsWidget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        verticalLayout_2 = new QVBoxLayout(widget_3);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_2 = new QSpacerItem(20, 1, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout_2->addItem(verticalSpacer_2);

        showColorsPushButton = new QPushButton(widget_3);
        showColorsPushButton->setObjectName(QString::fromUtf8("showColorsPushButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(showColorsPushButton->sizePolicy().hasHeightForWidth());
        showColorsPushButton->setSizePolicy(sizePolicy2);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/editor/text_editor/ShowColors.png"), QSize(), QIcon::Normal, QIcon::Off);
        showColorsPushButton->setIcon(icon);
        showColorsPushButton->setIconSize(QSize(32, 30));

        verticalLayout_2->addWidget(showColorsPushButton);

        hideColorsPushButton = new QPushButton(widget_3);
        hideColorsPushButton->setObjectName(QString::fromUtf8("hideColorsPushButton"));
        sizePolicy2.setHeightForWidth(hideColorsPushButton->sizePolicy().hasHeightForWidth());
        hideColorsPushButton->setSizePolicy(sizePolicy2);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/editor/text_editor/TextColor.svg"), QSize(), QIcon::Normal, QIcon::Off);
        hideColorsPushButton->setIcon(icon1);
        hideColorsPushButton->setIconSize(QSize(32, 30));

        verticalLayout_2->addWidget(hideColorsPushButton);

        verticalSpacer = new QSpacerItem(20, 1, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout->addWidget(widget_3);

        contributorUsersWidget = new QWidget(contributorsWidget);
        contributorUsersWidget->setObjectName(QString::fromUtf8("contributorUsersWidget"));
        horizontalLayout_3 = new QHBoxLayout(contributorUsersWidget);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(contributorUsersWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setCursor(QCursor(Qt::IBeamCursor));
        label_2->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);

        horizontalLayout_3->addWidget(label_2);

        numberContributorUsersLabel = new QLabel(contributorUsersWidget);
        numberContributorUsersLabel->setObjectName(QString::fromUtf8("numberContributorUsersLabel"));
        numberContributorUsersLabel->setMinimumSize(QSize(14, 0));
        numberContributorUsersLabel->setCursor(QCursor(Qt::IBeamCursor));
        numberContributorUsersLabel->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);

        horizontalLayout_3->addWidget(numberContributorUsersLabel);

        contributorsIgnoredWrapper = new QWidget(contributorUsersWidget);
        contributorsIgnoredWrapper->setObjectName(QString::fromUtf8("contributorsIgnoredWrapper"));
        horizontalLayout_8 = new QHBoxLayout(contributorsIgnoredWrapper);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);

        horizontalLayout_3->addWidget(contributorsIgnoredWrapper);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        horizontalLayout->addWidget(contributorUsersWidget);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        horizontalLayout_5->addWidget(contributorsWidget);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(-1, -1, 0, -1);
        pushButton_3 = new QPushButton(widget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 1, 0, 1, 1);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setEnabled(true);

        gridLayout->addWidget(pushButton, 0, 0, 1, 1);

        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 0, 1, 1, 1);

        pushButton_4 = new QPushButton(widget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        gridLayout->addWidget(pushButton_4, 1, 1, 1, 1);


        horizontalLayout_5->addLayout(gridLayout);

        horizontalLayout_5->setStretch(0, 1);
        horizontalLayout_5->setStretch(2, 1);

        horizontalLayout_4->addWidget(widget);


        retranslateUi(GUI_UsersBar);

        QMetaObject::connectSlotsByName(GUI_UsersBar);
    } // setupUi

    void retranslateUi(QWidget *GUI_UsersBar)
    {
        label->setText(QApplication::translate("GUI_UsersBar", "Online users:", nullptr));
        numberOnlineUsersLabel->setText(QApplication::translate("GUI_UsersBar", "0", nullptr));
#ifndef QT_NO_TOOLTIP
        showColorsPushButton->setToolTip(QApplication::translate("GUI_UsersBar", "Apply users colors", nullptr));
#endif // QT_NO_TOOLTIP
        showColorsPushButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        hideColorsPushButton->setToolTip(QApplication::translate("GUI_UsersBar", "Apply text colors", nullptr));
#endif // QT_NO_TOOLTIP
        hideColorsPushButton->setText(QString());
        label_2->setText(QApplication::translate("GUI_UsersBar", "Contributors:", nullptr));
        numberContributorUsersLabel->setText(QApplication::translate("GUI_UsersBar", "0", nullptr));
        pushButton_3->setText(QApplication::translate("GUI_UsersBar", "Add contributor", nullptr));
        pushButton->setText(QApplication::translate("GUI_UsersBar", "Add User", nullptr));
        pushButton_2->setText(QApplication::translate("GUI_UsersBar", "Remove User", nullptr));
        pushButton_4->setText(QApplication::translate("GUI_UsersBar", "Remove contributor", nullptr));
        Q_UNUSED(GUI_UsersBar);
    } // retranslateUi

};

namespace Ui {
    class GUI_UsersBar: public Ui_GUI_UsersBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_USERSBAR_H
