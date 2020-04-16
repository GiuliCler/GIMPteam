#include "collegamentoDB.h"
#include "sha256.h"
#include <vector>
#include <QCryptographicHash>

/*
 * Utilizzo: funzione che permette di collegarsi al database
 * Parametri:
 *      dbname: nome del database a cui collegarsi
 *      connectionName: nome della connessione
 *      hostname: default "localhost"
 *      username: default "root"
 *      pssw: default ""
 * Ritorno: nessuno
 */
void CollegamentoDB::connettiDB(const QString& dbname, const QString& connectionName, const QString& hostname, const QString& username, const QString& pssw){

    QSqlDatabase conn = QSqlDatabase::addDatabase("QMYSQL", connectionName);
    conn.setHostName(hostname);
    conn.setUserName(username);
    conn.setPassword(pssw);
    conn.setDatabaseName(dbname);

    if(conn.open()){
        std::cout << "Connessione con il DB effettuata correttamente" << std::endl;
    } else {
        std::cout << "Errore durante la connessione con il DB" << std::endl;
        qDebug() << conn.lastError();
    }

    // Salvo il nome della connessione nell'oggetto CollegamentoDB corrente
    this->connectionName = connectionName;
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
std::vector<QString> CollegamentoDB::login(QString username, QString password){
    std::vector<QString> ritorno;

    if(username.isEmpty() || password.isEmpty()) {
        ritorno.emplace_back("errore");
        return ritorno;
    }

    std::string query = "SELECT * FROM utenti WHERE username=:user";
    QSqlQuery ris(QSqlDatabase::database(connectionName));
    ris.prepare(QString::fromStdString(query));
    ris.bindValue(":user", username);

    if(ris.exec()){
        if(ris.size() == 1){
            while(ris.next()){

                QString pass_nel_DB = QString::fromStdString(ris.value(1).toByteArray().toStdString());
                QString sale = QString::fromStdString(ris.value(2).toByteArray().toStdString());
                QString pass_salata = password + sale;
                QString pass_da_testare = QString(QCryptographicHash::hash((pass_salata.toUtf8()),QCryptographicHash::Sha256));

                if(pass_nel_DB == pass_da_testare) {
                    /* password inserita corretta */
                    QString nickname = QString::fromStdString(ris.value(3).toByteArray().toStdString());
                    QString icona = QString::fromStdString(ris.value(4).toByteArray().toStdString());
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
int CollegamentoDB::signup(QString username, QString password, QString nickname, QString icona){

    if(username.isEmpty() || password.isEmpty() || nickname.isEmpty())
        return 0;

    char sale[10];
    gen_random(sale, 10);
    std::string sale_std(sale);
    QString sale_qt = QString::fromStdString(sale_std);
    QString pass_salata = password + sale_qt;
    QString pass_crypt = QString(QCryptographicHash::hash((pass_salata.toUtf8()),QCryptographicHash::Sha256));

    std::string query = "INSERT INTO utenti(username, password, sale, nickname, icona) VALUES(:user, :pssw, :salt, :nick, :icon)";
    QSqlQuery ris(QSqlDatabase::database(connectionName));
    ris.prepare(QString::fromStdString(query));
    ris.bindValue(":user", username);
    ris.bindValue(":pssw", pass_crypt);
    ris.bindValue(":salt", sale_qt);
    ris.bindValue(":nick", nickname);

    if(!icona.isEmpty())
        ris.bindValue(":icon", icona);
    else
        ris.bindValue(":icon", "NULL");

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
int CollegamentoDB::creaDoc(QString nomeDOC){

    if(nomeDOC.isEmpty())
        return 0;

    QString uri = creaURI(nomeDOC);

    std::string query = "INSERT INTO doc(nome_doc, uri) VALUES(:doc, :ur)";
    QSqlQuery ris(QSqlDatabase::database(connectionName));
    ris.prepare(QString::fromStdString(query));
    ris.bindValue(":doc", nomeDOC);
    ris.bindValue(":ur", uri);

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
QString CollegamentoDB::creaURI(QString nomeDOC){
    QString blah = QString(QCryptographicHash::hash(nomeDOC.toUtf8(),QCryptographicHash::Md5).toHex());
    QString s = "://GIMPdocs/" + blah;
    return s;
}

/*
 * Utilizzo: funzione che permette di recuperare il nome di un documento dato un certo URI
 * Parametri:
 *      uri: URI di un certo documento
 * Ritorno:
 *      tutto ok (URI presente nel DB) -> stringa corrispondente al nome del documento relativo all'URI passato
 *      errore (URI inesistente) -> "errore"
 */
QString CollegamentoDB::recuperaDocDatoURI(QString uri){

    if(uri.isEmpty()) {
        return "errore";
    }

    QString doc_cercato;
    std::string query = "SELECT * FROM doc WHERE uri=:ur";
    QSqlQuery ris(QSqlDatabase::database(connectionName));
    ris.prepare(QString::fromStdString(query));
    ris.bindValue(":ur", uri);

    if(ris.exec()){
        if(ris.size() == 1){
            while(ris.next()){
                doc_cercato = QString::fromStdString(ris.value(0).toByteArray().toStdString());
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
int CollegamentoDB::aggiungiPartecipante(QString nomeDOC, QString username){

    if(nomeDOC.isEmpty())
        return 2;

    int esito = 1;

    std::string query1 = "SELECT * FROM utente_doc WHERE username=:user AND nome_doc=:doc";
    std::string query2 = "INSERT INTO utente_doc(username, nome_doc) VALUES(:user, :doc)";
    std::string query3 = "SELECT * FROM doc WHERE nome_doc=:doc";
    QSqlQuery ris1(QSqlDatabase::database(connectionName)), ris2(QSqlDatabase::database(connectionName)), ris3(QSqlDatabase::database(connectionName));
    ris1.prepare(QString::fromStdString(query1));
    ris2.prepare(QString::fromStdString(query2));
    ris3.prepare(QString::fromStdString(query3));
    ris1.bindValue(":user", username);
    ris1.bindValue(":doc", nomeDOC);
    ris2.bindValue(":user", username);
    ris2.bindValue(":doc", nomeDOC);
    ris3.bindValue(":doc", nomeDOC);

//    if(QSqlDatabase::database().driver()->hasFeature(QSqlDriver::Transactions)){

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
//    }

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
std::vector<QString> CollegamentoDB::recuperaDocs(QString username){

    std::vector<QString> elenco;

    std::string query = "SELECT nome_doc FROM utente_doc WHERE username=:user";
    QSqlQuery ris(QSqlDatabase::database(connectionName));
    ris.prepare(QString::fromStdString(query));
    ris.bindValue(":user", username);

    ris.exec();

    if(ris.size() > 0){
        while(ris.next()){
            QString doc = QString::fromStdString(ris.value(0).toByteArray().toStdString());
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
QString CollegamentoDB::getNickname(QString username){

    //std::cout<<"SONO DENTRO LA getNickname e USERNAME E': "<<username.toStdString()<<std::endl;            // DEBUG

    std::string query = "SELECT nickname FROM utenti WHERE username=:user";
    QSqlQuery ris(QSqlDatabase::database(connectionName));
    ris.prepare(QString::fromStdString(query));
    ris.bindValue(":user", username);

    ris.exec();

    //std::cout<<"HO ESEGUITO LA EXEC"<<std::endl;            // DEBUG

    if(ris.size() > 0){
        //std::cout<<"SONO NELL'IF... ris.size() vale "<<ris.size()<<std::endl;            // DEBUG
        ris.next();
        //std::cout<<"STO PER MANDARE INDIETRO UNA COSA DI TIPO... "<<ris.value(0).typeName()<<std::endl;  // DEBUG
        return QString::fromStdString(ris.value(0).toByteArray().toStdString());
    } else {
        //std::cout<<"SONO NELL'ELSE"<<std::endl;            // DEBUG
        return "errore";
    }
}

QString CollegamentoDB::getIconId(QString username){

    std::string query = "SELECT icona FROM utenti WHERE username=:user";
    QSqlQuery ris(QSqlDatabase::database(connectionName));
    ris.prepare(QString::fromStdString(query));
    ris.bindValue(":user", username);

    ris.exec();

    if(ris.size() > 0){
        ris.next();
        return QString::fromStdString(ris.value(0).toByteArray().toStdString());
    } else {
        return "errore";
    }
}

/*
 * Utilizzo: funzione che permette di recuperare dalla tabella UTENTE_DOC tutti i collaboratori (utenti abilitati alla modifica)
 *           per un certo documento
 * Parametri:
 *      nomeDOC: documento di cui si devono conoscere i collaboratori
 * Ritorno:
 *      >0 collaboratori -> vettore composto da vettori con (username, nickname, icona) degli utenti collaboratori
 *      =0 collaboratori, ovvero no righe trovate in utente_doc -> vettore contenentente un solo vettore con ("no")
 *      errere -> vettore contenentente un solo vettore con ("errore")
 */
std::vector<std::vector<QString>> CollegamentoDB::recuperaCollaboratori(QString nomeDOC){
    std::vector<std::vector<QString>> ritorno;

    if(nomeDOC.isEmpty()){
        std::vector<QString> error;
        error.emplace_back("errore");
        ritorno.push_back(error);
        return ritorno;
    }

    std::string query = "SELECT utente_doc.username, nickname, icona FROM utenti, utente_doc WHERE utenti.username=utente_doc.username AND utente_doc.nome_doc=:doc";
    QSqlQuery ris(QSqlDatabase::database(connectionName));
    ris.prepare(QString::fromStdString(query));
    ris.bindValue(":doc", nomeDOC);

    if(ris.exec()){
        if(ris.size() == 0){

            /* No collaboratori per il doc nomeDoc */
            std::vector<QString> nocollab;
            nocollab.emplace_back("no");
            ritorno.push_back(nocollab);

        } else {

            /* Si, ci sono collaboratori per il doc nomeDoc */
            while(ris.next()){
                std::vector<QString> collaboratore;
                QString s;
                s = QString::fromStdString(ris.value(0).toByteArray().toStdString());   // username
                collaboratore.push_back(s);
                s = QString::fromStdString(ris.value(1).toByteArray().toStdString());   // nickname
                collaboratore.push_back(s);
                s = QString::fromStdString(ris.value(2).toByteArray().toStdString());   // icona
                collaboratore.push_back(s);
                ritorno.push_back(collaboratore);
            }

        }
    } else {
        std::vector<QString> error;
        error.emplace_back("errore");
        ritorno.push_back(error);
    }

    return ritorno;
}

/*
 * Utilizzo: funzione che permette di recuperare dalla tabella UTENTE_DOC il site_id e il site_counter di un certo utente,
 *           dato il suo username e il nome del documento
 * Parametri:
 *      username: utente che sta chiedendo l'accesso ad un dato documento
 *      nomeDOC: nome del documento
 * Ritorno:
 *      ok -> vettore composto da [site_id, site_counter]
 *      errore -> vettore composto dal solo valore -1
 */
std::vector<int> CollegamentoDB::recuperaInfoUtenteDoc(QString nomeDOC, QString username){

    std::vector<int> rit;

    if(nomeDOC.isEmpty() || username.isEmpty()){
        rit.push_back(-1);
        return rit;
    }

    std::string query = "SELECT site_id, site_counter FROM utente_doc WHERE username=:user AND nome_doc=:doc";
    QSqlQuery ris(QSqlDatabase::database(connectionName));
    ris.prepare(QString::fromStdString(query));
    ris.bindValue(":user", username);
    ris.bindValue(":doc", nomeDOC);

    ris.exec();

    if(ris.size() == 1){
        while(ris.next()){
            int id = ris.value(0).toInt();
            int counter = ris.value(1).toInt();
            rit.push_back(id);
            rit.push_back(counter);
        }
    } else {
        rit.push_back(-1);
    }

    return rit;
}

/*
 * Utilizzo: funzione che permette di eliminare una riga nella tabella UTENTE_DOC come conseguenza del fatto che un utente non voglia
 *           più partecipare alla modifica di un certo documento e che quindi voglia rimuoverlo dal suo elenco di documenti
 *           modificabili
 * Parametri:
 *      nomeDOC: nome del documento che l'utente vuole rimuovere
 *      username: utente in questione
 * Ritorno:
 *      1 -> riga della tabella UTENTE_DOC eliminata correttamente
 *      0 -> errore, riga relativa a (username, nomeDOC) non presente nella tabella UTENTE_DOC
 */
int CollegamentoDB::rimuoviPartecipante(QString nomeDOC, QString username){

    if(nomeDOC.isEmpty() || username.isEmpty())
        return 0;

    int esito = 1;

    std::string query1 = "SELECT * FROM utente_doc WHERE username=:user AND nome_doc=:doc";
    std::string query2 = "DELETE FROM utente_doc WHERE username=:user AND nome_doc=:doc";
    std::string query3 = "SELECT * FROM utente_doc WHERE nome_doc=:doc";
    std::string query4 = "DELETE FROM doc WHERE nome_doc=:doc";
    QSqlQuery ris1(QSqlDatabase::database(connectionName)), ris2(QSqlDatabase::database(connectionName)), ris3(QSqlDatabase::database(connectionName)), ris4(QSqlDatabase::database(connectionName));
    ris1.prepare(QString::fromStdString(query1));
    ris2.prepare(QString::fromStdString(query2));
    ris3.prepare(QString::fromStdString(query3));
    ris4.prepare(QString::fromStdString(query4));
    ris1.bindValue(":user", username);
    ris1.bindValue(":doc", nomeDOC);
    ris2.bindValue(":user", username);
    ris2.bindValue(":doc", nomeDOC);
    ris3.bindValue(":doc", nomeDOC);
    ris4.bindValue(":doc", nomeDOC);

    if(QSqlDatabase::database().driver()->hasFeature(QSqlDriver::Transactions)){

        QSqlDatabase::database().transaction();

        ris1.exec();
        if(ris1.size() != 1){

            /* Non esiste alcuna riga all'interno della tabella UTENTE_DOC con i parametri specificati */
            esito = 0;

        } else {

            /* Riga (username, nomeDOC) esistente nella tabella UTENTE_DOC --> elimino tale riga dalla tabella UTENTE_DOC */
            ris2.exec();

            /* Verifico se esistono altre righe nella tabella UTENTE_DOC relative al documento nomeDOC e, se non esistono,
             * cancello il documento dalla tabella DOC */
            ris3.exec();
            if(ris3.size() == 0){
                ris4.exec();
            }

            QSqlDatabase::database().commit();

        }
    }

    return esito;
}

/*
 * Utilizzo: funzione che permette di aggiornare il site_counter di un certo utente relativo ad un certo documento
 * Parametri:
 *      username: utente in questione
 *      nomeDOC: documento in questione
 *      siteCount: nuovo site_counter
 * Ritorno:
 *      1 -> site_counter aggiornato correttamente
 *      0 -> errore
 */
int CollegamentoDB::aggiornaSiteCounter(QString nomeDOC, QString username, int siteCount){
    if(username.isEmpty() || nomeDOC.isEmpty())
        return 0;

    std::string query0 = "SELECT site_id FROM utente_doc WHERE username=:user AND nome_doc=:doc";
    QSqlQuery ris0(QSqlDatabase::database(connectionName));
    ris0.prepare(QString::fromStdString(query0));
    ris0.bindValue(":user", username);
    ris0.bindValue(":doc", nomeDOC);

    if(QSqlDatabase::database().driver()->hasFeature(QSqlDriver::Transactions)) {

        QSqlDatabase::database().transaction();

        if(ris0.exec()){
            if(ris0.size() == 1){

                int id = ris0.value(0).toInt();

                QSqlQuery risDEL(QSqlDatabase::database(connectionName));
                risDEL.prepare("DELETE FROM utente_doc WHERE username=:user AND nome_doc=:doc");
                risDEL.bindValue(":user", username);
                risDEL.bindValue(":doc", nomeDOC);
                risDEL.exec();

                std::string query = "INSERT INTO utente_doc(username, nome_doc, site_id, site_counter) VALUES(:user, :doc, :siteid, :sitecounter)";
                QSqlQuery ris(QSqlDatabase::database(connectionName));
                ris.prepare(QString::fromStdString(query));
                ris.bindValue(":user", username);
                ris.bindValue(":doc", nomeDOC);
                ris.bindValue(":siteid", QString::number(id));
                ris.bindValue(":sitecounter", QString::number(siteCount));

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

/*
 * Utilizzo: funzione che consente di recuperare l'URI di un certo documento, per permetterne la condivisione con altri utenti
 * Parametri:
 *      nomeDOC: nome del documento di cui si vuole recuperare l'URI
 * Ritorno:
 *      tutto ok -> stringa corrispondente all'URI del documento di interesse
 *      errore -> "errore"
 */
QString CollegamentoDB::recuperaURI(QString nomeDOC){

    if(nomeDOC.isEmpty())
        return "errore";

    QString uri;
    std::string query = "SELECT uri FROM doc WHERE nome_doc=:doc";
    QSqlQuery ris(QSqlDatabase::database(connectionName));
    ris.prepare(QString::fromStdString(query));
    ris.bindValue(":doc", nomeDOC);

    ris.exec();

    if(ris.size() == 1){
        while(ris.next()){
            uri = QString::fromStdString(ris.value(0).toByteArray().toStdString());
        }
    } else {
        uri = "errore";
    }

    return uri;
}

/*
 * Utilizzo: funzione che permette di recuperare dalla tabella DOC tutti i documenti presenti
 * Parametri:
 *      //
 * Ritorno:
 *      >0 documenti -> vettore composto dai nomi dei documenti presenti nel DB
 *      =0 documenti -> vettore contenentente il solo elemento "nessuno"
 */
std::vector<QString> CollegamentoDB::recuperaDocsNelDB(){
    std::vector<QString> elenco;

    std::string query = "SELECT nome_doc FROM doc";
    QSqlQuery ris(QSqlDatabase::database(connectionName));
    ris.prepare(QString::fromStdString(query));

    ris.exec();

    if(ris.size() > 0){
        while(ris.next()){
            QString doc = QString::fromStdString(ris.value(0).toByteArray().toStdString());
            elenco.push_back(doc);
        }
    } else {
        elenco.emplace_back("nessuno");
    }

    return elenco;
}


/*
 * Utilizzo: funzione che permette di recuperare dalla tabella UTENTI tutti gli utenti presenti
 * Parametri:
 *      //
 * Ritorno:
 *      >0 utenti -> vettore composto dagli username degli utenti presenti nel DB
 *      =0 utenti -> vettore contenentente il solo elemento "nessuno"
 */
std::vector<QString> CollegamentoDB::recuperaUtentiNelDB(){
    std::vector<QString> elenco;

    std::string query = "SELECT username FROM utenti";
    QSqlQuery ris(QSqlDatabase::database(connectionName));
    ris.prepare(QString::fromStdString(query));

    ris.exec();

    if(ris.size() > 0){
        while(ris.next()){
            QString user = QString::fromStdString(ris.value(0).toByteArray().toStdString());
            elenco.push_back(user);
        }
    } else {
        elenco.emplace_back("nessuno");
    }

    return elenco;
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
int CollegamentoDB::aggiornaUser(QString username, QString nuova_password, QString nuovo_nickname, QString nuova_icona){

    std::cout<<"SONO NELLA aggiornaUser"<<std::endl;        // DEBUG

    if(username.isEmpty() || nuova_password.isEmpty() || nuovo_nickname.isEmpty())
        return 0;

    std::string query0 = "SELECT * FROM utenti WHERE username=:user0";
    QSqlQuery ris0(QSqlDatabase::database(connectionName));
    ris0.prepare(QString::fromStdString(query0));
    ris0.bindValue(":user0", username);

//    if(QSqlDatabase::database().driver()->hasFeature(QSqlDriver::Transactions)) {

        QSqlDatabase::database().transaction();

        if(ris0.exec()){
            if(ris0.size() == 1){
                char sale[10];
                gen_random(sale, 10);
                std::string sale_std(sale);
                QString sale_qt = QString::fromStdString(sale_std);
                QString pass_salata = nuova_password + sale_qt;
                QString pass_crypt = QString(QCryptographicHash::hash((pass_salata.toUtf8()),QCryptographicHash::Sha256));

                QSqlQuery risDEL(QSqlDatabase::database(connectionName));
                risDEL.prepare("DELETE FROM utenti WHERE username=:user");
                risDEL.bindValue(":user", username);
                risDEL.exec();

                std::string query = "INSERT INTO utenti(username, password, sale, nickname, icona) VALUES(:user, :pssw, :salt, :nick, :icon)";
                QSqlQuery ris(QSqlDatabase::database(connectionName));
                ris.prepare(QString::fromStdString(query));
                ris.bindValue(":user", username);
                ris.bindValue(":pssw", pass_crypt);
                ris.bindValue(":salt", sale_qt);
                ris.bindValue(":nick", nuovo_nickname);

                if(!nuova_icona.isEmpty())
                    ris.bindValue(":icon", nuova_icona);
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

//    } else {
//        return 0;
//    }
}
