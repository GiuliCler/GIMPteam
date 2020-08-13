#include "thread_body.h"
#include <iostream>
#include <sstream>
#include <QThread>

Thread_body::Thread_body(int socketDescriptor, QObject *parent) : QObject(parent), current_docId(-1)
{
    auto thread_id = std::this_thread::get_id();
    std::stringstream ss;
    ss << thread_id;
    std::string thread_id_string = ss.str();

    std::cout << "---- ThreadBody constructor id: "<<thread_id<<" ---- "<< std::endl;      // DEBUG

    socket = new QTcpSocket();
    if (!socket->setSocketDescriptor(socketDescriptor)) {
        socket->disconnectFromHost();       //altrimenti non accetta più connessioni da altri client...
        emit error(socket->error());
        return;
    }
    socket->setReadBufferSize(0);
    // Creo nel thread un collegamento al DB, mettendo come nome univoco di connessione "connSOCKETDESCRIPTOR"
    database = new CollegamentoDB();
    database->connettiDB("gimpdocs_db", "conn" + QString::fromStdString(thread_id_string));

    // Ridefinisco in e out relativi alla connessione corrente
    in = new QDataStream(socket);
    in->setVersion(QDataStream::Qt_5_12);
//    in->startTransaction();
}

Thread_body::~Thread_body(){
    std::cout<<"STO DISTRUGGENDO IL THREAD_BODY"<<std::endl;
}

