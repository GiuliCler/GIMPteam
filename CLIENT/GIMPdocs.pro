#-------------------------------------------------
#
# Project created by QtCreator 2019-08-26T17:40:53
#
#-------------------------------------------------

QT       += core gui sql printsupport
QT       += network

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
        GUI/connection/gui_connecting.cpp \
        GUI/connection/gui_connectionToServerWrapper.cpp \
        GUI/connection/gui_reconnection.cpp \
        GUI/connection/gui_server.cpp \
        CRDT/crdt_controller.cpp \
        CRDT/crdt_message.cpp \
        CRDT/crdt_sharededitor.cpp \
        CRDT/crdt_symbol.cpp \
        GUI/editorWindow/gui_colorsmanager.cpp \
        GUI/editorWindow/gui_myscrollarea.cpp \
        GUI/editorWindow/gui_toolsbar.cpp \
        GUI/editorWindow/gui_usersbar.cpp \
        GUI/gimpdocs.cpp \
        GUI/editorWindow/gui_coloredcursor.cpp \
        GUI/editorWindow/gui_editor.cpp \
        GUI/gui_icons.cpp \
        GUI/gui_login.cpp \
        GUI/gui_menu.cpp \
        GUI/editorWindow/gui_mytextedit.cpp \
        GUI/gui_newdoc.cpp \
        GUI/gui_opendoc.cpp \
        GUI/gui_profile.cpp \
        GUI/gui_uri.cpp \
        connection_to_server.cpp \
        main.cpp \
        stub.cpp

HEADERS += \
        GUI/connection/gui_connecting.h \
        GUI/connection/gui_connectionException.h \
        GUI/connection/gui_connectionToServerWrapper.h \
        GUI/connection/gui_genericException.h \
        GUI/connection/gui_reconnection.h \
        GUI/connection/gui_server.h \
        CRDT/crdt_controller.h \
        CRDT/crdt_message.h \
        CRDT/crdt_sharededitor.h \
        CRDT/crdt_symbol.h \
        GUI/editorWindow/gui_colorsmanager.h \
        GUI/editorWindow/gui_myscrollarea.h \
        GUI/editorWindow/gui_toolsbar.h \
        GUI/editorWindow/gui_usersbar.h \
        GUI/gimpdocs.h \
        GUI/editorWindow/gui_coloredcursor.h \
        GUI/editorWindow/gui_editor.h \
        GUI/gui_icons.h \
        GUI/gui_login.h \
        GUI/gui_menu.h \
        GUI/editorWindow/gui_mytextedit.h \
        GUI/gui_newdoc.h \
        GUI/gui_opendoc.h \
        GUI/gui_profile.h \
        GUI/gui_uri.h \
        connection_to_server.h \
        stub.h

FORMS += \
    GUI/connection/ui/gui_connecting.ui \
    GUI/connection/ui/gui_reconnection.ui \
    GUI/connection/ui/gui_server.ui \
    GUI/editorWindow/ui/gui_toolsbar.ui \
    GUI/editorWindow/ui/gui_usersbar.ui \
    GUI/ui/gimpdocs.ui \
    GUI/editorWindow/ui/gui_editor.ui \
    GUI/editorWindow/ui/gui_editorwindow.ui \
        GUI/ui/gui_login.ui \
        GUI/ui/gui_menu.ui \
    GUI/ui/gui_newdoc.ui \
    GUI/ui/gui_opendoc.ui \
        GUI/ui/gui_profile.ui \
    GUI/ui/gui_uri.ui

RESOURCES += \
    GUI/images/images.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:RC_ICONS += GUI/images/logo/gimpLogo.ico


