#ifndef GUI_CONNECTIONTOSERVERWRAPPER_H
#define GUI_CONNECTIONTOSERVERWRAPPER_H

#include "../../connection_to_server.h"

class GIMPdocs;


//lo scopo di questa classe è quello di gestire i try catch qua dentro quando chiamo una funzione relativa alla connessione. In questo modo il codice delle altre classi dovrebbe risultare più leggibile
class GUI_ConnectionToServerWrapper
{
public:
    /*USER*/
    static int requestTryLoginWrapper(GIMPdocs *gimpdocs, QString username, QString password);
    static int requestNewAccountWrapper(GIMPdocs *gimpdocs, QString username, QString password, QString nickname, QString icon);
    static int requestUpdateAccountWrapper(GIMPdocs *gimpdocs, int userId, QString password, QString nickname, QString icon);

    static QString requestGetNicknameWrapper(GIMPdocs *gimpdocs, int userId);
    static QString requestGetUsernameWrapper(GIMPdocs *gimpdocs, int userId);
    static QString requestIconIdWrapper(GIMPdocs *gimpdocs, int userId);

    /*DOCUMENT*/
    static int requestCreateDocumentWrapper(GIMPdocs *gimpdocs, int userId, QString name);
    static int requestDocDatoUriWrapper(GIMPdocs *gimpdocs, QString uri);

    static QString requestUriWrapper(GIMPdocs *gimpdocs, long docId);
};

#endif // GUI_CONNECTIONTOSERVERWRAPPER_H
