#include <QCoreApplication>
#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <iostream>
#include "collegamentoDB.h"

int main(int argc, char *argv[]) {

    QCoreApplication a(argc, argv);
    CollegamentoDB* link = new CollegamentoDB();

    link->connettiDB("gimpdocs_db");

    int uno = link->login("pippoYEE", "pizza");     // PROVA -----------------------------------

    return a.exec();
}