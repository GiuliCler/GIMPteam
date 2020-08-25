#include "thread_body.h"
#include <iostream>
#include <sstream>
#include <QThread>

Thread_body::Thread_body(int socketDescriptor, QThread* server, QObject *parent) : QObject(parent), server(server), current_docId(-1), readBuffer(), readBuffer_size(0)
{
    auto thread_id = std::this_thread::get_id();

    std::cout << "ThreadBody constructor id: "<<thread_id<< std::endl;      // DEBUG

    socket = new QTcpSocket();
    if (!socket->setSocketDescriptor(socketDescriptor)) {
        socket->disconnectFromHost();       //altrimenti non accetta più connessioni da altri client...
        emit error(socket->error());
        return;
    }

    // Creo nel thread un collegamento al DB, mettendo come nome univoco di connessione "connSOCKETDESCRIPTOR"
    database = new CollegamentoDB();
    database->connettiDB("gimpdocs_db", "conn" + threadId_toQString(thread_id));

    QObject::connect(this, &Thread_body::dataReceived, this, &Thread_body::executeJob);
}

Thread_body::~Thread_body(){
    std::cout<<"STO DISTRUGGENDO IL THREAD_BODY"<<std::endl;            // DEBUG
}

void Thread_body::executeJob(QByteArray data){

//    qDebug()<<"##############################################################";        // DEBUG
//    qDebug()<<data;                                                                    // DEBUG
//    qDebug()<<"##############################################################";        // DEBUG

    auto thread_id = std::this_thread::get_id();
    std::cout << "THREAD - executeJob (inizio); Thread_id: "<<thread_id<< std::endl;            // DEBUG

    QDataStream in_data(&data, QIODevice::ReadOnly);
    in_data.setVersion(QDataStream::Qt_5_12);

    // Prendo la stringa di comando
    QByteArray text;
    in_data >> text;

    qDebug() << "THREAD - executeJob - Prima della verifica del comando... il comando e': "<< QString::fromStdString(text.toStdString());      // DEBUG

    QString c = "CREATE";
    if(text.contains(c.toUtf8())){
        //        qDebug() << "SONO DENTRO LA CREATE";             // DEBUG
        QString username, password, nickname, icon;
        in_data >> username;
        in_data >> password;
        in_data >> nickname;
        in_data >> icon;

        create(username, password, nickname, icon);
    }

    c = "LOGIN";
    if(text.contains(c.toUtf8())){
        //qDebug()<< "THREAD - Sono nella LOGIN";        // DEBUG
        QString username, password;
        in_data >> username;
        in_data >> password;

        login(username, password);
    }

    c = "LOGOUT";
    if(text.contains(c.toUtf8())){

        int userId;
        in_data >> userId;

        std::cout<<"LOGOUT - Ricevuto dal client lo userId: "<<userId<<std::endl;           // DEBUG

        logout(userId);
    }

    c = "DELETE_DOC";
    if(text.contains(c.toUtf8())){
        int docId, userId;
        in_data >> userId;
        in_data >> docId;

        deleteDoc(userId, docId);
    }

    c = "GET_DOC_TEXT";
    if(text.contains(c.toUtf8())){
        int docId, userId;
        in_data >> docId;
        in_data >> userId;

        getDocText(docId, userId);
    }

    c = "UPDATE";
    if(text.contains(c.toUtf8())){
        //        qDebug()<<"SONO DENTRO LA UPDATE";          // DEBUG
        QString password, nickname, icon;
        int userId;
        in_data >> userId;
        in_data >> password;
        in_data >> nickname;
        in_data >> icon;

        update(userId, password, nickname, icon);
    }

    c = "GET_USERNAME";
    if(text.contains(c.toUtf8())){
        int userId;
        in_data >> userId;

        retrieveUsername(userId);
    }

    c = "GET_NICKNAME";
    if(text.contains(c.toUtf8())){
        //qDebug()<< "SONO DENTRO LA GET_NICKNAME";             // DEBUG
        int userId;
        in_data >> userId;

        getNickname(userId);
    }

    c = "GET_DOC_NAME";
    if(text.contains(c.toUtf8())){
        int docId;
        in_data >> docId;

        retrieveDocName(docId);
    }

    c = "GET_ICON";
    if(text.contains(c.toUtf8())){
        //qDebug()<< "SONO DENTRO LA GET_ICON";             // DEBUG
        int userId;
        in_data >> userId;

        getIcon(userId);
    }

    c = "GET_DOCS";
    if(text.contains(c.toUtf8())){
        int userId;
        in_data >> userId;

        getDocs(userId);
    }

    c = "OPENDOC_DATO_URI";
    if(text.contains(c.toUtf8())){
        QString uri;
        int userId;
        in_data >> uri;
        in_data >> userId;

        openDocDatoUri(uri, userId);
    }

    c = "GET_URI";
    if(text.contains(c.toUtf8())){
        int docId;
        in_data >> docId;

        getUri(docId);
    }

    c = "GET_DOC_OWNER";
    if(text.contains(c.toUtf8())){
        int docId;
        in_data >> docId;

        getOwnerId(docId);
    }

    c = "GET_WORKINGUSERS_ONADOC";
    if(text.contains(c.toUtf8())){
        int docId;
        in_data >> docId;

        getWorkingUsersGivenDoc(docId);
    }

    c = "GET_CONTRIBUTORS_ONADOC";
    if(text.contains(c.toUtf8())){
        int docId;
        in_data >> docId;

        getCollaboratorsGivenDoc(docId);
    }

    c = "NEW_DOC";
    if(text.contains(c.toUtf8())){
        QString docName;
        int userId;
        in_data >> docName;
        in_data >> userId;

        newDoc(docName, userId);
    }

    c = "OPEN_DOC";
    if(text.contains(c.toUtf8())){
        int docId, userId;
        in_data >> docId;
        in_data >> userId;

        openDocument(docId, userId);
    }

    c = "SEND";
    if(text.contains(c.toUtf8())){

        CRDT_Message messaggio;
        in_data >> messaggio;

        std::cout << "if SEND - azione: "<<messaggio.getAzione()<< std::endl;           // DEBUG
        emit messageToServer(messaggio, threadId_toQString(thread_id), current_docId);
    }

    c = "DISCONNECT_FROM_DOC";
    if(text.contains(c.toUtf8())){

        int docId, userId;
        in_data >> docId;
        in_data >> userId;

        closeDocument(docId, userId);
    }

    //    socket->disconnectFromHost();
    //    socket->waitForDisconnected(3000);

    std::cout << "THREAD - executeJob (fine); Thread_id: "<<thread_id<< std::endl;            // DEBUG
}