void Thread_body::executeJob(){
    if(isProcessing)
        return;

    isProcessing = true;
    while(socket->bytesAvailable() > 0){
    auto thread_id = std::this_thread::get_id();
//    std::cout << "THREAD - executeJob; Thread: "<<thread_id<<" ---- "<< std::endl;

    QByteArray text;
    // Prendo la stringa di comando
    *in >> text;

    qDebug() << "THREAD - Run - Prima della verifica del comando... il comando e': "<< QString::fromStdString(text.toStdString());      // DEBUG

    QString c = "CREATE";
    if(text.contains(c.toUtf8())){
        //        qDebug() << "SONO DENTRO LA CREATE";             // DEBUG
        QString username, password, nickname, icon;
        *in >> username;
        *in >> password;
        *in >> nickname;
        *in >> icon;

        create(username, password, nickname, icon);
        continue;
    }

    c = "LOGIN";
    if(text.contains(c.toUtf8())){
        //qDebug()<< "THREAD - Sono nella LOGIN";        // DEBUG
        QString username, password;
        *in >> username;
        *in >> password;

        login(username, password);
    }

    c = "LOGOUT";
    if(text.contains(c.toUtf8())){

        int userId;
        *in >> userId;

        std::cout<<"LOGOUT - Ricevuto dal client lo userId: "<<userId<<std::endl;           // DEBUG

        logout(userId);
    }

    c = "DELETE_DOC";
    if(text.contains(c.toUtf8())){
        int docId, userId;
        *in >> userId;
        *in >> docId;

        deleteDoc(userId, docId);
    }

    c = "UPDATE";
    if(text.contains(c.toUtf8())){
        //        qDebug()<<"SONO DENTRO LA UPDATE";          // DEBUG
        QString password, nickname, icon;
        int userId;
        *in >> userId;
        *in >> password;
        *in >> nickname;
        *in >> icon;

        update(userId, password, nickname, icon);
    }

    c = "GET_USERNAME";
    if(text.contains(c.toUtf8())){
        int userId;
        *in >> userId;

        retrieveUsername(userId);
    }

    c = "GET_NICKNAME";
    if(text.contains(c.toUtf8())){
        //qDebug()<< "SONO DENTRO LA GET_NICKNAME";             // DEBUG
        int userId;
        *in >> userId;

        getNickname(userId);
    }

    c = "GET_DOC_NAME";
    if(text.contains(c.toUtf8())){
        int docId;
        *in >> docId;

        retrieveDocName(docId);
    }

    c = "GET_ICON";
    if(text.contains(c.toUtf8())){
        //qDebug()<< "SONO DENTRO LA GET_ICON";             // DEBUG
        int userId;
        *in >> userId;

        getIcon(userId);
    }

    c = "GET_DOCS";
    if(text.contains(c.toUtf8())){
        int userId;
        *in >> userId;

        getDocs(userId);
    }

    c = "GET_DOCUMENT_DATO_URI";
    if(text.contains(c.toUtf8())){
        QString uri;
        int userId;
        *in >> uri;
        *in >> userId;

        getDocumentDatoUri(uri, userId);
    }

    c = "GET_URI";
    if(text.contains(c.toUtf8())){
        int docId;
        *in >> docId;

        getUri(docId);
    }

    c = "GET_DOC_OWNER";
    if(text.contains(c.toUtf8())){
        int docId;
        *in >> docId;

        getOwnerId(docId);
    }

    c = "GET_WORKINGUSERS_ONADOC";
    if(text.contains(c.toUtf8())){
        int docId;
        *in >> docId;

        getWorkingUsersGivenDoc(docId);
    }

    c = "GET_CONTRIBUTORS_ONADOC";
    if(text.contains(c.toUtf8())){
        int docId;
        *in >> docId;

        getCollaboratorsGivenDoc(docId);
    }

    c = "NEW_DOC";
    if(text.contains(c.toUtf8())){
        QString docName;
        int userId;
        *in >> docName;
        *in >> userId;

        newDoc(docName, userId);
    }

    c = "OPEN_DOC";
    if(text.contains(c.toUtf8())){
        int docId, userId;
        *in >> docId;
        *in >> userId;

        openDocument(docId, userId);
    }

    c = "SEND";
    if(text.contains(c.toUtf8())){
//        QByteArray action;
//        do {
//            CRDT_Message m;
//            *in >> m;
//            std::cout << "if SEND - messaggeAction - "<<m.getAzione()<< std::endl;      // DEBUG

//            emit messageToServer(m, threadId_toQString(thread_id), current_docId);

//            if(!in->commitTransaction()){
//                *in >> action;
//                if(action.isEmpty()){
//                    break;
//                }else{
//                    std::cout << "if SEND - "<<action.toStdString()<< std::endl;        // DEBUG
//                }
//            }else{
//                break;
//            }
//        } while (!in->commitTransaction());

        //PRIMA ERA COSì:
        CRDT_Message messaggio;
        *in >> messaggio;

//        std::cout << "if SEND - "<<messaggio.getAzione()<< std::endl;      // DEBUG

//         scrivi su crdt del server? MUTEX + chiediti se metterla dopo emit        todo ila&paolo
        std::stringstream ss;
        ss << thread_id;
        std::string thread_id_string = ss.str();
        emit messageToServer(messaggio, QString::fromStdString(thread_id_string), current_docId);
        continue;
    }

    c = "DISCONNECT_FROM_DOC";
    if(text.contains(c.toUtf8())){

        int docId, userId;
        *in >> docId;
        *in >> userId;

        removeFromWorkingUsers(docId, userId);

        QString username = getUsername(userId);
        QString docName = getDocname(docId);

        mutex_db->lock();
        database->aggiornaSiteCounter(docName, username, current_siteCounter);
        mutex_db->unlock();
        continue;
    }

    //    socket->disconnectFromHost();
    //    socket->waitForDisconnected(3000);

    }
//    qDebug() << "EXECUTE JOB finita";      // DEBUG
    isProcessing = false;
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
//       1 --> OPEN_DOC
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
    } else if(open_new == 1){                       // arrivo da OPEN_DOC
        CRDT_Symbol s = *new CRDT_Symbol();
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
        CRDT_Message *m = new CRDT_Message("ONLINEUSER_"+std::to_string(userId), s, userId);
        auto thread_id = std::this_thread::get_id();
        emit messageToServer(*m, threadId_toQString(thread_id), docId);
    } else {
        // open_new non è uguale nè a 0 nè a 1
        esito = 0;
    }
    return esito;
}


