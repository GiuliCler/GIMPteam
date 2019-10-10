#ifndef GIMPDOCS_COLLEGAMENTODB_H
#define GIMPDOCS_COLLEGAMENTODB_H
#include <QCoreApplication>
#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <iostream>

class CollegamentoDB{
private:
    std::string creaURI(std::string nomeDOC);
    void gen_random(char *s, const int len);
public:
    void connettiDB(const QString& dbname, const QString& hostname="localhost", const QString& username="root", const QString& pssw="");
    void disconnettiDB();
    std::vector<std::string> login(std::string username, std::string password);
    int signup(std::string username, std::string password, std::string nickname, std::string icona);
    int creaDoc(std::string nomeDOC);
    std::string recuperaURI(std::string nomeDOC);
    std::string recuperaDocDatoURI(std::string uri);
    std::vector<std::string> recuperaDocs(std::string username);
    std::vector<std::string> recuperaCollaboratori(std::string nomeDOC);                    // TODO
    std::vector<int> recuperaInfoUtenteDoc(std::string nomeDOC, std::string username);      // TODO -- to test
    int aggiungiPartecipante(std::string nomeDOC, std::string username);                     // TODO -- to re-test
    int rimuoviPartecipante(std::string nomeDOC, std::string username);                      // TODO -- to test
    int aggiornaSiteCounter(std::string nomeDOC, std::string username, int siteCount);      // TODO -- to test
    int aggiornaUser(std::string username, std::string nuova_password, std::string nuovo_nickname, std::string nuova_icona);
};

#endif //GIMPDOCS_COLLEGAMENTODB_H