QString Thread_body::getUsername(int userId){
    QString username = "";
    mutex_users->lock();
    QMapIterator<QString, int> i(users);
    while (i.hasNext()) {
        i.next();
        if(i.value()==userId){
            username=i.key();
            break;
        }
    }
    mutex_users->unlock();

    return username;
}

QString Thread_body::getDocname(int docId){
    QString docName = "";
    mutex_docs->lock();
    QMapIterator<QString, int> j(documents);
    while (j.hasNext()) {
        j.next();
        if(j.value()==docId){
            docName=j.key();
            break;
        }
    }
    mutex_docs->unlock();

    return docName;
}

QString Thread_body::threadId_toQString(std::thread::id id){
    std::stringstream ss;
    ss << id;
    std::string str = ss.str();
    return QString::fromStdString(str);
}

// NOTA: open_new è un flag che indica da dove è stata chiamata la connect
//       0 --> NEW_DOC
//       1 --> OPEN_DOC / OPENDOC_DATO_URI
// RETURN:
//       1 --> tutto ok
//       0 --> errore
int Thread_body::addToWorkingUsers(int docId, int userId, int open_new){

    int esito = 1;

    if(open_new == 0){                              // arrivo da NEW_DOC
        // creo nuova riga in workingUsers
        QVector<int> value;
        value.append(userId);
        mutex_workingUsers->lock();
        workingUsers.insert(docId, value);
        mutex_workingUsers->unlock();
    } else if(open_new == 1){                       // arrivo da OPEN_DOC / OPENDOC_DATO_URI
        if(workingUsers.contains(docId)){
            // chiave docId presente in workingUsers
            // aggiorno il vettore corrispondente alla riga con chiave docId in workingUsers
            mutex_workingUsers->lock();
            workingUsers[docId].append(userId);
            mutex_workingUsers->unlock();
        } else {
            // non c'è alcuna chiave in workingUsers corrispondente al docId
            // creo nuova riga in workingUsers, perchè l'utente attuale richiede l'apertura del documento
            QVector<int> value;
            value.append(userId);
            mutex_workingUsers->lock();
            workingUsers.insert(docId, value);
            mutex_workingUsers->unlock();
        }
    } else {
        // open_new non è uguale nè a 0 nè a 1
        esito = 0;
    }
    return esito;
}


void Thread_body::notifyNewWorkingUser(int userId, int docId){

    CRDT_Symbol s = *new CRDT_Symbol();
    CRDT_Message *m = new CRDT_Message("ONLINEUSER_"+std::to_string(userId), s, userId);
    auto thread_id = std::this_thread::get_id();

    emit messageToServer(*m, threadId_toQString(thread_id), docId);
}

void Thread_body::notifyWorkingUserAway(int userId, int docId){

    CRDT_Symbol s = *new CRDT_Symbol();
    CRDT_Message *m = new CRDT_Message("OFFLINEUSER_"+std::to_string(userId), s, userId);
    auto thread_id = std::this_thread::get_id();

    emit messageToServer(*m, threadId_toQString(thread_id), docId);
}

void Thread_body::notifyNewContributor(int userId, int docId){

    CRDT_Symbol s = *new CRDT_Symbol();
    CRDT_Message *m = new CRDT_Message("NEWCONTRIBUTOR_"+std::to_string(userId), s, userId);
    auto thread_id = std::this_thread::get_id();

    emit messageToServer(*m, threadId_toQString(thread_id), docId);
}