void Thread_body::removeFromWorkingUsers(int docId, int userId){

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
                CRDT_Symbol s = *new CRDT_Symbol();
                CRDT_Message *m = new CRDT_Message("OFFLINEUSER_"+std::to_string(userId), s, userId);
                auto thread_id = std::this_thread::get_id();
                emit messageToServer(*m, threadId_toQString(thread_id), docId);
            }
        } else if(count == 1){
            workingUsers.remove(docId);
            mutex_workingUsers->unlock();
        } else {
            // Nota: caso che *in teoria* non dovrebbe mai verificarsi
            mutex_workingUsers->unlock();
        }
    } else {
        // non c'è alcuna chiave in workingUsers corrispondente al docId
        qDebug() << "Oh no, il docId non è presente nella workingUsers... Qualcosa non va...";
        mutex_workingUsers->unlock();
    }

    current_docId = -1;
}


void Thread_body::newDoc(QString docName, int userId){
    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    QString username = getUsername(userId);

    //controllo che ci sia la cartella del dato utente
    if(!username.isEmpty() && QDir(path+username).exists()){
        mutex_db->lock();
        if(database->creaDoc(username+"_"+docName)){
            mutex_db->unlock();
            // Associazione username - nome_doc nella tabella utente_doc del DB
            int id = openDoc(docName, username, -1, userId, 0);
            if(id == -1){
                out << "errore";
                socket->write(blocko);
                socket->flush();
            }else{
                mutex_db->lock();
                if(database->aggiungiPartecipante(username+"_"+docName, username) != 2){
                    std::vector<int> info = database->recuperaInfoUtenteDoc(username+"_"+docName, username);
                    mutex_db->unlock();

                    int siteId = info[0];
                    int siteCounter = info[1];
                    current_siteCounter = siteCounter;
                    QString ritorno = "ok_"+QString::number(siteId)+"_"+QString::number(siteCounter)+"_"+QString::number(id);

                    out << ritorno.toUtf8();
                    socket->write(blocko);
                    socket->flush();
                }else{
                    mutex_db->unlock();
                    out << "errore";
                    socket->write(blocko);
                    socket->flush();
                }
            }
        }else{
            mutex_db->unlock();
            out << "errore";
            socket->write(blocko);
            socket->flush();
        }

        // ********************************************************************************
        // GIULIA TODO: gestire meglio il "ritorno" e le modifiche su file -> crdt
        // ********************************************************************************

    } else {
        // se username non esiste o non c'è la cartella relativa
        out << "errore";
        socket->write(blocko);
        socket->flush();
    }
}

//viene passato anche il docId, nel caso possa servire per cose future. Si noti che nel caso di NewDoc
//è -1!!!
int Thread_body::openDoc(QString docName, QString username, int docId, int userId, int new_doc){

    if(docId == -1){
        // Sono arrivato dalla "newDoc"
        mutex_docs->lock();
        docId = documents.size();
        docId++;
        documents.insert(username + "_" + docName, docId);
        mutex_docs->unlock();
    }

    // Aggiungo la riga (docId, [userId]) alla mappa degli workingUsers
    int esito = addToWorkingUsers(docId, userId, new_doc);
    if(esito == 0){
        return -1;
    }

    // Aggiorno il docId su cui sto iniziando a lavorare
    current_docId = docId;

    // ?????????????????????????????????????????????????????????????????????????????
    // Creazione del file
    QString filename = docName;

    // DUBBIO SULL'ESTENSIONE DEL FILE!! Al momento li faccio txt
    QFile file(path+username+"/"+filename+".txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)){
        //riesce ad aprire il file creato
        QTextStream out_file(&file);
        // ATTENZIONE: per scrivere sul file:
        // out_file << "The magic number is: " << 49 << "\n";       // DEBUG

        // *******************************************************
        // todo ila&paolo: gestione CRDT
        // *******************************************************


    }
    // ?????????????????????????????????????????????????????????????????????????????

    return docId;
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
        //qDebug()<<"STO SCRIVENDO NELLA MAPPA LA COPPIA key:"<<username<<" E value: "<<id;        // DEBUG
        users.insert(username, id);
        mutex_users->unlock();

        //creo la cartella sul file system per l'utente
        QDir dir = QDir::current();
        dir.mkpath(path+username);

        //verifico sia stata correttamente creata
        if(QDir(path+username).exists()){
            out << "ok";
            out << id;
            socket->write(blocko);
            socket->flush();
        }
    } else {
        out << "errore";
        socket->write(blocko);
        socket->flush();
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
        socket->write(blocko);
        socket->flush();
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
            socket->write(blocko);
            socket->flush();
        }else{
            out << "errore";
            socket->write(blocko);
            socket->flush();
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
    socket->write(blocko);
    socket->flush();
    //socket->waitForBytesWritten(Timeout);

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
            socket->write(blocko);
            socket->flush();
        } else {
            mutex_db->unlock();
            out << "errore";
            socket->write(blocko);
            socket->flush();
        }
    } else {
        out << "errore";
        socket->write(blocko);
        socket->flush();
    }
}


