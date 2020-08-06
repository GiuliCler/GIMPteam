#ifndef STUB_H
#define STUB_H

#include <QObject>
#include <memory>
#include <QColor>
#include <QTextDocument>

#include "GUI/connection/gui_connectionException.h"
#include "GUI/connection/gui_genericException.h"
#include "GUI/editorWindow/gui_editor.h"
#include "connection_to_server.h"


class Stub : public QObject
{
    Q_OBJECT
public:
    explicit Stub(QObject *parent = nullptr);

    static bool isConnectionWorking();

    /*USERS*/
    //questa serve per fare il login. Restituisc l'id se username e password sono corretti, altrimenti lancia un'eccezione
    static int requestTryLoginTemporary(connection_to_server *connection, QString username, QString password);
    static int requestTryLogOutTemporary(connection_to_server *connection, int userId);
    static int requestNewAccountTemporary(connection_to_server *connection, QString username, QString password, QString nickname, QString icon);
    static int requestUpdateAccountTemporary(connection_to_server *connection, int userId, QString password, QString nickname, QString icon);
    static QString requestGetNicknameTemporary(connection_to_server *connection, int userId);
    static QString requestGetUsernameTemporary(connection_to_server *connection, int userId);
    static QString requestIconIdTemporary(connection_to_server *connection, int userId);


    /*DOCUMENTS*/
    static int requestCreateDocumentTemporary(connection_to_server *connection, int userId, QString name);
    static QString openKnownDocument(connection_to_server *connection, int userId, int documentId);                                  // FILE
    static void forgetKnownDocumentTemporary(connection_to_server *connection, int userId, int documentId);
    static std::shared_ptr<QMap<QString, int>> getKnownDocumentsTemporary(connection_to_server *connection, int userId);
    //lo userId serve per aggiungere il collegamento tra utente e document, se ancora non era presente nel DB
    static long requestDocDatoUri(connection_to_server *connection, int userId, QString uri);       // FILE
    static void closeDocument(connection_to_server *connection, int userId, int docId);                               // FILE

    static QString requestUriTemporary(connection_to_server *connection, int docId);
    static QString requestDocNameTemporary(connection_to_server *connection,int docId);
    //mi serve per l'export PDF da parte del server perchè i document sono ancora tutti chiusi (quindi non è per te Paul, credo)
    static std::shared_ptr<QTextDocument> getDocumentText(int docId);               // ?????
    //mi serve per ricevere l'id dell'owner del document
    static int requestDocumentOwner(connection_to_server *connection, int docId);

    /*EDITOR*/
    //ritorna un set con un vettore di userId
    static std::shared_ptr<QSet<int>> getWorkingUsersOnDocumentTemporary(connection_to_server *connection,int docId);
    //ritorna tutti gli id degli users che hanno conrtibuito al document. Viene chiamata appena aperto il doc, mentre per l'update ci sono altre funzioni apposta nella classe gui_editor
    static std::shared_ptr<QSet<int>> getContributorsUsersOnDocument(int docId);
    static void Editor(connection_to_server *connection);
};

#endif // STUB_H
