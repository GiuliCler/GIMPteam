/********************************************************************************
** Form generated from reading UI file 'gimpdocs.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GIMPDOCS_H
#define UI_GIMPDOCS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GIMPdocs
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;

    void setupUi(QMainWindow *GIMPdocs)
    {
        if (GIMPdocs->objectName().isEmpty())
            GIMPdocs->setObjectName(QString::fromUtf8("GIMPdocs"));
        GIMPdocs->resize(600, 450);
        QFont font;
        font.setFamily(QString::fromUtf8("Gill Sans Ultra Bold"));
        GIMPdocs->setFont(font);
        GIMPdocs->setStyleSheet(QString::fromUtf8("/*font: bold italic 40px \"Times New Roman\";*/\n"
"\n"
"QMainWindow, QDialog{\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(122, 158, 126, 255), stop:1 rgba(198, 255, 194, 255));\n"
"}\n"
""));
        centralwidget = new QWidget(GIMPdocs);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	padding-left: 30px;\n"
"	/*height: 25px;\n"
"	width: 75px;*/\n"
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
"}"));
        GIMPdocs->setCentralWidget(centralwidget);
        menubar = new QMenuBar(GIMPdocs);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 600, 21));
        GIMPdocs->setMenuBar(menubar);

        retranslateUi(GIMPdocs);

        QMetaObject::connectSlotsByName(GIMPdocs);
    } // setupUi

    void retranslateUi(QMainWindow *GIMPdocs)
    {
        GIMPdocs->setWindowTitle(QApplication::translate("GIMPdocs", "GIMPdocs", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GIMPdocs: public Ui_GIMPdocs {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GIMPDOCS_H
