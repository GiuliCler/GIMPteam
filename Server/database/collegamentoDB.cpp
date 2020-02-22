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

    if(username.empty() || password.empty()) {
        ritorno.emplace_back("errore");
        return ritorno;
    }

    std::string query = "SELECT * FROM utenti WHERE username=:user";
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
                    /* password inserita corretta */
                    std::string nickname = ris.value(3).toString().toUtf8().constData();
                    std::string icona = ris.value(4).toString().toUtf8().constData();
                    ritorno.push_back(nickname);
                    ritorno.push_back(icona);
                } else {
                    /* Password inserita non corretta */
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
 *      icona --> nome di immagine   oppure   "" in caso di immagine assente
 *
 * Ritorno:
 *      1 -> username e password correttamente inseriti nel database
 *      0 -> errore
 */
int CollegamentoDB::signup(std::string username, std::string password, std::string nickname, std::string icona){

    if(username.empty() || password.empty() || nickname.empty())
        return 0;

    char sale[10];
    gen_random(sale, 10);
    std::string salt(sale);
    std::string pass = sha256(password + sale);

    std::string query = "INSERT INTO utenti(username, password, sale, nickname, icona) VALUES(:user, :pssw, :salt, :nick, :icon)";
    QSqlQuery ris;
    ris.prepare(QString::fromStdString(query));
    ris.bindValue(":user", QString::fromStdString(username));
    ris.bindValue(":pssw", QString::fromStdString(pass));
    ris.bindValue(":salt", QString::fromStdString(salt));
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

    if(nomeDOC.empty())
        return 0;

    std::string uri = creaURI(nomeDOC);

    std::string query = "INSERT INTO doc(nome_doc, uri) VALUES(:doc, :ur)";
    QSqlQuery ris;
    ris.prepare(QString::fromStdString(query));
    ris.bindValue(":doc", QString::fromStdString(nomeDOC));
    ris.bindValue(":ur", QString::fromStdString(uri));

    if(!ris.exec())
        return 0;

    return 1;
}

/*
 * Utilizzo: funzione che crea un URI partendo dal nome del documento passato come parametro
 * Parametri:
 *      nomeDOC: nome del documento di cui si vuole creare l'URI
 * Ritorno:
 *      stringa corrispondente all'URI creata
 */
std::string CollegamentoDB::creaURI(std::string nomeDOC){
    QByteArray byteArray(nomeDOC.c_str(), nomeDOC.length());
    QString blah = QString(QCryptographicHash::hash((byteArray),QCryptographicHash::Md5).toHex());
    QString s = "://GIMPdocs/" + blah;
    return s.toUtf8().constData();
}

/*
 * Utilizzo: funzione che permette di recuperare il nome di un documento dato un certo URI
 * Parametri:
 *      uri: URI di un certo documento
 * Ritorno:
 *      tutto ok (URI presente nel DB) -> stringa corrispondente al nome del documento relativo all'URI passato
 *      errore (URI inesistente) -> "errore"
 */
std::string CollegamentoDB::recuperaDocDatoURI(std::string uri){

    if(uri.empty()) {
        return "errore";
    }

    std::string doc_cercato;
    std::string query = "SELECT * FROM doc WHERE uri=:ur";
    QSqlQuery ris;
    ris.prepare(QString::fromStdString(query));
    ris.bindValue(":ur", QString::fromStdString(uri));

    if(ris.exec()){
        if(ris.size() == 1){
            while(ris.next()){
                doc_cercato = ris.value(0).toString().toUtf8().constData();
            }
        } else {
            return "errore";
        }
    }
    else{
        return "errore";
    }

    return doc_cercato;
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
 *      2 -> Il documento di cui è stato fornito il nome non esiste nella tabella DOC oppure è stata fornita
 *           una stringa vuota
 */
int CollegamentoDB::aggiungiPartecipante(std::string nomeDOC, std::string username){

    if(nomeDOC.empty())
        return 2;

    int esito = 1;

    std::string query1 = "SELECT * FROM utente_doc WHERE username=:user AND nome_doc=:doc";
    std::string query2 = "INSERT INTO utente_doc(username, nome_doc) VALUES(:user, :doc)";
    std::string query3 = "SELECT * FROM doc WHERE nome_doc=:doc";
    QSqlQuery ris1, ris2, ris3;
    ris1.prepare(QString::fromStdString(query1));
    ris2.prepare(QString::fromStdString(query2));
    ris3.prepare(QString::fromStdString(query3));
    ris1.bindValue(":user", QString::fromStdString(username));
    ris1.bindValue(":doc", QString::fromStdString(nomeDOC));
    ris2.bindValue(":user", QString::fromStdString(username));
    ris2.bindValue(":doc", QString::fromStdString(nomeDOC));
    ris3.bindValue(":doc", QString::fromStdString(nomeDOC));

    if(QSqlDatabase::database().driver()->hasFeature(QSqlDriver::Transactions)){

        QSqlDatabase::database().transaction();

        ris3.exec();
        if(ris3.size() == 0){

            /* Non esiste alcuna riga all'interno della tabella DOC con il nomeDOC specificato */
            esito = 2;

        } else {

            ris1.exec();

            /* "Esiste già una riga nella tabella UTENTE_DOC corrispondente alla coppia (username,nomeDOC)?" */
            if(ris1.size() != 0){
                /* L'utente è già stato abilitato alla modifica del documento */
                esito = 0;
                QSqlDatabase::database().commit();
            } else {
                /* L'utente non è ancora stato abilitato alla modifica del documento */
                ris2.exec();
                QSqlDatabase::database().commit();
            }
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

    std::string query = "SELECT nome_doc FROM utente_doc WHERE username=:user";
    QSqlQuery ris;
    ris.prepare(QString::fromStdString(query));
    ris.bindValue(":user", QString::fromStdString(username));

    ris.exec();

    if(ris.size() > 0){
        while(ris.next()){
            std::string doc;
            doc = ris.value(0).toString().toUtf8().constData();

            elenco.push_back(doc);
        }
    } else {
        elenco.emplace_back("nessuno");
    }

    return elenco;
}
/*
 * Funzione che ritorna il nickname dato username.
 * Se tutto ok => nickname
 * Se errore => stringa vuota
 *
 */
std::string CollegamentoDB::getNickname(std::string username){

    std::string query = "SELECT nickname FROM utenti WHERE username=:user";
    QSqlQuery ris;
    ris.prepare(QString::fromStdString(query));
    ris.bindValue(":user", QString::fromStdString(username));

    ris.exec();

    if(ris.size() > 0){
        ris.next();
        return ris.value(0).toString().toStdString();
    } else {
        return "errore";
    }
}

std::string CollegamentoDB::getIconId(std::string username){

    std::string query = "SELECT icona FROM utenti WHERE username=:user";
    QSqlQuery ris;
    ris.prepare(QString::fromStdString(query));
    ris.bindValue(":user", QString::fromStdString(username));

    ris.exec();

    if(ris.size() > 0){
        ris.next();
        return ris.value(0).toString().toStdString();
    } else {
        return "errore";
    }
}


/*
 * Utilizzo: funzione che consente di recuperare l'URI di un certo documento, per permetterne la condivisione con altri utenti
 * Parametri:
 *      nomeDOC: nome del documento di cui si vuole recuperare l'URI
 * Ritorno:
 *      tutto ok -> stringa corrispondente all'URI del documento di interesse
 *      errore -> "errore"
 */
std::string CollegamentoDB::recuperaURI(std::string nomeDOC){

    if(nomeDOC.empty())
        return "errore";

    std::string uri;
    std::string query = "SELECT uri FROM doc WHERE nome_doc=:doc";
    QSqlQuery ris;
    ris.prepare(QString::fromStdString(query));
    ris.bindValue(":doc", QString::fromStdString(nomeDOC));

    ris.exec();

    if(ris.size() == 1){
        while(ris.next()){
            uri = ris.value(0).toString().toUtf8().constData();
        }
    } else {
        uri = "errore";
    }

    return uri;
}


/*
 * Utilizzo: funzione che permette di aggiornare le informazioni relative ad un utente già presente nel DB
 * Parametri:
 *      username, nuova_password  e nuovo_nickname dell'utente da modificare
 *      nuova_icona --> nome di immagine   oppure   "" in caso di immagine assente
 *
 * Ritorno:
 *      1 -> info relative all'utente aggiornate correttamente
 *      0 -> errore
 */

// -------- CON UPDATE --------
/*int CollegamentoDB::aggiornaUser(std::string username, std::string nuova_password, std::string nuovo_nickname, std::string nuova_icona){

    if(username.empty() || nuova_password.empty() || nuovo_nickname.empty())
        return 0;

    std::string query0 = "SELECT * FROM utenti WHERE username=:user0";
    QSqlQuery ris0;
    ris0.prepare(QString::fromStdString(query0));
    ris0.bindValue(":user0", QString::fromStdString(username));

    if(ris0.exec()){
        if(ris0.size() == 1){
            char sale[10];
            gen_random(sale, 10);
            std::string salt(sale);
            std::string pass = sha256(nuova_password + sale);

            std::string query = "UPDATE utenti SET password=:pssw, sale=:salt, nickname=:nick, icona=:icon WHERE username=:user";
            QSqlQuery ris;
            ris.prepare(QString::fromStdString(query));
            ris.bindValue(":pssw", QString::fromStdString(pass));
            ris.bindValue(":salt", QString::fromStdString(salt));
            ris.bindValue(":nick", QString::fromStdString(nuovo_nickname));

            if(!nuova_icona.empty())
                ris.bindValue(":icon", QString::fromStdString(nuova_icona));
            else
                ris.bindValue(":icon", QString::fromStdString("NULL"));

            ris.bindValue(":user", QString::fromStdString(username));

            if(ris.exec())
                return 1;
            else
                return 0;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

*/

// -------- CON DELETE/INSERT --------
int CollegamentoDB::aggiornaUser(std::string username, std::string nuova_password, std::string nuovo_nickname, std::string nuova_icona){

    if(username.empty() || nuova_password.empty() || nuovo_nickname.empty())
        return 0;

    std::string query0 = "SELECT * FROM utenti WHERE username=:user0";
    QSqlQuery ris0;
    ris0.prepare(QString::fromStdString(query0));
    ris0.bindValue(":user0", QString::fromStdString(username));

    if(QSqlDatabase::database().driver()->hasFeature(QSqlDriver::Transactions)) {

        QSqlDatabase::database().transaction();

        if(ris0.exec()){
            if(ris0.size() == 1){
                char sale[10];
                gen_random(sale, 10);
                std::string salt(sale);
                std::string pass = sha256(nuova_password + sale);

                QSqlQuery risDEL;
                risDEL.prepare("DELETE FROM utenti WHERE username=:user");
                risDEL.bindValue(":user", QString::fromStdString(username));
                risDEL.exec();

                std::string query = "INSERT INTO utenti(username, password, sale, nickname, icona) VALUES(:user, :pssw, :salt, :nick, :icon)";
                QSqlQuery ris;
                ris.prepare(QString::fromStdString(query));
                ris.bindValue(":user", QString::fromStdString(username));
                ris.bindValue(":pssw", QString::fromStdString(pass));
                ris.bindValue(":salt", QString::fromStdString(salt));
                ris.bindValue(":nick", QString::fromStdString(nuovo_nickname));

                if(!nuova_icona.empty())
                    ris.bindValue(":icon", QString::fromStdString(nuova_icona));
                else
                    ris.bindValue(":icon", QString::fromStdString("NULL"));

                if(ris.exec()){
                    QSqlDatabase::database().commit();
                    return 1;
                } else {
                    QSqlDatabase::database().commit();
                    return 0;
                }
            } else {
                QSqlDatabase::database().commit();
                return 0;
            }
        } else {
            QSqlDatabase::database().commit();
            return 0;
        }

    } else {
        return 0;
    }
}




