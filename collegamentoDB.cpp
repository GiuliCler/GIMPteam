//
// Created by ilaria on 04/09/2019.
//

#include "collegamentoDB.h"
#include "sha256.h"
#include <vector>

/*
 * Utilizzo: funzione che permette di collegarsi al database
 * Parametri:
 *      dbname: nome del database a cui collegarsi
 *      hostname: default "localhost"
 *      username: default "root"
 *      pssw: default ""
 * Ritorno: nessuno
 */
void CollegamentoDB::connettiDB(const QString& dbname, const QString& hostname, const QString& username, const QString& pssw){

    QSqlDatabase conn = QSqlDatabase::addDatabase("QMYSQL");
    conn.setHostName(hostname);
    conn.setUserName(username);
    conn.setPassword(pssw);
    conn.setDatabaseName(dbname);

    if(conn.open()){
        std::cout << "Connessione con il DB effettuata correttamente" << std::endl;
    } else {
        std::cout << "Errore durante la connessione con il DB" << std::endl;
    }
}

/*
 * Utilizzo: funzione che permette di scollegarsi dal database
 * Parametri: nessuno
 * Ritorno: nessuno
 */
void CollegamentoDB::disconnettiDB(){
    QSqlDatabase::database().close();
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
}

/*
 * Utilizzo: funzione che permette di accedere al servizio, passando due stringhe (username e password) e
 *           verificando che esse corrispondano alle credenziali di un utente presente nel database
 * Parametri: username e password dell'utente che vuole effettuare l'accesso
 * Ritorno:
 *      tutto ok -> vettore composto da due stringhe: nickname e icona
 *      errore -> vettore composto da una sola stringa "errore"
 */
std::vector<std::string> CollegamentoDB::login(std::string username, std::string password){
    std::vector<std::string> ritorno;

    std::string query = "SELECT * FROM utenti WHERE username=\':user\'";
    QSqlQuery ris;
    ris.prepare(QString::fromStdString(query));
    ris.bindValue(":user", QString::fromStdString(username));

    if(ris.exec()){
        if(ris.size() == 1){
            while(ris.next()){
                std::string pass_nel_DB = ris.value(1).toString().toUtf8().constData();
                std::string sale = ris.value(2).toString().toUtf8().constData();

                std::string pass_da_testare = sha256(password + sale);
                if(pass_nel_DB == pass_da_testare) {
                    // password inserita corretta
                    std::string nickname = ris.value(3).toString().toUtf8().constData();
                    std::string icona = ris.value(4).toString().toUtf8().constData();
                    ritorno.push_back(nickname);
                    ritorno.push_back(icona);                    
                } else {
                    // Password inserita non corretta
                    ritorno.emplace_back("errore");
                }
            }
        } else {
            ritorno.emplace_back("errore");
        }
    }
    else{
        ritorno.emplace_back("errore");
    }

    return ritorno;
}

/*
 * Utilizzo: funzione che permette di registrarsi al servizio, passando due stringhe (username e password) e
 *           inserendole all'interno del database
 * Parametri:
 *      username, password  e nickname dell'utente che vuole effettuare la registrazione
 *      icona --> nome di immagine caricata   oppure   "" in caso di immagine assente
 *
 * Ritorno:
 *      1 -> username e password correttamente inseriti nel database
 *      0 -> errore
 */
int CollegamentoDB::signup(std::string username, std::string password, std::string nickname, std::string icona){

    char sale[10];
    gen_random(sale, 10);
    std::string pass = sha256(password + sale);

    std::string query = "INSERT INTO utenti() VALUES(\':user\', \':pssw\', \':salt\', \':nick\', \':icon\')";
    QSqlQuery ris;
    ris.prepare(QString::fromStdString(query));
    ris.bindValue(":user", QString::fromStdString(username));
    ris.bindValue(":pssw", QString::fromStdString(pass));
    ris.bindValue(":salt", QString::fromStdString(sale));
    ris.bindValue(":nick", QString::fromStdString(nickname));

    if(!icona.empty())
        ris.bindValue(":icon", QString::fromStdString(icona));
    else
        ris.bindValue(":icon", QString::fromStdString("NULL"));

    if(ris.exec())
        return 1;
    else
        return 0;
}

/*
 * Utilizzo: funzione che permette di generare una stringa di caratteri casuali
 * Parametri:
 *      s: stringa destinazione
 *      len: lunghezza della stringa
 * Ritorno: nessuno
 */
void CollegamentoDB::gen_random(char *s, const int len) {

    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}

/*
 * Utilizzo: funzione che permette di creare una nuova riga corrispondente ad un nuovo documento
 *           all'interno della tabella DOC del database
 * Parametri:
 *      nomeDOC: nome del nuovo documento da inserire nella tabella DOC del database
 * Ritorno:
 *      1 -> tutto ok
 *      0 -> errore
 */
