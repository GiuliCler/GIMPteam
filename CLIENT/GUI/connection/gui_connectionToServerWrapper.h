#ifndef GUI_CONNECTIONTOSERVERWRAPPER_H
#define GUI_CONNECTIONTOSERVERWRAPPER_H

#include "../../connection_to_server.h"
//serve per gli shared pointers
#include <memory>

class GIMPdocs;


//lo scopo di questa classe è quello di gestire i try catch qua dentro quando chiamo una funzione relativa alla connessione. In questo modo il codice delle altre classi dovrebbe risultare più leggibile
class GUI_ConnectionToServerWrapper
{
public:

    //ci vuole sempre un valore di ritorno, anche per funzioni potenzialmente void, per notificare se ci sono state eccezioni o se è andato tutto bene (ed in questo caso, il valore di ritorno può essere il dato richiesto)
    /*USER*/
    static int requestTryLoginWrapper(GIMPdocs *gimpdocs, QString username, QString password);
    static int requestNewAccountWrapper(GIMPdocs *gimpdocs, QString username, QString password, QString nickname, QString icon);
    static int requestUpdateAccountWrapper(GIMPdocs *gimpdocs, int userId, QString password, QString nickname, QString icon);

    static QString requestGetNicknameWrapper(GIMPdocs *gimpdocs, int userId);
    static QString requestGetUsernameWrapper(GIMPdocs *gimpdocs, int userId);
    static QString requestIconIdWrapper(GIMPdocs *gimpdocs, int userId);

    /*DOCUMENT*/
    static int requestCreateDocumentWrapper(GIMPdocs *gimpdocs, int userId, QString name);
    static int openKnownDocumentWrapper(GIMPdocs *gimpdocs, int documentId);
    static int forgetKnownDocumentWrapper(GIMPdocs *gimpdocs, int userId, int documentId);
    static int requestDocDatoUriWrapper(GIMPdocs *gimpdocs, QString uri);
    static std::shared_ptr<QMap<int, QString>> getKnownDocumentsWrapper(GIMPdocs *gimpdocs, int userId);
    static int closeDocumentWrapper(GIMPdocs *gimpdocs, int userId, int docId);

    static QString requestUriWrapper(GIMPdocs *gimpdocs, int docId);
};

#endif // GUI_CONNECTIONTOSERVERWRAPPER_H
