#ifndef STUB_H
#define STUB_H

#include <QObject>

class Stub : public QObject
{
    Q_OBJECT
public:
    explicit Stub(QObject *parent = nullptr);
    //questa serve per fare il login. Restituisc l'id se username e password sono corretti, altrimenti 0 o -1, basta metterci d'accordo
    static long tryLogin(QString username, QString password);
    //anche qui mi srve che ritorni un id
    static long createUser(QString username, QString password, QString nickname, int iconId);
    static void updateUser(long id, QString password, QString nickname, int iconId);

    //dato l'id restituiscono parametri
    static int getIconId(int id);
    static QString getNickname(long id);
    static QString getUsername(long id);
    static QString getPassword(long id);
};

#endif // STUB_H