void Thread_body::retrieveUsername(int userId){
    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    QString username = getUsername(userId);

    if(!username.isEmpty()){
        out << username;
        socket->write(blocko);
        socket->flush();
    }else{
        out << "errore";
        socket->write(blocko);
        socket->flush();
    }
}


void Thread_body::getNickname(int userId){
    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    QString username = getUsername(userId);

    if(!username.isEmpty()){
        mutex_db->lock();
        QString nick = database->getNickname(username);       // DEBUG
        mutex_db->unlock();
        out << nick.toLocal8Bit();
        socket->write(blocko);
        socket->flush();
    }else{
        out << "errore";
        socket->write(blocko);
        socket->flush();
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
        out << icon.toLocal8Bit();
        socket->write(blocko);
        socket->flush();
    }else{
        out << "errore";
        socket->write(blocko);
        socket->flush();
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

            qDebug()<< "GET_DOCS - docname: "<<doc_name;             // DEBUG

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
        socket->write(blocko);
        socket->flush();
    }else{
        out << -1;
        socket->write(blocko);
        socket->flush();
    }
}


void Thread_body::getDocumentDatoUri(QString uri, int userId){
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
        QString ritorno = associateDoc(docId, userId);

        if(ritorno.contains("ok")){
            out << ritorno.toUtf8();
            socket->write(blocko);
            socket->flush();
            //segnalo agli altri contributors che ne faccio parte
            CRDT_Symbol s = *new CRDT_Symbol();
            CRDT_Message *m = new CRDT_Message("NEWCONTRIBUTOR_"+std::to_string(userId), s, userId);
            auto thread_id = std::this_thread::get_id();
            emit messageToServer(*m, threadId_toQString(thread_id), docId);
        }else{
            out << "errore";
            socket->write(blocko);
            socket->flush();
        }
    }else{
        out << "errore";
        socket->write(blocko);
        socket->flush();
    }
}


QString Thread_body::associateDoc(int docId, int userId){
    //cerco il nome del doc e dello user
    QString username = getUsername(userId);
    QString docName = getDocname(docId);

    if(!username.isEmpty() && !docName.isEmpty() && QDir(path+username).exists()){
        mutex_db->lock();
        if(database->aggiungiPartecipante(docName,username)!=2){
            std::vector<int> info = database->recuperaInfoUtenteDoc(docName, username);
            mutex_db->unlock();

            int siteId = info[0];
            int siteCounter = info[1];
            current_siteCounter = siteCounter;
            QString ritorno = "ok_"+QString::number(siteId)+"_"+QString::number(siteCounter)+"_"+QString::number(docId);

            int id = openDoc(docName, username, docId, userId, 1);
            if(id == -1){
                return "errore";
            } else {
                return ritorno;
            }
        }
        mutex_db->unlock();
    }

    return "errore";
}

