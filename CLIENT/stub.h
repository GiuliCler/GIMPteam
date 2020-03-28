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
    static QString getPassword(int userid);


    /*DOCUMENTS*/
    static int requestCreateDocumentTemporary(connection_to_server *connection, int userId, QString name);
    static int forgetDocumentWithName(int userId, QString docname);
    static std::shared_ptr<QVector<QString>> getDocuments(int userId);
    static std::string requestDocDatoUriTemporary(connection_to_server *connection, QString uri);
    static int openWithName(QString name);
    static int closeDocument(int userId, int docId);

    static std::string requestUriTemporary(connection_to_server *connection, int docId);
    static int getDocumentId(QString name);
    static QString getDocumentName(int docId);
    //mi serve per l'export PDF da parte del server perchè i document sono ancora tutti chiusi (quindi non è per te Paul)
    static std::shared_ptr<QTextDocument> getDocumentText();

    /*EDITOR*/
    //ritorna un set con un vettore di vettori con <carciofo, nickname, id-icona/nome-icona/carciofo-icona>
    static std::shared_ptr<QSet<int>> getWorkingUsersOnDocument(int docId);
    //ritorna tutti gli id degli users che hanno conrtibuito al document. Viene chiamata appena aperto il doc, mentre per l'update metto a disposizione altre funzioni
    static std::shared_ptr<QSet<int>> getContributorsUsersOnDocument(int docId);

    //questo serve per quando si sposta il cursore e bisogna cambiare automaticamente colore al pulsante
    static QColor getCurrentTextColor();
    static void setCurrentTextColor(QColor color);

};

#endif // STUB_H
