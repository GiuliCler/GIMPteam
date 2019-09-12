#ifndef GIMPDOCS_COLLEGAMENTODB_H
#define GIMPDOCS_COLLEGAMENTODB_H
#include <QCoreApplication>
#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <iostream>

class CollegamentoDB{
private:
    std::string recuperaURI(std::string nomeDOC);
    void gen_random(char *s, const int len);
public:
    void connettiDB(const QString& dbname, const QString& hostname="localhost", const QString& username="root", const QString& pssw="");
    void disconnettiDB();
    std::vector<std::string> login(std::string username, std::string password);
    int signup(std::string username, std::string password, std::string nickname, std::string icona);
    int creaDoc(std::string nomeDOC);
    std::string creaURI(std::string nomeDOC);
    int aggiungiPartecipante(std::string nomeDOC, std::string username);
    std::vector<std::string> recuperaDocs(std::string username);
};

#endif //GIMPDOCS_COLLEGAMENTODB_H