int CollegamentoDB::creaDoc(std::string nomeDOC){

    int ok = 1;
    std::string uri = creaURI(nomeDOC);

    std::string query = "INSERT INTO doc(nome_doc, uri) VALUES (\':doc\', \':ur\')";
    QSqlQuery ris;
    ris.prepare(QString::fromStdString(query));
    ris.bindValue(":doc", QString::fromStdString(nomeDOC));
    ris.bindValue(":ur", QString::fromStdString(uri));

    bool esito = ris.exec(QString::fromStdString(query));
    if(!esito)
        ok = 0;

    return ok;
}

/*
 * Utilizzo: funzione che crea un URI partendo dal nome del documento passato come parametro
 * Parametri:
 *      nomeDOC: nome del documento di cui si vuole creare l'URI
 * Ritorno:
 *      stringa corrispondente all'URI creata
 */
std::string CollegamentoDB::creaURI(std::string nomeDOC){
    // TODO -------------------------------------------------------------------------------------------------
}

/*
 * Utilizzo: funzione che permette di creare una nuova riga nella tabella UTENTE_DOC, corrispondente
 *           al nuovo permesso di modifica di un documento da parte di un nuovo partecipante
 * Parametri:
 *      nomeDOC: nome del documento a cui l'utente può accedere per la prima volta
 *      username: nuovo partecipante alla modifica del documento in questione
 * Ritorno:
 *      1 -> L'utente non è ancora stato abilitato alla modifica del documento, quindi la riga
 *           (username,nomeDOC) è stata aggiunta alla tabella UTENTE_DOC
 *      0 -> L'utente è già stato abilitato alla modifica del documento, ovvero è già presente una riga
 *           con (username,nomeDOC) nella tabella UTENTE_DOC
 */
int CollegamentoDB::aggiungiPartecipante(std::string nomeDOC, std::string username){

    int esito = 1;

    std::string query1 = "SELECT * FROM utente_doc WHERE username=\':user\' AND nome_doc=\':doc\'";
    std::string query2 = "INSERT INTO utente_doc(username, nome_doc) VALUES (\':user\', \':doc\')";
    QSqlQuery ris1, ris2;
    ris1.prepare(QString::fromStdString(query1));
    ris2.prepare(QString::fromStdString(query2));
    ris1.bindValue(":user", QString::fromStdString(username));
    ris1.bindValue(":doc", QString::fromStdString(nomeDOC));
    ris2.bindValue(":user", QString::fromStdString(username));
    ris2.bindValue(":doc", QString::fromStdString(nomeDOC));

    if(QSqlDatabase::database().driver()->hasFeature(QSqlDriver::Transactions)){

        QSqlDatabase::database().transaction();
        ris1.exec(QString::fromStdString(query1));

        // "Esiste già una riga nella tabella UTENTE_DOC corrispondente alla coppia (username,nomeDOC)?"
        if(ris1.size() == 0){
            // L'utente è già stato abilitato alla modifica del documento
            esito = 0;
            QSqlDatabase::database().commit();
        } else {
            // L'utente non è ancora stato abilitato alla modifica del documento
            ris2.exec(QString::fromStdString(query2));
            QSqlDatabase::database().commit();
        }
    }

    return esito;
}

/*
 * Utilizzo: funzione che permette di recuperare dalla tabella UTENTE_DOC tutti i documenti che un certo utente è
 *           abilitato a modificare
 * Parametri:
 *      username: utente di cui si devono mostrare i documenti che possono essere da lui modificati
 * Ritorno:
 *      >0 documenti modificabili -> vettore composto dai nomi dei documenti che l'utente è abilitato a modificare
 *      =0 documenti modificabili -> vettore contenentente il solo elemento "nessuno"
 */
std::vector<std::string> CollegamentoDB::recuperaDocs(std::string username){

    std::vector<std::string> elenco;

    std::string query = "SELECT nome_doc FROM utente_doc WHERE username=\':user\'";
    QSqlQuery ris;
    ris.prepare(QString::fromStdString(query));
    ris.bindValue(":user", QString::fromStdString(username));

    ris.exec(QString::fromStdString(query));

    if(ris.size() > 0){
        while(ris.next()){
            std::string doc;
            doc = ris.value(1).toString().toUtf8().constData();
            elenco.push_back(doc);
        }
    } else {
        elenco.emplace_back("nessuno");
    }

    return elenco;
}


/*
 * Utilizzo: funzione che permette di recuperare l'URI di un certo documento
 * Parametri:
 *      nomeDOC: nome del documento di cui si vuole recuperare l'URI
 * Ritorno:
 *      tutto ok -> stringa corrispondente all'URI del documento di interesse
 *      errore -> "errore"
 */
std::string CollegamentoDB::recuperaURI(std::string nomeDOC){

    std::string uri;

    std::string query = "SELECT uri FROM doc WHERE nome_doc=\':doc\'";
    QSqlQuery ris;
    ris.prepare(QString::fromStdString(query));
    ris.bindValue(":doc", QString::fromStdString(nomeDOC));

    ris.exec(QString::fromStdString(query));

    if(ris.size() == 1){
        while(ris.next()){
            uri = ris.value(2).toString().toUtf8().constData();
        }
    } else {
        uri = "errore";
    }

    return uri;
}