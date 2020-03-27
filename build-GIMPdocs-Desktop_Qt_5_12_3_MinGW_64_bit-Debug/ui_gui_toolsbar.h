/********************************************************************************
** Form generated from reading UI file 'gui_toolsbar.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_TOOLSBAR_H
#define UI_GUI_TOOLSBAR_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GUI_ToolsBar
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *borderStylesheetWidget;
    QGridLayout *gridLayout;
    QWidget *stylesheetWidget;
    QHBoxLayout *horizontalLayout_7;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *undoPushButton;
    QPushButton *redoPushButton;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *cutPushButton;
    QPushButton *copyPushButton;
    QPushButton *pastePushButton;
    QFrame *line_5;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *alignLeftPushButton;
    QPushButton *alignCenterPushButton;
    QPushButton *alignRightPushButton;
    QPushButton *alignJustifiedPushButton;
    QFrame *line_3;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *italicPushButton;
    QPushButton *boldPushButton;
    QPushButton *underlinedPushButton;
    QPushButton *strikethroughPushButton;
    QFrame *line_4;
    QFontComboBox *fontComboBox;
    QHBoxLayout *fontHorizontalLayout;
    QLabel *label;
    QSpinBox *spinBox;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_2;
    QPushButton *colorPushButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *closePushButton;

    void setupUi(QWidget *GUI_ToolsBar)
    {
        if (GUI_ToolsBar->objectName().isEmpty())
            GUI_ToolsBar->setObjectName(QString::fromUtf8("GUI_ToolsBar"));
        GUI_ToolsBar->resize(982, 70);
        GUI_ToolsBar->setStyleSheet(QString::fromUtf8("QWidget#borderStylesheetWidget{\n"
"	background-color: qlineargradient(spread:reflect, x1:0.5, y1:0, x2:0.5, y2:0.49, stop:0 rgba(207, 245, 236, 255), stop:0.17 rgba(215, 255, 245, 255), stop:1 rgba(230, 255, 249, 255));\n"
"}\n"
"\n"
"#line_2,#line_3,#line_4,#line_5{\n"
"background-color: rgb(203, 240, 251);\n"
"}\n"
"\n"
"QPushButton {\n"
"	height: 24px;\n"
"	width: 28px;\n"
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
"QFontComboBox{\n"
"    border-width: 1px;\n"
"	border-style: inset;\n"
"	border-color: hsv(165, 55, 205);\n"
"}\n"
"\n"
"QFontComboBox:focus{\n"
"    border-width: 2px;\n"
"	border-color: hsv(165, 5"
                        "5, 205);\n"
"}\n"
"\n"
"QComboBox::down-arrow {\n"
"	image: url(:/widgets_parts/widgets_parts/arrowdown.png);\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"	background-color: white;\n"
"	border: 0px;\n"
"}\n"
"\n"
"QSpinBox{\n"
"    border-width: 1px;\n"
"	border-style: inset;\n"
"	border-color: hsv(165, 55, 205);\n"
"}\n"
"\n"
"QSpinBox::down-arrow {\n"
"	image: url(:/widgets_parts/widgets_parts/arrow-down.png);\n"
"}\n"
"\n"
"QSpinBox::up-arrow {\n"
"	image: url(:/widgets_parts/widgets_parts/arrow-up.png);\n"
"}\n"
"\n"
"QSpinBox::down-button,QSpinBox::up-button {\n"
"	background-color: hsv(165, 55, 255);\n"
"    border-width: 1px;\n"
"	border-style: outset;\n"
"	border-color: hsv(165, 55, 205);\n"
"}\n"
"\n"
"QSpinBox::down-button:pressed,QSpinBox::up-button:pressed {\n"
"	border-style: inset;\n"
"	background-color: hsv(165, 55, 220);\n"
"}"));
        horizontalLayout = new QHBoxLayout(GUI_ToolsBar);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        borderStylesheetWidget = new QWidget(GUI_ToolsBar);
        borderStylesheetWidget->setObjectName(QString::fromUtf8("borderStylesheetWidget"));
        gridLayout = new QGridLayout(borderStylesheetWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        stylesheetWidget = new QWidget(borderStylesheetWidget);
        stylesheetWidget->setObjectName(QString::fromUtf8("stylesheetWidget"));
        horizontalLayout_7 = new QHBoxLayout(stylesheetWidget);
        horizontalLayout_7->setSpacing(12);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(15, 5, 15, 5);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        undoPushButton = new QPushButton(stylesheetWidget);
        undoPushButton->setObjectName(QString::fromUtf8("undoPushButton"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/editor/text_editor/Undo.svg"), QSize(), QIcon::Normal, QIcon::Off);
        undoPushButton->setIcon(icon);

        horizontalLayout_2->addWidget(undoPushButton);

        redoPushButton = new QPushButton(stylesheetWidget);
        redoPushButton->setObjectName(QString::fromUtf8("redoPushButton"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/editor/text_editor/Redo.svg"), QSize(), QIcon::Normal, QIcon::Off);
        redoPushButton->setIcon(icon1);

        horizontalLayout_2->addWidget(redoPushButton);


        horizontalLayout_7->addLayout(horizontalLayout_2);

        line_2 = new QFrame(stylesheetWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
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
        line_2->setPalette(palette);
        line_2->setFrameShadow(QFrame::Plain);
        line_2->setFrameShape(QFrame::VLine);

        horizontalLayout_7->addWidget(line_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        cutPushButton = new QPushButton(stylesheetWidget);
        cutPushButton->setObjectName(QString::fromUtf8("cutPushButton"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/editor/text_editor/Cut.svg"), QSize(), QIcon::Normal, QIcon::Off);
        cutPushButton->setIcon(icon2);

        horizontalLayout_3->addWidget(cutPushButton);

        copyPushButton = new QPushButton(stylesheetWidget);
        copyPushButton->setObjectName(QString::fromUtf8("copyPushButton"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/editor/text_editor/Copy.svg"), QSize(), QIcon::Normal, QIcon::Off);
        copyPushButton->setIcon(icon3);

        horizontalLayout_3->addWidget(copyPushButton);

        pastePushButton = new QPushButton(stylesheetWidget);
        pastePushButton->setObjectName(QString::fromUtf8("pastePushButton"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/editor/text_editor/Paste.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pastePushButton->setIcon(icon4);

        horizontalLayout_3->addWidget(pastePushButton);


        horizontalLayout_7->addLayout(horizontalLayout_3);

        line_5 = new QFrame(stylesheetWidget);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        line_5->setPalette(palette1);
        line_5->setFrameShadow(QFrame::Plain);
        line_5->setFrameShape(QFrame::VLine);

        horizontalLayout_7->addWidget(line_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        alignLeftPushButton = new QPushButton(stylesheetWidget);
        alignLeftPushButton->setObjectName(QString::fromUtf8("alignLeftPushButton"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/editor/text_editor/LeftAlign.svg"), QSize(), QIcon::Normal, QIcon::Off);
        alignLeftPushButton->setIcon(icon5);
        alignLeftPushButton->setCheckable(true);

        horizontalLayout_4->addWidget(alignLeftPushButton);

        alignCenterPushButton = new QPushButton(stylesheetWidget);
        alignCenterPushButton->setObjectName(QString::fromUtf8("alignCenterPushButton"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/editor/text_editor/CentralAlign.svg"), QSize(), QIcon::Normal, QIcon::Off);
        alignCenterPushButton->setIcon(icon6);
        alignCenterPushButton->setCheckable(true);

        horizontalLayout_4->addWidget(alignCenterPushButton);

        alignRightPushButton = new QPushButton(stylesheetWidget);
        alignRightPushButton->setObjectName(QString::fromUtf8("alignRightPushButton"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/editor/text_editor/RightAlign.svg"), QSize(), QIcon::Normal, QIcon::Off);
        alignRightPushButton->setIcon(icon7);
        alignRightPushButton->setCheckable(true);

        horizontalLayout_4->addWidget(alignRightPushButton);

        alignJustifiedPushButton = new QPushButton(stylesheetWidget);
        alignJustifiedPushButton->setObjectName(QString::fromUtf8("alignJustifiedPushButton"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/editor/text_editor/JustifiedAlign.svg"), QSize(), QIcon::Normal, QIcon::Off);
        alignJustifiedPushButton->setIcon(icon8);
        alignJustifiedPushButton->setCheckable(true);

        horizontalLayout_4->addWidget(alignJustifiedPushButton);


        horizontalLayout_7->addLayout(horizontalLayout_4);

        line_3 = new QFrame(stylesheetWidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        line_3->setPalette(palette2);
        line_3->setFrameShadow(QFrame::Plain);
        line_3->setFrameShape(QFrame::VLine);

        horizontalLayout_7->addWidget(line_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        italicPushButton = new QPushButton(stylesheetWidget);
        italicPushButton->setObjectName(QString::fromUtf8("italicPushButton"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/editor/text_editor/Italic.svg"), QSize(), QIcon::Normal, QIcon::Off);
        italicPushButton->setIcon(icon9);
        italicPushButton->setCheckable(true);

        horizontalLayout_5->addWidget(italicPushButton);

        boldPushButton = new QPushButton(stylesheetWidget);
        boldPushButton->setObjectName(QString::fromUtf8("boldPushButton"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/editor/text_editor/Bold.svg"), QSize(), QIcon::Normal, QIcon::Off);
        boldPushButton->setIcon(icon10);
        boldPushButton->setCheckable(true);

        horizontalLayout_5->addWidget(boldPushButton);

        underlinedPushButton = new QPushButton(stylesheetWidget);
        underlinedPushButton->setObjectName(QString::fromUtf8("underlinedPushButton"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/editor/text_editor/Underlined.svg"), QSize(), QIcon::Normal, QIcon::Off);
        underlinedPushButton->setIcon(icon11);
        underlinedPushButton->setCheckable(true);

        horizontalLayout_5->addWidget(underlinedPushButton);

        strikethroughPushButton = new QPushButton(stylesheetWidget);
        strikethroughPushButton->setObjectName(QString::fromUtf8("strikethroughPushButton"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/editor/text_editor/StrikeThrough.svg"), QSize(), QIcon::Normal, QIcon::Off);
        strikethroughPushButton->setIcon(icon12);
        strikethroughPushButton->setCheckable(true);

        horizontalLayout_5->addWidget(strikethroughPushButton);


        horizontalLayout_7->addLayout(horizontalLayout_5);

        line_4 = new QFrame(stylesheetWidget);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette3.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette3.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette3.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        line_4->setPalette(palette3);
        line_4->setFrameShadow(QFrame::Plain);
        line_4->setFrameShape(QFrame::VLine);

        horizontalLayout_7->addWidget(line_4);

        fontComboBox = new QFontComboBox(stylesheetWidget);
        fontComboBox->setObjectName(QString::fromUtf8("fontComboBox"));

        horizontalLayout_7->addWidget(fontComboBox);

        fontHorizontalLayout = new QHBoxLayout();
        fontHorizontalLayout->setSpacing(3);
        fontHorizontalLayout->setObjectName(QString::fromUtf8("fontHorizontalLayout"));
        label = new QLabel(stylesheetWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(16, 16));
        label->setMaximumSize(QSize(16, 16));
        label->setPixmap(QPixmap(QString::fromUtf8(":/editor/text_editor/FontSize.svg")));
        label->setScaledContents(true);

        fontHorizontalLayout->addWidget(label);

        spinBox = new QSpinBox(stylesheetWidget);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));

        fontHorizontalLayout->addWidget(spinBox);


        horizontalLayout_7->addLayout(fontHorizontalLayout);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(3);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_2 = new QLabel(stylesheetWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMaximumSize(QSize(16, 16));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/editor/text_editor/TextColor.svg")));
        label_2->setScaledContents(true);

        horizontalLayout_6->addWidget(label_2);

        colorPushButton = new QPushButton(stylesheetWidget);
        colorPushButton->setObjectName(QString::fromUtf8("colorPushButton"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/editor/text_editor/TextColor.svg"), QSize(), QIcon::Normal, QIcon::Off);
        colorPushButton->setIcon(icon13);

        horizontalLayout_6->addWidget(colorPushButton);


        horizontalLayout_7->addLayout(horizontalLayout_6);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);

        closePushButton = new QPushButton(stylesheetWidget);
        closePushButton->setObjectName(QString::fromUtf8("closePushButton"));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/editor/text_editor/Close.svg"), QSize(), QIcon::Normal, QIcon::Off);
        closePushButton->setIcon(icon14);
        closePushButton->setIconSize(QSize(18, 18));

        horizontalLayout_7->addWidget(closePushButton);


        gridLayout->addWidget(stylesheetWidget, 0, 0, 1, 1);


        horizontalLayout->addWidget(borderStylesheetWidget);


        retranslateUi(GUI_ToolsBar);

        QMetaObject::connectSlotsByName(GUI_ToolsBar);
    } // setupUi

    void retranslateUi(QWidget *GUI_ToolsBar)
    {
        GUI_ToolsBar->setWindowTitle(QApplication::translate("GUI_ToolsBar", "Form", nullptr));
#ifndef QT_NO_TOOLTIP
        undoPushButton->setToolTip(QApplication::translate("GUI_ToolsBar", "Undo", nullptr));
#endif // QT_NO_TOOLTIP
        undoPushButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        redoPushButton->setToolTip(QApplication::translate("GUI_ToolsBar", "Redo", nullptr));
#endif // QT_NO_TOOLTIP
        redoPushButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        cutPushButton->setToolTip(QApplication::translate("GUI_ToolsBar", "Cut", nullptr));
#endif // QT_NO_TOOLTIP
        cutPushButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        copyPushButton->setToolTip(QApplication::translate("GUI_ToolsBar", "Copy", nullptr));
#endif // QT_NO_TOOLTIP
        copyPushButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        pastePushButton->setToolTip(QApplication::translate("GUI_ToolsBar", "Paste", nullptr));
#endif // QT_NO_TOOLTIP
        pastePushButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        alignLeftPushButton->setToolTip(QApplication::translate("GUI_ToolsBar", "Align Left", nullptr));
#endif // QT_NO_TOOLTIP
        alignLeftPushButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        alignCenterPushButton->setToolTip(QApplication::translate("GUI_ToolsBar", "Align Center", nullptr));
#endif // QT_NO_TOOLTIP
        alignCenterPushButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        alignRightPushButton->setToolTip(QApplication::translate("GUI_ToolsBar", "Align Right", nullptr));
#endif // QT_NO_TOOLTIP
        alignRightPushButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        alignJustifiedPushButton->setToolTip(QApplication::translate("GUI_ToolsBar", "Align Justified", nullptr));
#endif // QT_NO_TOOLTIP
        alignJustifiedPushButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        italicPushButton->setToolTip(QApplication::translate("GUI_ToolsBar", "Italic", nullptr));
#endif // QT_NO_TOOLTIP
        italicPushButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        boldPushButton->setToolTip(QApplication::translate("GUI_ToolsBar", "Bold", nullptr));
#endif // QT_NO_TOOLTIP
        boldPushButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        underlinedPushButton->setToolTip(QApplication::translate("GUI_ToolsBar", "Underlined", nullptr));
#endif // QT_NO_TOOLTIP
        underlinedPushButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        strikethroughPushButton->setToolTip(QApplication::translate("GUI_ToolsBar", "Strikethrough", nullptr));
#endif // QT_NO_TOOLTIP
        strikethroughPushButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        fontComboBox->setToolTip(QApplication::translate("GUI_ToolsBar", "Font", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label->setToolTip(QApplication::translate("GUI_ToolsBar", "Font Size", nullptr));
#endif // QT_NO_TOOLTIP
        label->setText(QString());
#ifndef QT_NO_TOOLTIP
        label_2->setToolTip(QApplication::translate("GUI_ToolsBar", "Font Color", nullptr));
#endif // QT_NO_TOOLTIP
        label_2->setText(QString());
        colorPushButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        closePushButton->setToolTip(QApplication::translate("GUI_ToolsBar", "Close button", nullptr));
#endif // QT_NO_TOOLTIP
        closePushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class GUI_ToolsBar: public Ui_GUI_ToolsBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_TOOLSBAR_H
