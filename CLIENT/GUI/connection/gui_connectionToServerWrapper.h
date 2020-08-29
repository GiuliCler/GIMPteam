#ifndef GUI_CONNECTIONTOSERVERWRAPPER_H
#define GUI_CONNECTIONTOSERVERWRAPPER_H

#include "../../connection_to_server.h"
//serve per gli shared pointers
#include <memory>
#include "GUI/editorWindow/gui_editor.h"
#include <QTextDocument>

class GIMPdocs;


//lo scopo di questa classe è quello di gestire i try catch qua dentro quando chiamo una funzione relativa alla connessione. In questo modo il codice delle altre classi dovrebbe risultare più leggibile
class GUI_ConnectionToServerWrapper
{
public:

    //ci vuole sempre un valore di ritorno, anche per funzioni potenzialmente void, per notificare se ci sono state eccezioni o se è andato tutto bene (ed in questo caso, il valore di ritorno può essere il dato richiesto)
    /*USERS*/
    static int requestLoginWrapper(GIMPdocs *gimpdocs, QString username, QString password);
    static int requestLogoutWrapper(GIMPdocs *gimpdocs, int userId);
    //è per quando chiudo direttamente GIMPdocs
    static int requestDefinitiveLogoutWrapper(GIMPdocs *gimpdocs, int userId);
    static int requestNewAccountWrapper(GIMPdocs *gimpdocs, QString username, QString password, QString nickname, QString icon);
    static int requestUpdateAccountWrapper(GIMPdocs *gimpdocs, int userId, QString password, QString nickname, QString icon);
    static QString requestGetNicknameWrapper(GIMPdocs *gimpdocs, int userId);
    static QString requestGetUsernameWrapper(GIMPdocs *gimpdocs, int userId);
    static QString requestGetIconIdWrapper(GIMPdocs *gimpdocs, int userId);


    /*DOCUMENTS*/
    static std::shared_ptr<QMap<int, QString>> requestGetKnownDocumentsWrapper(GIMPdocs *gimpdocs, int userId);
    static QString requestCreateDocumentWrapper(GIMPdocs *gimpdocs, int userId, QString name);
    static int requestDeleteDocumentWrapper(GIMPdocs *gimpdocs, int userId, int documentId);
    static QString requestOpenDocumentWrapper(GIMPdocs *gimpdocs, int userId, int documentId);
    static int requestCloseDocumentWrapper(GIMPdocs *gimpdocs, int userId, int docId);
    static QString requestDocumentDatoUriWrapper(GIMPdocs *gimpdocs, int userId, QString uri);


    /*DOCUMENT PROPERTIES*/
    static QString requestDocumentNameWrapper(GIMPdocs *gimpdocs, int docId);
    static QString requestUriWrapper(GIMPdocs *gimpdocs, int docId);
    static int requestDocumentOwnerWrapper(GIMPdocs *gimpdocs, int docId);
    static std::shared_ptr<QTextEdit> getDocumentTextWrapper(GIMPdocs *gimpdocs, int docId, int userId);

    /*EDITOR*/
    static std::shared_ptr<QSet<int>> getWorkingUsersOnDocumentWrapper(GIMPdocs *gimpdocs, int docId);
    static std::shared_ptr<QSet<int>> getContributorsUsersOnDocumentWrapper(GIMPdocs *gimpdocs, int docId);
    static int requestStartEditorConnection(GIMPdocs *gimpdocs);

};

#endif // GUI_CONNECTIONTOSERVERWRAPPER_H
