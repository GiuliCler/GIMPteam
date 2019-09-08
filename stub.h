#ifndef STUB_H
#define STUB_H

#include <QObject>

class Stub : public QObject
{
    Q_OBJECT
public:
    explicit Stub(QObject *parent = nullptr);
    //questa serve per fare il login. Restituisc vero se username e password sono corretti
    static bool tryLogin(QString username, QString password);
    //questa restituisce il nickname dell'utente attivo. Probabilmente avrà bisogno anche di un parametro tipo l'id
    static QString getNickname();
};

#endif // STUB_H
