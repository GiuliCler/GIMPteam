QT += network widgets
QT += sql
QT += core
HEADERS       = server.h \
    crdt/crdt_message.h \
    crdt/crdt_servereditor.h \
    crdt/crdt_symbol.h \
    database/collegamentoDB.h \
    dialog.h \
    thread_body.h \
    thread_management.h
SOURCES       = server.cpp \
                crdt/crdt_message.cpp \
                crdt/crdt_servereditor.cpp \
                crdt/crdt_symbol.cpp \
                database/collegamentoDB.cpp \
                dialog.cpp \
                main.cpp \
                thread_body.cpp \
                thread_management.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/network/fortuneserver
INSTALLS += target

DISTFILES += \
    ../../../../../../OpenSSL-Win64/bin/key.key \
    ../../../../../../OpenSSL-Win64/bin/key.pem \
    certificates/client_key.key \
    certificates/client_key.pem \
    certificates/key.key \
    certificates/key.pem \
    database/CMakeLists.txt \
    database/README.md

RESOURCES +=
