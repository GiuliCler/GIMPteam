#ifndef STUB_H
#define STUB_H

#include <QObject>
#include <memory>

class Stub : public QObject
{
    Q_OBJECT
public:
    explicit Stub(QObject *parent = nullptr);
    //questa serve per fare il login. Restituisc l'id se username e password sono corretti, altrimenti 0 o -1, basta metterci d'accordo
    static long tryLogin(QString username, QString password);
    //anche qui mi srve che ritorni un id
    static long createUser(QString username, QString password, QString nickname, int iconId);
    //a seconda del codice di errore stamperò un messaggio appropriato. Oppure può ritornare direttamente il messaggio
    static int updateUser(long id, QString password, QString nickname, int iconId);

    //dato l'id restituiscono parametri
    static int getIconId(long userid);
    static QString getNickname(long userid);
    static QString getUsername(long userid);
    static QString getPassword(long userid);

    //il valore di ritorno può essere usato o per l'id del document o per un codice di errore
    static long createDocument(int userId, QString name);
    static long openWithURI(QString uri);
    static long openWithName(QString name);
    static std::shared_ptr<QVector<QString>> getDocuments(long userId);
    static void closeDocument(long userId, long docId);
    //volendo può ritornare un codice d'errore
    static int forgetDocumentWithName(long userId, QString docname);
    static QString getDocumentURI(long docId);
    static long getDocumentId(QString name);

    //ritorna un set cogli userId
    static std::shared_ptr<QSet<long>> getWorkingUsersOnDocument(long docId);
    //ritorna tutti gli id degli users che hanno conrtibuito al document. Viene chiamata appena aperto il doc, mentre per l'update metto a disposizione altre funzioni
    static std::shared_ptr<QSet<long>> getContributorsUsersOnDocument(long docId);
};

#endif // STUB_H
