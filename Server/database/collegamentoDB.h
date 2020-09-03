#ifndef GIMPDOCS_COLLEGAMENTODB_H
#define GIMPDOCS_COLLEGAMENTODB_H
#include <QCoreApplication>
#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <iostream>
#include <QVariant>
#include <QPair>

class CollegamentoDB {

private:
    QString creaURI(QString nomeDOC);
    void gen_random(char *s, const int len);
    QString connectionName;

public:
    void connettiDB(const QString& dbname, const QString& connectionName, const QString& hostname="localhost", const QString& username="root", const QString& pssw="");
    void disconnettiDB();
    std::vector<QString> login(QString username, QString password);
    int signup(QString username, QString password, QString nickname, QString icona, int userId);
    int creaDoc(QString nomeDOC);
    QString recuperaURI(QString nomeDOC);
    QString recuperaDocDatoURI(QString uri);
    int aggiungiPartecipante(QString nomeDOC, QString username);
    std::vector<QString> recuperaDocs(QString username);
    QString getNickname(QString username);
    QString getIcon(QString username);
    std::vector<std::vector<QString>> recuperaCollaboratori(QString nomeDOC);
    int recuperaSiteCounter(QString nomeDOC, QString username);
    int rimuoviPartecipante(QString nomeDOC, QString username);
    int rimuoviAccesso(QString nomeDOC, QString username);
    int aggiornaSiteCounter(QString nomeDOC, QString username, int siteCount);
    int aggiornaUser(QString username, QString nuova_password, QString nuovo_nickname, QString nuova_icona, int userId);
    std::vector<QString> recuperaDocsNelDB();
    QVector<QPair<QString, int>> recuperaUtentiNelDB();
    int rimuoviDocumento(QString nomeDOC);
};

#endif //GIMPDOCS_COLLEGAMENTODB_H