bool Thread_body::removeFromWorkingUsers(int docId, int userId){

    mutex_workingUsers->lock();

    if(workingUsers.contains(docId)){
        // chiave docId presente in workingUsers

        // Recupero il vettore di userId associato al docId
        // Conto quanti elementi ha il vettore... se count > 1 => rimuovo lo userId dal vettore e devo anche comunicare agli altri utenti
        //                                                        che mi sono sconnesso
        //                                        altrimenti (se count == 1), devo eliminare riga
        int count = workingUsers[docId].size();
        if(count > 1){
            int flag = 0;
            for(auto i = workingUsers[docId].begin(); i < workingUsers[docId].end(); i++){
                if((*i) == userId){
                    flag = 1;
                    workingUsers[docId].erase(i);
                    break;
                }
            }

            mutex_workingUsers->unlock();

            if(flag == 1){
                notifyWorkingUserAway(userId, docId);
            }
        } else if(count == 1){
            workingUsers.remove(docId);
            mutex_workingUsers->unlock();
            current_docId = -1;
            return true;
        } else {
            // Nota: caso che *in teoria* non dovrebbe mai verificarsi
            mutex_workingUsers->unlock();
        }
    } else {
        // Non c'è alcuna chiave in workingUsers corrispondente al docId
        // Nota: caso che *in teoria* non dovrebbe mai verificarsi
        qDebug() << "Oh no, il docId non è presente nella workingUsers... Qualcosa non va...";
        mutex_workingUsers->unlock();
    }

    current_docId = -1;

    return false;
}


void Thread_body::newDoc(QString docName, int userId){
    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    QString username = getUsername(userId);

    //controllo che ci sia la cartella del dato utente
    if(!username.isEmpty() && QDir(path+username).exists()){
        mutex_db->lock();
        int esito = database->creaDoc(username+"_"+docName);
        if(esito == 1){
            // Riga creata correttamente nella tabella doc del DB
            mutex_db->unlock();

            // Creo nuovo docId e inserisco nella mappa dei documents
            mutex_docs->lock();
            int docId = documents.size();
            docId++;
            documents.insert(username + "_" + docName, docId);
            mutex_docs->unlock();

            // Creo file fisico nel filesystem attraverso la openDoc
            if(openDoc(username + "_" + docName, docId, userId, 0) == -1){
                out << "errore";
                writeData(blocko);
            }else{
                mutex_db->lock();
                // Associazione username - nome_doc nella tabella utente_doc del DB
                if(database->aggiungiPartecipante(username+"_"+docName, username) != 2){
                    int siteCounter = database->recuperaSiteCounter(username+"_"+docName, username);
                    mutex_db->unlock();

                    if(siteCounter == -1){
                        out << "errore";
                        writeData(blocko);
                    } else {
                        // Aggiorno il docId su cui sto iniziando a lavorare
                        current_docId = docId;

                        current_siteCounter = siteCounter;
                        QString ritorno = "ok_"+QString::number(siteCounter)+"_"+QString::number(docId);

                        out << ritorno.toUtf8();
                        writeData(blocko);

                        notifyNewWorkingUser(userId, docId);
                    }
                }else{
                    mutex_db->unlock();
                    out << "errore";
                    writeData(blocko);
                }
            }
        }else if(esito == 2){
            // Riga già esistente nella tabella doc del DB
            mutex_db->unlock();
            out << "erroreGiaCreato";
            writeData(blocko);
        }else{
            mutex_db->unlock();
            out << "errore";
            writeData(blocko);
        }
    } else {
        // se username non esiste o non c'è la cartella relativa
        out << "errore";
        writeData(blocko);
    }
}


// La funzione openDoc restituisce:
//    1 --> tutto ok
//   -1 --> errore
int Thread_body::openDoc(QString docName, int docId, int userId, int new_doc){

    // Aggiungo la riga (docId, [userId]) alla mappa degli workingUsers
    int esito = addToWorkingUsers(docId, userId, new_doc);
    if(esito == 0){
        return -1;
    }

    mutex_files->lock();
    if(files.contains(docId)){
        // Qualcuno ha già "aperto" il file (vuol dire che c'è la riga nella QMap)
        // Salvo il puntatore allo CRDT_ServerEditor
        crdt = files.value(docId);
        mutex_files->unlock();
    } else {
        // Nessuno ha ancora "aperto" il file
         mutex_files->unlock();

        // Creo il percorsoFile con cui accedo al file
        QString owner = docName.split("_")[0];
        QString percorsoFile = path+owner+"/"+docName+".txt";

//        qDebug()<<"openDoc -- docName: "<<docName<<", percorsoFile: "<<percorsoFile;          // DEBUG

        // Creazione nuovo ServerEditor (=> new CRDT_ServerEditor())
        CRDT_ServerEditor* file = new CRDT_ServerEditor(percorsoFile);

        // Spostamento della proprietà dell'oggetto al master thread (Server)
        file->moveToThread(server);

        // Creazione nuova riga in files
        mutex_files->lock();
        files.insert(docId, file);
        mutex_files->unlock();

        // Salvo il puntatore allo CRDT_ServerEditor
        crdt = file;

        // Carico il crdt dal filesystem (o creo un file vuoto nel caso in cui non esista ancora)
        crdt->loadFromFilesystem();
    }

    return 1;
}


void Thread_body::create(QString username, QString password, QString nickname, QString icon){
    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    mutex_db->lock();
    int ret = database->signup(username, password, nickname, icon);
    mutex_db->unlock();
    if(ret == 1){
        // Dati correttamente inseriti nel DB
        mutex_users->lock();
        int id = users.size();
        id++;
        users.insert(username, id);
        mutex_users->unlock();

        //creo la cartella sul file system per l'utente
        QDir dir = QDir::current();
        dir.mkpath(path+username);

        //verifico sia stata correttamente creata
        if(QDir(path+username).exists()){
            out << "ok";
            out << id;
            writeData(blocko);
            // Aggiungo al vettore di logged_users
            mutex_logged_users->lock();
            logged_users.push_back(username);
            mutex_logged_users->unlock();
        }else {
            out << "erroreNellaCreazioneDelProfilo";
            writeData(blocko);
        }

    } else {
        out << "erroreNellaCreazioneDelProfilo";
        writeData(blocko);
    }
}