void Thread_body::getUri(int docId){

    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    QString docName = getDocname(docId);

    if(!docName.isEmpty()){
        mutex_db->lock();
        out << database->recuperaURI(docName);
        mutex_db->unlock();
        socket->write(blocko);
        socket->flush();
    }else{
        out << "errore";
        socket->write(blocko);
        socket->flush();
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
        socket->write(blocko);
        socket->flush();
    }else{
        out << -1;
        socket->write(blocko);
        socket->flush();
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
        out << "errore";
        socket->write(blocko);
        socket->flush();
        return;
    }

    //cerco lo username dell'utente che ha chiesto l'eliminazione (per fare
    //la verifica sul fatto che sia l'owner o meno
    QString username = getUsername(userId);
    if(username.isEmpty()){
        out << "errore";
        socket->write(blocko);
        socket->flush();
        return;
    }

    //controllo il creatore del documento con username
    if(QString::compare(username, docName.split("_").at(0))==0){
        mutex_db->lock();
        //è il creatore del documento: tutti i partecipanti, non vi hanno più accesso
        std::vector<std::vector<QString>> collaboratori = database->recuperaCollaboratori(docName);
        mutex_db->unlock();
        if(collaboratori.size()==0){
            out << "errore";
            socket->write(blocko);
            socket->flush();
            return;
        }
        if(collaboratori.size()==1 && (collaboratori.at(0).at(0)=="errore")) {
            out << "errore";
            socket->write(blocko);
            socket->flush();
            return;
        }

        //itero sui collaboratori ed elimino il loro documento
        for(auto i:collaboratori){
            mutex_db->lock();
            if(database->rimuoviPartecipante(docName, i.at(0))==0){
                mutex_db->unlock();
                out << "errore";
                socket->write(blocko);
                socket->flush();
                return;
            }
            mutex_db->unlock();
        }

        //elimino il documento in doc
        mutex_db->lock();
        if(database->rimuoviDocumento(docName)==0){
            mutex_db->unlock();
            out << "errore";
            socket->write(blocko);
            socket->flush();
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
            socket->write(blocko);
            socket->flush();
        }
    }else{
        // il documento rimane e viene dimenticato il documento da parte del partecipane
        mutex_db->lock();
        if(database->rimuoviAccesso(docName, username)==0){
            mutex_db->unlock();
            out << "errore";
            socket->write(blocko);
            socket->flush();
        }else{
            mutex_db->unlock();
            out << "ok";
            socket->write(blocko);
            socket->flush();
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
        socket->write(blocko);
        socket->flush();
    }else{
        out << "errore";
        socket->write(blocko);
        socket->flush();
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
            //            qDebug()<<"GET_WORKINGUSERS_ONADOC - Sto mandando al client ID: "<<id;
            // Mando la QString così generata al client
            out << id;
        }

        socket->write(blocko);
        socket->flush();

    } else {
        // Documento non presente nella mappa workingUsers
        int no_doc = -1;
        out << no_doc;
        socket->write(blocko);
        socket->flush();
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
        socket->write(blocko);
        socket->flush();
    }else{
        out << 1;
        out << -2;
        socket->write(blocko);
        socket->flush();
    }
}

void Thread_body::openDocument(int docId, int userId){
    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    //cerco il nome del doc e dello user
    QString username = getUsername(userId);
    QString docName = getDocname(docId);

    // Controllo se il documento di cui si vuole fare la OPEN è tra i documenti esistenti
    if(docName.isEmpty() || username.isEmpty()){
        if(username.isEmpty()){
            // L'utente non esiste
            out << "errore";
            socket->write(blocko);
            socket->flush();
        } else {
            // Il documento non esiste (vuol dire che è stato cancellato dall'owner)
            out << "doc-inesistente";
            socket->write(blocko);
            socket->flush();
        }
    } else {
        // L'utente e il documento esistono
        if(openDoc(docName, username, docId, userId, 1) == -1){
            out << "errore";
            socket->write(blocko);
            socket->flush();
        }else{
            mutex_db->lock();
            std::vector<int> info = database->recuperaInfoUtenteDoc(docName, username);
            mutex_db->unlock();
            int siteId = info[0];
            int siteCounter = info[1];
            current_siteCounter = siteCounter;
            QString ritorno = "ok_"+QString::number(siteId)+"_"+QString::number(siteCounter);
            out << ritorno.toUtf8();
            socket->write(blocko);
            socket->flush();
        }
    }
}

