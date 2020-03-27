/********************************************************************************
** Form generated from reading UI file 'gui_editor.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_EDITOR_H
#define UI_GUI_EDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GUI_Editor
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *toolsBarWidget;
    QHBoxLayout *horizontalLayout_5;
    QWidget *toolsBarShadow;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QWidget *widget_3;
    QGridLayout *gridLayout;
    QWidget *widget_6;
    QWidget *widget_2;
    QWidget *textWidget;
    QGridLayout *gridLayout_2;
    QWidget *widget_4;
    QWidget *widget_5;
    QWidget *widget;
    QWidget *widget_7;
    QWidget *widget_8;
    QWidget *widget_9;
    QSpacerItem *horizontalSpacer_2;
    QWidget *usersBarShadow;
    QHBoxLayout *horizontalLayout_4;
    QWidget *usersBarWidget;
    QHBoxLayout *horizontalLayout_2;

    void setupUi(QWidget *GUI_Editor)
    {
        if (GUI_Editor->objectName().isEmpty())
            GUI_Editor->setObjectName(QString::fromUtf8("GUI_Editor"));
        GUI_Editor->resize(565, 393);
        GUI_Editor->setStyleSheet(QString::fromUtf8("#toolsBarShadow{\n"
"	background-color: qlineargradient(spread:reflect, x1:0.5, y1:0, x2:0.5, y2:1, stop:0 rgba(25, 30, 28, 120), stop:1 rgba(0, 0, 0, 0));\n"
"}\n"
"\n"
"#usersBarShadow{\n"
"background-color: qlineargradient(spread:reflect, x1:0.5, y1:1, x2:0.5, y2:0, stop:0 rgba(25, 30, 28, 120), stop:1 rgba(0, 0, 0, 0));\n"
"}"));
        verticalLayout = new QVBoxLayout(GUI_Editor);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        toolsBarWidget = new QWidget(GUI_Editor);
        toolsBarWidget->setObjectName(QString::fromUtf8("toolsBarWidget"));
        horizontalLayout_5 = new QHBoxLayout(toolsBarWidget);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);

        verticalLayout->addWidget(toolsBarWidget);

        toolsBarShadow = new QWidget(GUI_Editor);
        toolsBarShadow->setObjectName(QString::fromUtf8("toolsBarShadow"));
        horizontalLayout_3 = new QHBoxLayout(toolsBarShadow);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);

        verticalLayout->addWidget(toolsBarShadow);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        widget_3 = new QWidget(GUI_Editor);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        gridLayout = new QGridLayout(widget_3);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widget_6 = new QWidget(widget_3);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        widget_6->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:reflect, x1:0.5, y1:1, x2:0.5, y2:0, stop:0 rgba(25, 30, 28, 120), stop:1 rgba(0, 0, 0, 0));"));

        gridLayout->addWidget(widget_6, 0, 1, 1, 1);

        widget_2 = new QWidget(widget_3);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:reflect, x1:1, y1:0.5, x2:0, y2:0.5, stop:0 rgba(25, 30, 28, 120), stop:1 rgba(0, 0, 0, 0));"));

        gridLayout->addWidget(widget_2, 1, 0, 1, 1);

        textWidget = new QWidget(widget_3);
        textWidget->setObjectName(QString::fromUtf8("textWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(textWidget->sizePolicy().hasHeightForWidth());
        textWidget->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(textWidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);

        gridLayout->addWidget(textWidget, 1, 1, 1, 1);

        widget_4 = new QWidget(widget_3);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:reflect, x1:0, y1:0.5, x2:1, y2:0.5, stop:0 rgba(25, 30, 28, 120), stop:1 rgba(0, 0, 0, 0));"));

        gridLayout->addWidget(widget_4, 1, 2, 1, 1);

        widget_5 = new QWidget(widget_3);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        widget_5->setStyleSheet(QString::fromUtf8("background-color: qradialgradient(spread:reflect, cx:0.5, cy:0, radius:1.6, fx:0.5, fy:0, stop:0 rgba(25, 30, 28, 120), stop:1 rgba(0, 0, 0, 0));"));

        gridLayout->addWidget(widget_5, 2, 1, 1, 1);

        widget = new QWidget(widget_3);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setStyleSheet(QString::fromUtf8("background-color: qradialgradient(spread:reflect, cx:1, cy:1, radius:1.5, fx:1, fy:1, stop:0 rgba(25, 30, 28, 120), stop:0.6 rgba(0, 0, 0, 0));"));

        gridLayout->addWidget(widget, 0, 0, 1, 1);

        widget_7 = new QWidget(widget_3);
        widget_7->setObjectName(QString::fromUtf8("widget_7"));
        widget_7->setStyleSheet(QString::fromUtf8("background-color: qradialgradient(spread:reflect, cx:0, cy:1, radius:1.5, fx:0, fy:1, stop:0 rgba(25, 30, 28, 120), stop:0.6 rgba(0, 0, 0, 0));"));

        gridLayout->addWidget(widget_7, 0, 2, 1, 1);

        widget_8 = new QWidget(widget_3);
        widget_8->setObjectName(QString::fromUtf8("widget_8"));
        widget_8->setStyleSheet(QString::fromUtf8("background-color: qradialgradient(spread:reflect, cx:1, cy:0, radius:1.5, fx:1, fy:0, stop:0 rgba(25, 30, 28, 120), stop:0.6 rgba(0, 0, 0, 0));"));

        gridLayout->addWidget(widget_8, 2, 0, 1, 1);

        widget_9 = new QWidget(widget_3);
        widget_9->setObjectName(QString::fromUtf8("widget_9"));
        widget_9->setStyleSheet(QString::fromUtf8("background-color: qradialgradient(spread:reflect, cx:0, cy:0, radius:1.5, fx:0, fy:0, stop:0 rgba(25, 30, 28, 120), stop:0.6 rgba(0, 0, 0, 0));"));

        gridLayout->addWidget(widget_9, 2, 2, 1, 1);

        gridLayout->setRowStretch(0, 1);
        gridLayout->setRowStretch(1, 120);
        gridLayout->setRowStretch(2, 1);
        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 120);
        gridLayout->setColumnStretch(2, 1);

        horizontalLayout->addWidget(widget_3);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        horizontalLayout->setStretch(0, 4);
        horizontalLayout->setStretch(1, 7);
        horizontalLayout->setStretch(2, 4);

        verticalLayout->addLayout(horizontalLayout);

        usersBarShadow = new QWidget(GUI_Editor);
        usersBarShadow->setObjectName(QString::fromUtf8("usersBarShadow"));
        horizontalLayout_4 = new QHBoxLayout(usersBarShadow);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, 0, 0, 0);

        verticalLayout->addWidget(usersBarShadow);

        usersBarWidget = new QWidget(GUI_Editor);
        usersBarWidget->setObjectName(QString::fromUtf8("usersBarWidget"));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush1(QColor(180, 180, 180, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        usersBarWidget->setPalette(palette);
        usersBarWidget->setAutoFillBackground(true);
        horizontalLayout_2 = new QHBoxLayout(usersBarWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);

        verticalLayout->addWidget(usersBarWidget);

        verticalLayout->setStretch(0, 7);
        verticalLayout->setStretch(1, 1);
        verticalLayout->setStretch(2, 80);
        verticalLayout->setStretch(3, 1);

        retranslateUi(GUI_Editor);

        QMetaObject::connectSlotsByName(GUI_Editor);
    } // setupUi

    void retranslateUi(QWidget *GUI_Editor)
    {
        GUI_Editor->setWindowTitle(QApplication::translate("GUI_Editor", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GUI_Editor: public Ui_GUI_Editor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_EDITOR_H