void Thread_body::stampaLoggedUsers(){          // Funzione per il DEBUG
    std::cout<<"### LOGGED USERS: ";
    mutex_logged_users->lock();
    for(auto it=logged_users.begin(); it<logged_users.end(); it++){
        std::cout<<(*it).toStdString()<<" ";
    }
    mutex_logged_users->unlock();
    std::cout<<"###"<<std::endl;
}

void Thread_body::login(QString username, QString password){
    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

//    std::cout<<"### LOGIN di: "<<username.toStdString()<<std::endl;     // DEBUG
//    stampaLoggedUsers();                                                // DEBUG

    // Controllo se l'utente ha già effettuato il login ed è attualmente loggato
    mutex_logged_users->lock();
    if(logged_users.contains(username)){
        // L'utente ha già effettuato il login ed è attualmente loggato
        mutex_logged_users->unlock();
//        std::cout<<"### Utente gia' loggato"<<std::endl;                // DEBUG
        out << "alreadyLogged";
        writeData(blocko);
    } else {
        // L'utente non è ancora loggato
        mutex_logged_users->unlock();

//        std::cout<<"### Utente non ancora loggato"<<std::endl;          // DEBUG
        mutex_db->lock();
        std::vector<QString> v = database->login(username, password);
        mutex_db->unlock();
        if(v.size()==2){
            // Aggiungo al vettore di users
            mutex_users->lock();
            int id = users[username];
            if(id == 0){
                id = users.size();
                id++;
                users.insert(username, id);
            }
            mutex_users->unlock();

            // Aggiungo al vettore di logged_users
            mutex_logged_users->lock();
            logged_users.push_back(username);
            mutex_logged_users->unlock();

            out << "ok";
            out << id;
            writeData(blocko);
        }else{
            out << "erroreLogin";
            writeData(blocko);
        }
    }

//    stampaLoggedUsers();                                                // DEBUG
}


void Thread_body::logout(int userId){
    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    int result = 1;
    QString username = getUsername(userId);

//    std::cout<<"### LOGOUT di: "<<username.toStdString()<<std::endl;    // DEBUG
//    stampaLoggedUsers();                                                // DEBUG

    if(username.isEmpty()){
        result = -1;
    } else {
        // Rimuovo l'utente dal vettore di logged_users
        mutex_logged_users->lock();
        bool flag = false;
        for(auto it=logged_users.begin(); it<logged_users.end(); it++){
            if((*it) == username){
                logged_users.erase(it);
                flag = true;
                break;
            }
        }
        mutex_logged_users->unlock();

//        std::cout<<"### Utente rimosso"<<std::endl;                     // DEBUG

        if(!flag){
            // L'username non è presente all'interno di logged_users
            result = -1;
        }
    }

//    stampaLoggedUsers();                                                // DEBUG

    out << result;
    writeData(blocko);

    // Chiudo il socket dal lato del client
    socket->close();

    emit finished();
}


void Thread_body::update(int userId, QString password, QString nickname, QString icon){
    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    QString username = getUsername(userId);

    if(!username.isEmpty()){
        mutex_db->lock();
        if(database->aggiornaUser(username, password, nickname, icon)){
            mutex_db->unlock();
            // orrettamente aggiornato nel db
            out << "ok";
            writeData(blocko);
        } else {
            mutex_db->unlock();
            out << "erroreUpdate";
            writeData(blocko);
        }
    } else {
        out << "erroreUpdate";
        writeData(blocko);
    }
}


void Thread_body::retrieveUsername(int userId){
    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    QString username = getUsername(userId);

    if(!username.isEmpty()){
        out << username;
        writeData(blocko);
    }else{
        out << "erroreGetUsername";
        writeData(blocko);
    }
}


void Thread_body::getNickname(int userId){
    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    QString username = getUsername(userId);

    if(!username.isEmpty()){
        mutex_db->lock();
        QString nick = database->getNickname(username);
        mutex_db->unlock();
        out << nick.toUtf8();
        writeData(blocko);
    }else{
        out << "erroreGetNickname";
        writeData(blocko);
    }
}


void Thread_body::getIcon(int userId){
    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    QString username = getUsername(userId);

    if(!username.isEmpty()){
        mutex_db->lock();
        QString icon = database->getIconId(username);
        mutex_db->unlock();
        out << icon.toUtf8();
        writeData(blocko);
    }else{
        out << "erroreGetIcon";
        writeData(blocko);
    }
}