void Thread_body::processMessage(CRDT_Message m, QString thread_id_sender, int docId){

//    qDebug() << "THREAD ID SENDER: "+thread_id_sender;                              // DEBUG
    QString docidForDebug = "CURRENTDOCID: "+QString::number(current_docId);       // DEBUG

    auto thread_id = std::this_thread::get_id();
//    std::cout << "---- ThreadBody processMessage RICEVUTO thread_id: "<<thread_id<<", doc_id: "<<docId<<" ---- "<< "; Stringa: "<<m.getAzione()<< std::endl;      // DEBUG
    QString thread_id_string = threadId_toQString(thread_id);

    // Se altro documento o stesso user_id di questo thread => discard (return) del messaggio
    // NOTA: se stesso user_id e è una insert, aggiorna il current_siteCounter
    if(docId != current_docId){
        return;
    }
    if(thread_id_string == thread_id_sender){
        if(m.getAzione() == "insert"){
            QString str = QString::fromStdString(m.getSimbolo().getIDunivoco());
            current_siteCounter = str.split("_")[1].toInt();
        }
        return;
    }

//    std::cout << "---- ThreadBody processMessage ACCETTATO thread_id: "<<thread_id<<", doc_id: "<<docId<<" ---- "<< "; Stringa: "<<m.getAzione()<< std::endl;      // DEBUG

    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    QString strAction = QString::fromStdString(m.getAzione());

    /* Messaggio che NON fa parte del CRDT */
    QString c = "OFFLINEUSER";
    if(strAction.contains(c.toUtf8())){
        QStringList userIdDisconnect = strAction.split("_");
        qDebug() << userIdDisconnect[1];
        QByteArray blocko;
        QDataStream out(&blocko, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_12);
        out << "OFFLINEUSER";
        out <<  userIdDisconnect[1].toInt();
        socket->write(blocko);
        socket->flush();
        return;
    }

    c = "ONLINEUSER";
    if(strAction.contains(c.toUtf8())){
        QStringList userIdConnect = strAction.split("_");
        qDebug() << userIdConnect[1];
        QByteArray blocko;
        QDataStream out(&blocko, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_12);
        //mando in uscita anche Nickname e icona
        mutex_db->lock();
        QString nick = database->getNickname(getUsername(userIdConnect[1].toInt()));       // DEBUG
        QString icon = database->getIconId(getUsername(userIdConnect[1].toInt()));
        mutex_db->unlock();
        out << "ONLINEUSER";
        out <<  userIdConnect[1].toInt();
        out << nick.toLocal8Bit();
        out << icon.toLocal8Bit();
        socket->write(blocko);
        socket->flush();
        return;
    }

    c = "NEWCONTRIBUTOR";
    if(strAction.contains(c.toUtf8())){
        QStringList userIdContributor = strAction.split("_");
        qDebug() << userIdContributor[1];
        QByteArray blocko;
        QDataStream out(&blocko, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_12);
        //mando in uscita anche Nickname e icona
        mutex_db->lock();
        QString nick = database->getNickname(getUsername(userIdContributor[1].toInt()));
        QString icon = database->getIconId(getUsername(userIdContributor[1].toInt()));
        mutex_db->unlock();
        out << "NEWCONTRIBUTOR";
        out <<  userIdContributor[1].toInt();
        out << nick.toLocal8Bit();
        out << icon.toLocal8Bit();
        socket->write(blocko);
        socket->flush();
        return;
    }

    /* Messaggio che fa parte del CRDT */

    out << "CRDT";
    out << m;
    std::cout << "Azione: " << m.getAzione() << "; Carattere: " << m.getSimbolo().getCarattere().toLatin1() << std::endl;
    socket->write(blocko);
    socket->flush();
    socket->waitForBytesWritten();
}

