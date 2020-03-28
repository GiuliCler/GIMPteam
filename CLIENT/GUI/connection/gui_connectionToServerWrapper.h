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
    /*USER*/
    static int requestTryLoginWrapper(GIMPdocs *gimpdocs, QString username, QString password);
    static int requestNewAccountWrapper(GIMPdocs *gimpdocs, QString username, QString password, QString nickname, QString icon);
    static int requestUpdateAccountWrapper(GIMPdocs *gimpdocs, int userId, QString password, QString nickname, QString icon);
    static QString getPasswordWrapper(GIMPdocs *gimpdocs, int userid);

    static QString requestGetNicknameWrapper(GIMPdocs *gimpdocs, int userId);
    static QString requestGetUsernameWrapper(GIMPdocs *gimpdocs, int userId);
    static QString requestIconIdWrapper(GIMPdocs *gimpdocs, int userId);

    /*DOCUMENT*/
    static int requestCreateDocumentWrapper(GIMPdocs *gimpdocs, int userId, QString name);
    //static int forgetDocumentWithNameWrapper(GIMPdocs *gimpdocs, int userId, QString docname);
    //static std::shared_ptr<QVector<QString>> getDocuments(int userId);
    static int requestDocDatoUriWrapper(GIMPdocs *gimpdocs, QString uri);
    //static int openWithNameWrapper(GIMPdocs *gimpdocs, QString name);
    static int closeDocumentWrapper(GIMPdocs *gimpdocs, int userId, int docId);

    static QString requestUriWrapper(GIMPdocs *gimpdocs, int docId);
};

#endif // GUI_CONNECTIONTOSERVERWRAPPER_H