void Thread_body::getDocs(int userId){
    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    QString username = getUsername(userId);

    if(!username.isEmpty()){
        // Recupero i documenti per cui l'utente e' abilitato ad accedere
        mutex_db->lock();
        std::vector<QString> documenti = database->recuperaDocs(username);
        mutex_db->unlock();

        // Mando al client il numero di elementi/documenti che verranno inviati
        int num_doc = documenti.size();
        //        qDebug() << "GET_DOCS - STO MANDANDO AL CLIENT num_doc: "<<num_doc;             // DEBUG
        out << num_doc;

        // Mando al client i nomi dei documenti a cui l'utente può accedere singolarmente
        for(auto it = documenti.begin(); it<documenti.end(); it++){
            //            qDebug()<< "GET_DOCS - (*it): "<<(*it);                  // DEBUG

            // Salvo il nome documento corrente
            QString doc_name = (*it);

//            qDebug()<< "GET_DOCS - docname: "<<doc_name;             // DEBUG

            if(doc_name != "nessuno"){
                // Cerco il docId del documento corrente
                mutex_docs->lock();
                int docId = documents.value(doc_name);
                mutex_docs->unlock();

                // Concateno in una stringa unica da mandare al client
                QString doc = doc_name.split("_").at(1) + "_" + QString::number(docId);

                // Mando la QString così generata al client
                out << doc.toUtf8();
            }else{
                out << doc_name.toUtf8();
            }
        }
        writeData(blocko);
    }else{
        out << -1;
        writeData(blocko);
    }
}


void Thread_body::openDocDatoUri(QString uri, int userId){
    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    mutex_db->lock();
    QString doc = database->recuperaDocDatoURI(uri);
    mutex_db->unlock();
    if(doc != "errore"){
        // Nome del documento relativo all'URI ottenuto dal DB correttamente

        // Cerco il docId del documento corrente
        mutex_docs->lock();
        int docId = documents.value(doc);
        mutex_docs->unlock();

        //creo sul db l'associazione documento-utente (non owner)
        QString ritorno;

        //cerco il nome del doc e dello user
        QString username = getUsername(userId);
        QString docName = getDocname(docId);

        if(!username.isEmpty() && !docName.isEmpty()){
            mutex_db->lock();
            if(database->aggiungiPartecipante(docName,username)!=2){
                int siteCounter = database->recuperaSiteCounter(docName, username);
                mutex_db->unlock();

                if(siteCounter == -1){
                    ritorno = "erroreOpenDocUri";
                } else {
                    current_siteCounter = siteCounter;

                    if(openDoc(docName, docId, userId, 1) == -1){
                        ritorno = "erroreOpenDocUri";
                    } else {
                        ritorno = "ok_"+QString::number(siteCounter)+"_"+QString::number(docId);
                    }
                }
            } else {
                mutex_db->unlock();
            }
        }

        if(ritorno.contains("ok")){
            // Mando al client la stringa di "ok"
            out << ritorno.toUtf8();
            writeData(blocko);

            crdt->mutex->lock();

            // Recupero il contenuto del vettore _symbols che sta all'interno del ServerEditor
            QVector<CRDT_Symbol> simboli = crdt->getSymbols();

            // Aggiorno il docId su cui sto iniziando a lavorare
            current_docId = docId;

            crdt->mutex->unlock();

            // Mando al client il contenuto del il contenuto del vettore _symbols
            QByteArray blocko1;
            QDataStream out1(&blocko1, QIODevice::WriteOnly);
            out1.setVersion(QDataStream::Qt_5_12);

            qDebug()<<"Invio file - Sto per inviare simboli.count(): "<<simboli.count();     // DEBUG

            out1 << simboli.count();
            writeData(blocko1);

            int cont=1;
            for(auto i=simboli.cbegin(); i<simboli.cend(); i++, cont++){

                qDebug()<<"Invio file - CICLO DI SCRITTURA i: "<<cont<<"/"<<simboli.count()<<", simbolo che sto inviando: "<<(*i).getCarattere().toLatin1();         // DEBUG

                QByteArray blocko2;
                QDataStream out2(&blocko2, QIODevice::WriteOnly);
                out2.setVersion(QDataStream::Qt_5_12);

                out2 << (*i);
                writeData(blocko2);
            }

            notifyNewWorkingUser(userId, docId);

            //segnalo agli altri contributors che ne faccio parte
            notifyNewContributor(userId, docId);

        }else{
            out << "erroreOpenDocUri";
            writeData(blocko);
        }
    }else{
        out << "erroreOpenDocUri";
        writeData(blocko);
    }
}


void Thread_body::getUri(int docId){

    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    QString docName = getDocname(docId);

    if(!docName.isEmpty()){
        mutex_db->lock();
        out << database->recuperaURI(docName).toUtf8();
        mutex_db->unlock();
        writeData(blocko);
    }else{
        out << "doc-inesistente";
        writeData(blocko);
    }
}


void Thread_body::getOwnerId(int docId){
    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    QString ownerName;
    int ownerId;

    // Recupero il docName, dato il docId
    QString docName = getDocname(docId);

    if(!docName.isEmpty()){
        // Faccio la split del docName e recupero ownerName (at(0))
        ownerName = docName.split("_").at(0);

        // Recupero il ownerId, dato il ownerName
        mutex_users->lock();
        ownerId = users.value(ownerName);
        mutex_users->unlock();

        out << ownerId;
        writeData(blocko);
    }else{
        out << -1;
        writeData(blocko);
    }
}


