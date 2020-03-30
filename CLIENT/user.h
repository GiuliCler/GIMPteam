#ifndef USER_H
#define USER_H

#include <QObject>
#include <QString>

class User : public QObject
{
    Q_OBJECT
public:
    explicit User(QObject *parent = nullptr);

//dato l'id restituiscono parametri
QString username, nickname, iconId, password;

QString getIconId();
QString getNickname();
QString getUsername();

void setIconId(QString);
void setNickname(QString);
void setUsername(QString);
};
#endif // USER_H
