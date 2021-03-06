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

    std::cout<<"---------------------------------------------"<<std::endl;

    /* Creo due utenti */
    int uno = link->signup("utente1@p.it", "cane", "paxerello22", "image1");
    std::cout<<"Inserimento uno: "<<uno<<std::endl;     // valore di ritorno atteso: 1
    int due = link->signup("utente2@p.it", "gatto", "paperella14", "image2");
    std::cout<<"Inserimento due: "<<due<<std::endl;     // valore di ritorno atteso: 1

    /* Creo un terzo utente che non può stare nel DB (username uguale all'username del primo utente) */
    int tre = link->signup("utente1@p.it", "criceto", "ananas666", "image3");
    std::cout<<"Inserimento tre: "<<tre<<std::endl;     // valore di ritorno atteso: 0

    /* Creo un utente senza immagine di icona (boundary case) */
    int quattro = link->signup("utente3@p.it", "scimmia", "carciofomalefico", "");
    std::cout<<"Inserimento quattro: "<<quattro<<std::endl;     // valore di ritorno atteso: 1

    std::cout<<"---------------------------------------------"<<std::endl;

    /* Creo due documenti */
    int one = link->creaDoc("DivinaCommedia");
    std::cout<<"Inserimento one: "<<one<<std::endl;     // valore di ritorno atteso: 1
    int two = link->creaDoc("PromessiSposi");
    std::cout<<"Inserimento two: "<<two<<std::endl;     // valore di ritorno atteso: 1

    /* Creo un terzo documento (nome doc uguale al primo doc)*/
    int three = link->creaDoc("DivinaCommedia");
    std::cout<<"Inserimento three: "<<three<<std::endl;     // valore di ritorno atteso: 0

    std::cout<<"---------------------------------------------"<<std::endl;

    /* Provo i boundary case (stringhe vuote) --> valori di ritorno attesi: 0 */
    int rit;
    rit = link->signup("", "delfino", "cilieginasullatorta44", "image4");
    std::cout<<"Username vuoto: "<<rit<<std::endl;
    rit = link->signup("utente4@p.it", "", "babbonatale68", "");
    std::cout<<"Password vuota: "<<rit<<std::endl;
    rit = link->signup("utente5@p.it", "suricato", "", "image5");
    std::cout<<"Nickname vuoto: "<<rit<<std::endl;
    rit = link->creaDoc("");
    std::cout<<"Nome doc vuoto: "<<rit<<std::endl;

    std::cout<<"---------------------------------------------"<<std::endl;

    /* Segno che l'utente 1 è abilitato alla modifica del documento 1 */
    // Valore di ritorno atteso: 1
    int m;
    m = link->aggiungiPartecipante("DivinaCommedia", "utente1@p.it");
    std::cout<<"Utente1Doc1: "<<m<<std::endl;

    /* Segno che l'utente 1 è abilitato alla modifica del documento 2 */
    // Valore di ritorno atteso: 1
    m = link->aggiungiPartecipante("PromessiSposi", "utente1@p.it");
    std::cout<<"Utente1Doc2: "<<m<<std::endl;

    /* Segno che l'utente 2 è abilitato alla modifica del documento 1 */
    // Valore di ritorno atteso: 1
    m = link->aggiungiPartecipante("DivinaCommedia", "utente2@p.it");
    std::cout<<"Utente2Doc1: "<<m<<std::endl;

    /* Riprovo: segno che l'utente 1 è abilitato alla modifica del documento 1 */
    // Valore di ritorno atteso: 0
    m = link->aggiungiPartecipante("DivinaCommedia", "utente1@p.it");
    std::cout<<"Utente1Doc1_BIS: "<<m<<std::endl;

    /* Segno che l'utente 1 è abilitato alla modifica di un documento inesistente (cioè non presente
     * nella tabella DOC) */
    // Valore di ritorno atteso: 2
    m = link->aggiungiPartecipante("IlFuMattiaPascal", "utente1@p.it");
    std::cout<<"Utente1DocInesistente: "<<m<<std::endl;

    /* Provo il boundary case (stringa vuota) --> valore di ritorno atteso: 2 */
    m = link->aggiungiPartecipante("", "utente1@p.it");
    std::cout<<"Utente1DocVuoto: "<<m<<std::endl;

    std::cout<<"---------------------------------------------"<<std::endl;

    /* Recupero i documenti dell'utente 1 (doc1 e doc2) */
    std::vector<std::string> doc_utente1 = link->recuperaDocs("utente1@p.it");
    std::cout<<"Documenti dell'utente utente1@p.it..."<<std::endl;
    for(auto i=doc_utente1.begin(); i!=doc_utente1.end(); i++)
        std::cout<<"\t"<<(*i)<<std::endl;

    /* Recuperto i documenti dell'utente 3 (nessuno) */
    std::vector<std::string> doc_utente3 = link->recuperaDocs("utente3@p.it");
    std::cout<<"Documenti dell'utente utente3@p.it..."<<std::endl;
    for(auto j=doc_utente3.begin(); j!=doc_utente3.end(); j++)
        std::cout<<"\t"<<(*j)<<std::endl;

    std::cout<<"---------------------------------------------"<<std::endl;

    /* Corretto login utente 1 */
    std::vector<std::string> log1 = link->login("utente1@p.it", "cane");
    std::cout<<"Nickname e icona dell'utente utente1@p.it..."<<std::endl;
    for(auto i=log1.begin(); i!=log1.end(); i++)
        std::cout<<"\t"<<(*i)<<std::endl;

    /* Corretto login utente 3 */
    std::vector<std::string> log2 = link->login("utente3@p.it", "scimmia");
    std::cout<<"Nickname e icona dell'utente utente3@p.it..."<<std::endl;
    for(auto i=log2.begin(); i!=log2.end(); i++)
        std::cout<<"\t"<<(*i)<<std::endl;

    /* Sbagliato login utente 1 (scritto UTEnte1@p.it invece che utente1@p.it) */
    std::vector<std::string> log3 = link->login("UTEnte1@p.it", "cane");
    std::cout<<"Username sbagliato utente UTEnte1@p.it..."<<std::endl;
    for(auto i=log3.begin(); i!=log3.end(); i++)
        std::cout<<"\t"<<(*i)<<std::endl;

    /* Sbagliato login utente con username sbagliato*/
    std::vector<std::string> log0 = link->login("utente0@p.it", "cane");
    std::cout<<"Username sbagliato..."<<std::endl;
    for(auto i=log0.begin(); i!=log0.end(); i++)
        std::cout<<"\t"<<(*i)<<std::endl;

    /* Sbagliato login utente 2 (password sbagliata)*/
    std::vector<std::string> log4 = link->login("utente2@p.it", "canarino");
    std::cout<<"Password sbagliata utente utente2@p.it..."<<std::endl;
    for(auto i=log4.begin(); i!=log4.end(); i++)
        std::cout<<"\t"<<(*i)<<std::endl;

    /* Boundary case (stringhe vuote) */
    std::vector<std::string> log5 = link->login("", "cane");
    std::cout<<"Username vuoto..."<<std::endl;
    for(auto i=log5.begin(); i!=log5.end(); i++)
        std::cout<<"\t"<<(*i)<<std::endl;

    std::vector<std::string> log6 = link->login("utente3@p.it", "");
    std::cout<<"Password vuota..."<<std::endl;
    for(auto i=log6.begin(); i!=log6.end(); i++)
        std::cout<<"\t"<<(*i)<<std::endl;

    std::cout<<"---------------------------------------------"<<std::endl;

    /* Richiedo l'uri del doc 1 --> valore di ritorno atteso: URI */
    std::string uri0 = link->recuperaURI("DivinaCommedia");
    std::cout<<"URI doc 1: "<<uri0<<std::endl;

    /* Richiedo l'uri di un doc inesistente --> valore di ritorno atteso: "errore" */
    std::string uri1 = link->recuperaURI("IlFuMattiaPascal");
    std::cout<<"URI doc inesistente: "<<uri1<<std::endl;

    /* Boundary case: nomeDOC vuoto --> valore di ritorno atteso: "errore" */
    std::string uri2 = link->recuperaURI("");
    std::cout<<"URI doc vuoto: "<<uri2<<std::endl;

    std::cout<<"---------------------------------------------"<<std::endl;

   /* Modifico il nickname dell'utente1 */
    int upd0 = link->aggiornaUser("utente1@p.it", "cane", "puzzettaXD", "image1");
    std::cout<<"Nuovo nickname utente1: "<<upd0<<std::endl;

    /* Modifico la password dell'utente2 */
    int upd1 = link->aggiornaUser("utente2@p.it", "fenicottero", "paperella14", "image2");
    std::cout<<"Nuova password utente2: "<<upd1<<std::endl;

    /* Modifico l'icona dell'utente3 */
    int upd2 = link->aggiornaUser("utente3@p.it", "scimmia", "carciofomalefico", "image34");
    std::cout<<"Nuova icona utente3: "<<upd2<<std::endl;

    /* Modifico le informazioni di un utente inesistente --> valore di ritorno atteso: 0 */
    int upd3 = link->aggiornaUser("utente7@p.it", "banana", "sorbettoalmandarino12", "image5");
    std::cout<<"Update utente inesistente: "<<upd3<<std::endl;
    // int aggiornaUser(std::string username, std::string nuova_password, std::string nuovo_nickname, std::string nuova_icona);

    /* Boundary case: username vuoto --> valore di ritorno atteso: 0 */
    int upd4 = link->aggiornaUser("", "castoro", "lol666", "image9");
    std::cout<<"Username vuoto: "<<upd4<<std::endl;

    /* Boundary case: password vuota --> valore di ritorno atteso: 0 */
    int upd5 = link->aggiornaUser("utente1@p.it", "", "prova0", "image1");
    std::cout<<"Password vuota: "<<upd5<<std::endl;

    /* Boundary case: nickname vuoto --> valore di ritorno atteso: 0 */
    int upd6 = link->aggiornaUser("utente1@p.it", "cane", "", "image8");
    std::cout<<"Nickname vuoto: "<<upd6<<std::endl;

    /* Boundary case: icona vuota --> valore di ritorno atteso: 1 */
    int upd7 = link->aggiornaUser("utente2@p.it", "fenicottero", "paperella14", "");
    std::cout<<"Icona vuota: "<<upd7<<std::endl;

    std::cout<<"---------------------------------------------"<<std::endl;

    /* Fornisco l'uri del documento 1 */
    std::string doc0 = link->recuperaDocDatoURI("://GIMPdocs/80423b4c7a9c3e047148ececb88d1d41");
    std::cout<<"Dato l'URI ottengo il nome doc... "<<doc0<<std::endl;

    /* Fornisco un uri inesistente */
    std::string doc1 = link->recuperaDocDatoURI("://GIMPdocs/OIBABOIII");
    std::cout<<"URI inesistente... "<<doc1<<std::endl;

    /* Boundary case: stringa vuota */
    std::string doc2 = link->recuperaDocDatoURI("");
    std::cout<<"URI vuoto... "<<doc2<<std::endl;

    std::cout<<"---------------------------------------------"<<std::endl;

    return a.exec();
}