//l'eliminazione di un documento deve avvertire il possessore del documento che anche tutti i collaboratori
//non potranno più accedervi (messaggio di notifica). L'eliminazione del documento da parte dei collaboratori elimina
//solamente la corrispondenza con quel documento nel db.
//eliminare anche dal file system
void Thread_body::deleteDoc(int userId, int docId){
    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    //cerco il nome del documento da eliminare
    QString docName = getDocname(docId);

    if(docName.isEmpty()){
        out << "doc-inesistente";
        writeData(blocko);
        return;
    }

    //cerco lo username dell'utente che ha chiesto l'eliminazione (per fare
    //la verifica sul fatto che sia l'owner o meno
    QString username = getUsername(userId);
    if(username.isEmpty()){
        out << "erroreDeleteDoc";
        writeData(blocko);
        return;
    }

    //controllo il creatore del documento con username
    if(QString::compare(username, docName.split("_").at(0))==0){
        mutex_db->lock();
        //è il creatore del documento: tutti i partecipanti, non vi hanno più accesso
        std::vector<std::vector<QString>> collaboratori = database->recuperaCollaboratori(docName);
        mutex_db->unlock();
        if(collaboratori.size()==0){
            out << "erroreDeleteDoc";
            writeData(blocko);
            return;
        }
        if(collaboratori.size()==1 && (collaboratori.at(0).at(0)=="errore")) {
            out << "erroreDeleteDoc";
            writeData(blocko);
            return;
        }

        //itero sui collaboratori ed elimino il loro documento
        for(auto i:collaboratori){
            mutex_db->lock();
            if(database->rimuoviPartecipante(docName, i.at(0))==0){
                mutex_db->unlock();
                out << "erroreDeleteDoc";
                writeData(blocko);
                return;
            }
            mutex_db->unlock();
        }

        //elimino il documento in doc
        mutex_db->lock();
        if(database->rimuoviDocumento(docName)==0){
            mutex_db->unlock();
            out << "erroreDeleteDoc";
            writeData(blocko);
        }else{
            mutex_db->unlock();

            // Rimuovo il documento da documents
            mutex_docs->lock();
            documents.remove(docName);
            mutex_docs->unlock();

            //elimino il documento nel file system
            QFile file (path+username+"/"+docName+".txt");
            file.remove();
            out << "ok";
            writeData(blocko);
        }
    }else{
        // il documento rimane e viene dimenticato il documento da parte del partecipane
        mutex_db->lock();
        if(database->rimuoviAccesso(docName, username)==0){
            mutex_db->unlock();
            out << "erroreDeleteDoc";
            writeData(blocko);
        }else{
            mutex_db->unlock();
            out << "ok";
            writeData(blocko);
        }
    }
}

void Thread_body::retrieveDocName(int docId){
    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    QString docName = getDocname(docId);
    if(!docName.isEmpty()){
        out << docName.split("_").at(1).toUtf8();
        writeData(blocko);
    }else{
        out << "erroreRetrieveDocName";
        writeData(blocko);
    }
}

void Thread_body::getWorkingUsersGivenDoc(int docId){
    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    mutex_workingUsers->lock();

    // Recupero gli utenti online che stanno lavorando sul documento al momento
    // Controllo che nella mappa workingUsers sia presente il documento docId
    if(workingUsers.contains(docId)){

        // Dato il docId, recupero nella mappa il valore corrispondente a tale chiave, cioè il vettore di working users
        QVector<int> utenti_online = workingUsers.value(docId);

        // Mando al client il numero di elementi/id che verranno inviati
        int num_working_users = utenti_online.size();
//        qDebug() << "GET_WORKINGUSERS_ONADOC - STO MANDANDO AL CLIENT num_working_users: "<<num_working_users;             // DEBUG
        out << num_working_users;

        // Mando al client gli id degli utenti online che stanno lavorando sul documento al momento
        for(auto it = utenti_online.begin(); it<utenti_online.end(); it++){
            int id = (*it);
//            qDebug()<<"GET_WORKINGUSERS_ONADOC - Sto mandando al client ID: "<<id;                                           // DEBUG
            out << id;
        }

        writeData(blocko);

    } else {
        // Documento non presente nella mappa workingUsers
//        qDebug()<<"GET_WORKINGUSERS_ONADOC - Oh no, sono passato dall'else, quindi la mappa workingUsers NON contiene docId!!";           // DEBUG
        int no_doc = -1;
        out << no_doc;
        writeData(blocko);
    }

    mutex_workingUsers->unlock();

}

void Thread_body::getCollaboratorsGivenDoc(int docId){
    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    //cerco il nome del documento
    QString docName = getDocname(docId);
    if(!docName.isEmpty()){
        //recupero i collaboratori dal db
        mutex_db->lock();
        std::vector<std::vector<QString>> collaboratori = this->database->recuperaCollaboratori(docName);
        mutex_db->unlock();

        // Mando al client il numero di elementi/id che verranno inviati
        int num_collaborators = collaboratori.size();
        out << num_collaborators;

        for(auto it_ext = collaboratori.begin(); it_ext<collaboratori.end(); it_ext++){
            for(auto it_int = it_ext->begin(); it_int<it_ext->begin()+1; it_int++){

                QString c = (*it_int);

                //controlli
                QString err = "errore";
                QString no = "no";
                if(c.contains(err.toUtf8())){
                    out << -2;
                } else if(c.contains(no.toUtf8())){
                    out << -1;
                } else {
                    //se sono qui, vuol dire che c'è almeno una tupla valida
                    //Mando quindi lo userId associato allo username
                    out << users[c];
                }
            }
        }
        writeData(blocko);
    }else{
        out << 1;
        out << -2;
        writeData(blocko);
    }
}

