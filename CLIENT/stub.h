#ifndef STUB_H
#define STUB_H

#include <QObject>
#include <memory>
#include <QColor>
#include <QTextDocument>

#include "GUI/connection/gui_connectionException.h"
#include "GUI/connection/gui_genericException.h"
#include "connection_to_server.h"


class Stub : public QObject
{
    Q_OBJECT
public:
    explicit Stub(QObject *parent = nullptr);

    //tutti i long degli id sono da modificare in ... dobbiamo ancora decidere in cosa
    static bool isConnectionWorking();

    /*USERS*/
    //questa serve per fare il login. Restituisc l'id se username e password sono corretti, altrimenti lancia un'eccezione
    static long requestTryLoginTemporary(connection_to_server *connection, QString username, QString password);
    static long requestNewAccountTemporary(connection_to_server *connection, QString username, QString password, QString nickname, QString icon);
    static long requestUpdateAccountTemporary(connection_to_server *connection, int userId, QString password, QString nickname, QString icon);

    //dato l'id restituiscono parametri
    static std::string requestGetNicknameTemporary(connection_to_server *connection, int userId);
    static std::string requestGetUsernameTemporary(connection_to_server *connection, int userId);
    static std::string requestIconIdTemporary(connection_to_server *connection, int userId);
    static QString getPassword(long userid);

    /*DOCUMENTS*/
    //il valore di ritorno può essere usato o per l'id del document o per un codice di errore
    static long createDocument(int userId, QString name);
    static int forgetDocumentWithName(long userId, QString docname);
    static std::shared_ptr<QVector<QString>> getDocuments(long userId);
    static long openWithURI(QString uri);
    static long openWithName(QString name);  
    static void closeDocument(long userId, long docId);


    static QString getDocumentURI(long docId);
    static long getDocumentId(QString name);
    static QString getDocumentName(long docId);
    //mi serve per l'export PDF da parte del server perchè i document sono ancora tutti chiusi (quindi non è per te Paul)
    static std::shared_ptr<QTextDocument> getDocumentText();

    /*EDITOR*/
    //ritorna un set con un vettore di vettori con <carciofo, nickname, id-icona/nome-icona/carciofo-icona>
    static std::shared_ptr<QSet<long>> getWorkingUsersOnDocument(long docId);
    //ritorna tutti gli id degli users che hanno conrtibuito al document. Viene chiamata appena aperto il doc, mentre per l'update metto a disposizione altre funzioni
    static std::shared_ptr<QSet<long>> getContributorsUsersOnDocument(long docId);

    //questo serve per quando si sposta il cursore e bisogna cambiare automaticamente colore al pulsante
    static QColor getCurrentTextColor();
    static void setCurrentTextColor(QColor color);

};

#endif // STUB_H
