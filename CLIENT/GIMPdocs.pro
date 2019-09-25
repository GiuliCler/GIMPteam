#-------------------------------------------------
#
# Project created by QtCreator 2019-08-26T17:40:53
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GIMPdocs
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        GUI/editorWindow/gui_colorsmanager.cpp \
        GUI/editorWindow/gui_myscrollarea.cpp \
        GUI/editorWindow/gui_usersbar.cpp \
        GUI/gimpdocs.cpp \
        GUI/editorWindow/gui_coloredcursor.cpp \
        GUI/editorWindow/gui_editor.cpp \
        GUI/gui_forgetdoc.cpp \
        GUI/gui_icons.cpp \
        GUI/gui_login.cpp \
        GUI/gui_menu.cpp \
        GUI/editorWindow/gui_mytextedit.cpp \
        GUI/gui_newdoc.cpp \
        GUI/gui_opendoc.cpp \
        GUI/gui_profile.cpp \
        main.cpp \
        stub.cpp

HEADERS += \
        GUI/editorWindow/gui_colorsmanager.h \
        GUI/editorWindow/gui_myscrollarea.h \
        GUI/editorWindow/gui_usersbar.h \
        GUI/gimpdocs.h \
        GUI/editorWindow/gui_coloredcursor.h \
        GUI/editorWindow/gui_editor.h \
        GUI/gui_forgetdoc.h \
        GUI/gui_icons.h \
        GUI/gui_login.h \
        GUI/gui_menu.h \
        GUI/editorWindow/gui_mytextedit.h \
        GUI/gui_newdoc.h \
        GUI/gui_opendoc.h \
        GUI/gui_profile.h \
        stub.h

FORMS += \
    GUI/editorWindow/ui/gui_usersbar.ui \
    GUI/ui/gimpdocs.ui \
    GUI/editorWindow/ui/gui_editor.ui \
    GUI/editorWindow/ui/gui_editorwindow.ui \
    GUI/ui/gui_forgetdoc.ui \
        GUI/ui/gui_login.ui \
        GUI/ui/gui_menu.ui \
    GUI/ui/gui_newdoc.ui \
    GUI/ui/gui_opendoc.ui \
        GUI/ui/gui_profile.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RESOURCES += \
    GUI/images/images.qrc