void Thread_body::getDocText(int docId, int userId){
    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    QString docName = getDocname(docId);
    QString username = getUsername(userId);

    if(docName.isEmpty()){
        // Il documento non esiste (vuol dire che è stato cancellato dall'owner)
        out << "doc-inesistente";
        writeData(blocko);
    } else {
        // Il documento esiste
        if(openDoc(docName, docId, userId, 1) == -1){
            out << "errore";
            writeData(blocko);
        }else{
            mutex_db->lock();
            int siteCounter = database->recuperaSiteCounter(docName, username);
            mutex_db->unlock();

            if(siteCounter == -1){
                out << "errore";
                writeData(blocko);
            }else{
                current_siteCounter = siteCounter;
                QString ritorno = "ok_"+QString::number(siteCounter);

                out << ritorno.toUtf8();
                writeData(blocko);

                // Recupero il contenuto del vettore _symbols che sta all'interno del ServerEditor
                QVector<CRDT_Symbol> simboli = crdt->getSymbols();

                //crdt->mutex->unlock();

                // Mando al client il contenuto del il contenuto del vettore _symbols
                QByteArray blocko1;
                QDataStream out1(&blocko1, QIODevice::WriteOnly);
                out1.setVersion(QDataStream::Qt_5_12);

                qDebug()<<"Invio file - Sto per inviare simboli.count(): "<<simboli.count();     // DEBUG

                out1 << simboli.count();
                writeData(blocko1);

                int cont=1;
                for(auto i=simboli.cbegin(); i<simboli.cend(); i++, cont++){

                    qDebug()<<"Invio file - CICLO DI SCRITTURA i: "<<cont<<"/"<<simboli.count()<<", simbolo che sto inviando: "<<(*i).getCarattere().toLatin1();         // DEBUG

                    QByteArray blocko2;
                    QDataStream out2(&blocko2, QIODevice::WriteOnly);
                    out2.setVersion(QDataStream::Qt_5_12);

                    out2 << (*i);
                    writeData(blocko2);
                }
            }
        }
    }

}

void Thread_body::openDocument(int docId, int userId){
    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    // Cerco il nome del doc e dello user
    QString username = getUsername(userId);
    QString docName = getDocname(docId);

    // Controllo se il documento di cui si vuole fare la OPEN è tra i documenti esistenti
    if(docName.isEmpty() || username.isEmpty()){
        if(username.isEmpty()){
            // L'utente non esiste
            out << "errore";
            writeData(blocko);
        } else {
            // Il documento non esiste (vuol dire che è stato cancellato dall'owner)
            out << "doc-inesistente";
            writeData(blocko);
        }
    } else {
        // L'utente e il documento esistono
        if(openDoc(docName, docId, userId, 1) == -1){
            out << "errore";
            writeData(blocko);
        }else{
            mutex_db->lock();
            int siteCounter = database->recuperaSiteCounter(docName, username);
            mutex_db->unlock();

            if(siteCounter == -1){
                out << "errore";
                writeData(blocko);
            } else {
                current_siteCounter = siteCounter;
                QString ritorno = "ok_"+QString::number(siteCounter);

                out << ritorno.toUtf8();
                writeData(blocko);

                crdt->mutex->lock();

                // Recupero il contenuto del vettore _symbols che sta all'interno del ServerEditor
                QVector<CRDT_Symbol> simboli = crdt->getSymbols();

                // Aggiorno il docId su cui sto iniziando a lavorare
                current_docId = docId;

                crdt->mutex->unlock();

                // Mando al client il contenuto del il contenuto del vettore _symbols
                QByteArray blocko1;
                QDataStream out1(&blocko1, QIODevice::WriteOnly);
                out1.setVersion(QDataStream::Qt_5_12);

                qDebug()<<"Invio file - Sto per inviare simboli.count(): "<<simboli.count();     // DEBUG

                out1 << simboli.count();
                writeData(blocko1);

                int cont=1;
                for(auto i=simboli.cbegin(); i<simboli.cend(); i++, cont++){

                    qDebug()<<"Invio file - CICLO DI SCRITTURA i: "<<cont<<"/"<<simboli.count()<<", simbolo che sto inviando: "<<(*i).getCarattere().toLatin1();         // DEBUG

                    QByteArray blocko2;
                    QDataStream out2(&blocko2, QIODevice::WriteOnly);
                    out2.setVersion(QDataStream::Qt_5_12);

                    out2 << (*i);
                    writeData(blocko2);
                }

                notifyNewWorkingUser(userId, docId);
            }
        }
    }
}


void Thread_body::closeDocument(int docId, int userId){

    // Rimuovo l'utente dalla riga degli utenti online su un certo documento
    bool last = removeFromWorkingUsers(docId, userId);

//    qDebug()<<"**** Sono entrato nella closeDocument... last: "<<last;         // DEBUG

    // Controllo se l'utente che sta chiudendo il documento è l'ultimo utente online su tale documento
    if(last){
        mutex_files->lock();
        files.remove(docId);
        mutex_files->unlock();

        // Salvo il contenuto attuale del crdt nel filesystem
        crdt->saveInFilesystem();

        delete crdt;
    }

    // "Resetto" il puntatore a CRDT_ServerEditor
    crdt = nullptr;

    // Recupero il nome del documento e il nome dello user
    QString username = getUsername(userId);
    QString docName = getDocname(docId);

    // Salvo il site_counter attuale nel DB
    mutex_db->lock();
    database->aggiornaSiteCounter(docName, username, current_siteCounter);
    mutex_db->unlock();
}


