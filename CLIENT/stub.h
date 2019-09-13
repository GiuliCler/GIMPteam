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
    static int getIconId(int id);
    static QString getNickname(long id);
    static QString getUsername(long id);
    static QString getPassword(long id);

    //il valore di ritorno può essere usato o per l'id del document o per un codice di errore
    static long createDocument(int userId, QString name);
    static long openWithURI(QString uri);
    static long openWithName(QString name);
    static std::shared_ptr<QVector<QString>> getDocuments(long userId);
};

#endif // STUB_H
