QT += network widgets
QT += sql
QT += core
HEADERS       = server.h \
    database/collegamentoDB.h \
    database/sha256.h \
    dialog.h
SOURCES       = server.cpp \
                database/collegamentoDB.cpp \
                database/sha256.cpp \
                dialog.cpp \
                main.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/network/fortuneserver
INSTALLS += target

DISTFILES += \
    database/CMakeLists.txt \
    database/README.md

RESOURCES += \
    Files/Files.qrc