void Thread_body::processMessage(CRDT_Message m, QString thread_id_sender, int docId){

    qDebug() << "THREAD ID SENDER: "+thread_id_sender;                              // DEBUG
    QString docidForDebug = "CURRENTDOCID: "+QString::number(current_docId);       // DEBUG

    auto thread_id = std::this_thread::get_id();
    std::cout << "---- ThreadBody processMessage RICEVUTO thread_id: "<<thread_id<<", doc_id: "<<docId<<" ---- "<< "; Stringa: "<<m.getAzione()<< std::endl;      // DEBUG
    QString thread_id_string = threadId_toQString(thread_id);

    // Se altro documento o stesso user_id di questo thread => discard (return) del messaggio
    // NOTA: se stesso user_id e è una insert, aggiorna il current_siteCounter
    if(docId != current_docId){
        return;
    }

    if(thread_id_string == thread_id_sender){

        if(m.getAzione() == "insert" || m.getAzione() == "delete"){
            crdt->process(m);
        }

        if(m.getAzione() == "insert"){
            QString str = QString::fromStdString(m.getSimbolo().getIDunivoco());
            current_siteCounter = str.split("_")[1].toInt() + 1;
        }
        return;
    }

    std::cout << "---- ThreadBody processMessage ACCETTATO thread_id: "<<thread_id<<", doc_id: "<<docId<<" ---- "<< "; Stringa: "<<m.getAzione()<< std::endl;      // DEBUG

    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    QString strAction = QString::fromStdString(m.getAzione());

    /* Messaggio che NON fa parte del CRDT */
    QString c = "OFFLINEUSER";
    if(strAction.contains(c.toUtf8())){
        QStringList userIdDisconnect = strAction.split("_");
//        qDebug() << userIdDisconnect[1];       // DEBUG

        out << "OFFLINEUSER";
        out <<  userIdDisconnect[1].toInt();
        writeData(blocko);
        return;
    }

    c = "ONLINEUSER";
    if(strAction.contains(c.toUtf8())){
        QStringList userIdConnect = strAction.split("_");
//        qDebug() << userIdConnect[1];       // DEBUG

        int userId = userIdConnect[1].toInt();

        //mando in uscita anche Nickname e icona
        mutex_db->lock();
        QString nick = database->getNickname(getUsername(userId));       // DEBUG
        QString icon = database->getIconId(getUsername(userId));
        mutex_db->unlock();
        out << "ONLINEUSER";
        out << userId;
        out << icon.toUtf8();
        out << nick.toUtf8();
        writeData(blocko);
        return;
    }

    c = "NEWCONTRIBUTOR";
    if(strAction.contains(c.toUtf8())){
        QStringList userIdContributor = strAction.split("_");
//        qDebug() << userIdContributor[1];

        //mando in uscita anche Nickname e icona
        mutex_db->lock();
        QString nick = database->getNickname(getUsername(userIdContributor[1].toInt()));
        QString icon = database->getIconId(getUsername(userIdContributor[1].toInt()));
        mutex_db->unlock();
        out << "NEWCONTRIBUTOR";
        out << userIdContributor[1].toInt();
        out << icon.toUtf8();
        out << nick.toUtf8();
        writeData(blocko);
        return;
    }

    /* Messaggio che fa parte del CRDT */
    out << "CRDT";
    out << m;
    writeData(blocko);
}


void Thread_body::readData(){

    qint32 size = readBuffer_size;

    while (socket->bytesAvailable() > 0){

//        qDebug()<<"readData - BytesAvailable: "<<socket->bytesAvailable();        // DEBUG

        readBuffer.append(socket->readAll());

        while ((size == 0 && readBuffer.size() >= 4) || (size > 0 && readBuffer.size() >= size))   // While can process data, process it
        {
            if (size == 0 && readBuffer.size() >= 4)        // If size of data has received completely, then store it on our global variable
            {
                size = ArrayToInt(readBuffer.mid(0, 4));
                readBuffer_size = size;
                readBuffer.remove(0, 4);
            }
            if (size > 0 && readBuffer.size() >= size)      // If data has received completely, then emit our SIGNAL with the data
            {
                QByteArray data = readBuffer.mid(0, size);
                readBuffer.remove(0, size);
                size = 0;
                readBuffer_size = size;
                emit dataReceived(data);
            }
        }
    }
}


qint32 Thread_body::ArrayToInt(QByteArray source) {
    qint32 temp;
    QDataStream data(&source, QIODevice::ReadWrite);
    data >> temp;
    return temp;
}


bool Thread_body::writeData(QByteArray data){
//    qDebug()<<"writeData - data.size(): "<<data.size();           // DEBUG
    socket->write(IntToArray(data.size()));          // ... write size of data
    socket->write(data);                             // ... write the data itself
    return socket->waitForBytesWritten(Timeout);
}


QByteArray Thread_body::IntToArray(qint32 source)      //Use qint32 to ensure that the number have 4 bytes
{
    // Avoid use of cast, this is the Qt way to serialize objects
    QByteArray temp;
    QDataStream data(&temp, QIODevice::ReadWrite);
    data << source;
    return temp;
}
