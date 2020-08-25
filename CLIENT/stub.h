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
    //La login restituisce l'Id dello user, come anche la new account
    static int requestTryLoginTemporary(connection_to_server *connection, QString username, QString password);
    static void requestTryLogOutTemporary(connection_to_server *connection, int userId);
    static int requestNewAccountTemporary(connection_to_server *connection, QString username, QString password, QString nickname, QString icon);
    static void requestUpdateAccountTemporary(connection_to_server *connection, int userId, QString password, QString nickname, QString icon);
    static QString requestGetNicknameTemporary(connection_to_server *connection, int userId);
    static QString requestGetUsernameTemporary(connection_to_server *connection, int userId);
    static QString requestIconIdTemporary(connection_to_server *connection, int userId);


    /*DOCUMENTS*/
    static std::shared_ptr<QMap<QString, int>> getKnownDocumentsTemporary(connection_to_server *connection, int userId);
    static QString requestCreateDocumentTemporary(connection_to_server *connection, int userId, QString name);
    static void requestDeleteDocTemporary(connection_to_server *connection, int userId, int documentId);
    static QString openDocTemporary(connection_to_server *connection, int userId, int documentId);
    static void closeDocumentTemporary(connection_to_server *connection, int userId, int docId);
    //lo userId serve per aggiungere il collegamento tra utente e document, se ancora non era presente nel DB
    static QString requestDocDatoUriTemporary(connection_to_server *connection, int userId, QString uri);


    /*DOCUMENT PROPERTIES*/
    static QString requestUriTemporary(connection_to_server *connection, int docId);
    static QString requestDocNameTemporary(connection_to_server *connection,int docId);
    static int getDocumentOwnerTemporary(connection_to_server *connection, int docId);
    //mi serve per l'export PDF da parte del server perchè i document sono ancora tutti chiusi (quindi non è per te Paul, credo)
    static std::shared_ptr<QTextDocument> getDocumentText(connection_to_server *connection, int docId, int userId);


    /*EDITOR*/
    //ritorna un set con un vettore di userId
    static std::shared_ptr<QSet<int>> getWorkingUsersOnDocumentTemporary(connection_to_server *connection,int docId);
    //ritorna tutti gli id degli users che hanno conrtibuito al document. Viene chiamata appena aperto il doc, mentre per l'update ci sono altre funzioni apposta nella classe gui_editor
    static std::shared_ptr<QSet<int>> getContributorsTemporary(connection_to_server *connection, int docId);
    //.... e questo da dove salta fuori?
    static void startEditorConnectionTemporary(connection_to_server *connection);
};

#endif // STUB_H
