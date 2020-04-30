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

    static bool isConnectionWorking();

    /*USERS*/
    //questa serve per fare il login. Restituisc l'id se username e password sono corretti, altrimenti lancia un'eccezione
    static int requestTryLoginTemporary(connection_to_server *connection, QString username, QString password);
    static int requestNewAccountTemporary(connection_to_server *connection, QString username, QString password, QString nickname, QString icon);
    static int requestUpdateAccountTemporary(connection_to_server *connection, int userId, QString password, QString nickname, QString icon);

    static std::string requestGetNicknameTemporary(connection_to_server *connection, int userId);
    static std::string requestGetUsernameTemporary(connection_to_server *connection, int userId);
    static std::string requestIconIdTemporary(connection_to_server *connection, int userId);


    /*DOCUMENTS*/
    static int requestCreateDocumentTemporary(connection_to_server *connection, int userId, QString name);
    static void openKnownDocument(int documentId);                                  // FILE
    static void forgetKnownDocument(connection_to_server *connection,int userId, int documentId);                    // DA DECIDERE COSA FARE
    static std::shared_ptr<QMap<int, QString>> getKnownDocuments(int userId);
    static std::string requestDocDatoUriTemporary(connection_to_server *connection, QString uri);       // FILE
    static void closeDocument(int userId, int docId);                               // FILE

    static std::string requestUriTemporary(connection_to_server *connection, int docId);
    static std::string getDocumentName(connection_to_server *connection,int docId);
    //mi serve per l'export PDF da parte del server perchè i document sono ancora tutti chiusi (quindi non è per te Paul, credo)
    static std::shared_ptr<QTextDocument> getDocumentText(int docId);               // ?????

    /*EDITOR*/
    //ritorna un set con un vettore di userId
    static std::shared_ptr<QSet<int>> getWorkingUsersOnDocument(int docId);
    //ritorna tutti gli id degli users che hanno conrtibuito al document. Viene chiamata appena aperto il doc, mentre per l'update metto a disposizione altre funzioni
    static std::shared_ptr<QSet<int>> getContributorsUsersOnDocument(int docId);

    //questo serve per quando si sposta il cursore e bisogna cambiare automaticamente colore al pulsante
    static QColor getCurrentTextColor();
    static void setCurrentTextColor(QColor color);

};

#endif // STUB_H
