#include "thread_management.h"
#include <iostream>
#include <sstream>

Thread_management::Thread_management(int socketDescriptor, QObject *parent): QThread(parent), socketDescriptor(socketDescriptor){
    qDebug()<< "THREAD - Costruttore del thread con descrittore "<<socketDescriptor;          // DEBUG

    std::cout << "---- THREAD Costruttore id: " << std::this_thread::get_id() << " ---- " << std::endl;      // DEBUG

    qDebug()<< "THREAD - Fine costruttore del thread con descrittore "<<socketDescriptor;       // DEBUG
}


void Thread_management::run(){

    qDebug() << "THREAD - run iniziata";           // DEBUG

    // todo ila&paolo ------------------------------------------------------------------------------------------------------------------------------------
    int timeoutReadRead = 5400000;
                                                    // todo ila : scegliere funzione che mi fa la break dal while(1)
                                                    // todo ila : distruzione dei thread nel server
    auto thread_id = std::this_thread::get_id();
    std::stringstream ss;
    ss << thread_id;
    std::string thread_id_string = ss.str();

    std::cout << "---- THREAD run id: "<<thread_id<<" ---- "<< std::endl;      // DEBUG

    socket = new QTcpSocket();
    if (!socket->setSocketDescriptor(socketDescriptor)) {
        emit error(socket->error());
        return;
    }

    bool connected = (socket->state() == QTcpSocket::ConnectedState);
    bool NOTconnected = (socket->state() == QTcpSocket::UnconnectedState);
    qDebug() << "THREAD - Run - connected:"<<connected<<" & NOTconnected:"<<NOTconnected;      // DEBUG

    // Creo nel thread un collegamento al DB, mettendo come nome univoco di connessione "connSOCKETDESCRIPTOR"
    database = new CollegamentoDB();
    database->connettiDB("gimpdocs_db", "conn" + QString::fromStdString(thread_id_string));

    // Ridefinisco in e out relativi alla connessione corrente
    QByteArray text;
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_12);
    in.startTransaction();

    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    //    connect(socket, SIGNAL(readyRead()), this, SLOT(executeJob()));
    //    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    while(1){
        qDebug() << this->socket->state();
        if (!socket->waitForReadyRead(timeoutReadRead)) {
            qDebug() << "Not enough time";
            emit error(socket->error());
            return;
        }

        // Prendo la stringa di comando
        in >> text;

        qDebug() << "THREAD - Run - Prima della verifica del comando... il comando e': "<< QString::fromStdString(text.toStdString());      // DEBUG

        QString c = "CREATE";
        if(text.contains(c.toUtf8())){
    //        qDebug() << "SONO DENTRO LA CREATE";             // DEBUG
            QString username, password, nickname, icon;
            in >> username;
            in >> password;
            in >> nickname;
            in >> icon;

            create(username, password, nickname, icon);
        }

        c = "LOGIN";
        if(text.contains(c.toUtf8())){
            //qDebug()<< "THREAD - Sono nella LOGIN";        // DEBUG
            QString username, password;
            in >> username;
            in >> password;

            login(username, password);
        }

        c = "DELETE_DOC";
        if(text.contains(c.toUtf8())){
            int docId, userId;
            in >> userId;
            in >> docId;

            deleteDoc(userId, docId);
        }

        c = "UPDATE";
        if(text.contains(c.toUtf8())){
    //        qDebug()<<"SONO DENTRO LA UPDATE";          // DEBUG
            QString password, nickname, icon;
            int userId;
            in >> userId;
            in >> password;
            in >> nickname;
            in >> icon;

            update(userId, password, nickname, icon);
        }

        c = "GET_USERNAME";
        if(text.contains(c.toUtf8())){
            int userId;
            in >> userId;

            getUsername(userId);
        }

        c = "GET_NICKNAME";
        if(text.contains(c.toUtf8())){
            //qDebug()<< "SONO DENTRO LA GET_NICKNAME";             // DEBUG
            int userId;
            in >> userId;

            getNickname(userId);
        }

        c = "GET_DOC_NAME";
        if(text.contains(c.toUtf8())){
            int docId;
            in >> docId;

            getDocName(docId);
        }

        c = "GET_ICON";
        if(text.contains(c.toUtf8())){
            //qDebug()<< "SONO DENTRO LA GET_ICON";             // DEBUG
            int userId;
            in >> userId;

            getIcon(userId);
        }

        c = "GET_DOCS";
        if(text.contains(c.toUtf8())){
            int userId;
            in >> userId;

            getDocs(userId);
        }

        c = "GET_DOCUMENT_DATO_URI";
        if(text.contains(c.toUtf8())){
            QString uri;
            in >> uri;

            getDocumentDatoUri(uri);
        }

        c = "GET_URI";
        if(text.contains(c.toUtf8())){
            int docId;
            in >> docId;

            getUri(docId);
        }

        c = "GET_WORKINGUSERS_ONADOC";
        if(text.contains(c.toUtf8())){
            int docId;
            in >> docId;

            getWorkingUsersGivenDoc(docId);
        }

        c = "NEW_DOC";
        if(text.contains(c.toUtf8())){
            QString docName;
            int userId;
            in >> docName;
            in >> userId;

            newDoc(docName, userId);
        }

        c = "OPEN_DOC";
        if(text.contains(c.toUtf8())){
            int docId, userId;
            in >> docId;
            in >> userId;

            openDoc(docId, userId);
        }

        c = "SEND";
        if(text.contains(c.toUtf8())){

            // todo ila&paolo -------------------------------------------------------------------------------------------------------------------------------

            // in >> messaggio

            // lock
            // codaMessaggi.push(messaggio, contatore);
            // unlock

            // notifica gli altri utenti ... dispatchMessages ... emit signal???
        }

        c = "DISCONNECT_FROM_DOC";
        if(text.contains(c.toUtf8())){

            // todo ila&paolo ------------------------------------------------------------------------------------------------------------------------------

            // disconnect: rimuovo riga all'interno di workingUsers

            // break;
        }

//        break;      // todo ila : da rimuovere -------------------------------------------------------------------------------------------------------
    }

    socket->disconnectFromHost();
    socket->waitForDisconnected(3000);

    qDebug() << "THREAD - run finita";      // DEBUG
}


// NOTA: open_new è un flag che indica da dove è stata chiamata la connect
//       0 --> NEW_DOC
//       1 --> OPEN_DOC
// RETURN:
//       1 --> tutto ok
//       0 --> errore
int Thread_management::addToWorkingUsers(int docId, int userId, int open_new){

    int esito = 1;
    mutex_workingUsers->lock();

    if(open_new == 0){              // arrivo da NEW_DOC

        // creo nuova riga in workingUsers
        QVector<int> value;
        value.append(userId);
        workingUsers.insert(docId, value);

    } else if(open_new == 1){       // arrivo da OPEN_DOC

        if(workingUsers.contains(docId)){
            // chiave docId presente in workingUsers
            // aggiorno il vettore corrispondente alla riga con chiave docId in workingUsers
            workingUsers[docId].append(userId);
        } else {
            // non c'è alcuna chiave in workingUsers corrispondente al docId
            esito = 0;
        }

    } else {
        // open_new non è uguale nè a 0 nè a 1
        esito = 0;
    }

    mutex_workingUsers->unlock();

    return esito;
}


int Thread_management::removeFromWorkingUsers(int docId, int userId){
    int i = docId;      // schifo per togliermi i warning
    docId = i;
    i = userId;
    userId = i;
    return 1;
    // todo ila&paolo --------------------------------------------------------------------------------------
}


void Thread_management::newDoc(QString docName, int userId){
    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    mutex_users->lock();
    QString username;
    //controllo che ci sia la cartella del dato utente
    QMapIterator<QString, int> i(users);
    while (i.hasNext()) {
        i.next();
        if(i.value()==userId){
            username=i.key();
            break;
        }
    }
    mutex_users->unlock();

    if(!username.isEmpty() && QDir(path+username).exists()){
        mutex_db->lock();
        if(database->creaDoc(username+"_"+docName)){
            mutex_db->unlock();

            // Documento creato e correttamente inserito nel DB
            // Associazione nome_doc - docId nella QMap
            mutex_docs->lock();
            int id = documents.size();
            id++;
            documents.insert(username + "_" + docName, id);
            mutex_docs->unlock();

            // todo ila&paolo ------------------------------------------------------------------------------------------------------------------------------

            // Aggiungo la riga (docId, [userId]) alla mappa degli workingUsers
            int esito = addToWorkingUsers(id, userId, 0);
            if(esito == 0){
                out << "errore";
                socket->write(blocko);
                return;
            }

            // Faccio la connect per venire notificato da un altro thread in caso di nuovo carattere da processare
            //    connect(Thread_management, SIGNAL(notifica_gli_altri()), this, SLOT(sono_stato_notificato()));

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

            // todo ila: sistemare la aggiungiPartecipante (site_id e site_counter) ------------------------------------------------------------------

            // Associazione username - nome_doc nella tabella utente_doc del DB
            mutex_db->lock();
            if(database->aggiungiPartecipante(username+"_"+docName, username, 0, 0) != 2){
                mutex_db->unlock();
                out << "ok";
                out << id;
                socket->write(blocko);
            }else{
                mutex_db->unlock();
                out << "errore";
                socket->write(blocko);
            }
        }else{
           mutex_db->unlock();
           out << "errore";
           socket->write(blocko);
        }

        // ********************************************************************************
        // GIULIA TODO: gestire meglio il "ritorno" e le modifiche su file -> crdt
        // ********************************************************************************

    } else {
        // se username non esiste o non c'è la cartella relativa
        out << "errore";
        socket->write(blocko);
    }
}


void Thread_management::openDoc(int docId, int userId){
    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    // todo ila&paolo ------------------------------------------------------------------------------------------------------------------------------

    // Aggiorno la riga (docId, [userId, ...]) nella mappa degli workingUsers
    int esito = addToWorkingUsers(docId, userId, 1);
    if(esito == 0){
        out << "errore";
        socket->write(blocko);
        return;
    }

    // Faccio la connect per venire notificato da un altro thread in caso di nuovo carattere da processare
    //    connect(Thread_management, SIGNAL(notifica_gli_altri()), this, SLOT(sono_stato_notificato()));

    // cose extra (che per ora ancora non so) da fare quando si apre il doc
}


void Thread_management::create(QString username, QString password, QString nickname, QString icon){
    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    mutex_db->lock();
    int ret = database->signup(username, password, nickname, icon);
    mutex_db->unlock();
    if(ret == 1){
        //qDebug() << "OK";                    // DEBUG
        // Dati correttamente inseriti nel DB
        mutex_users->lock();
        int id = users.size();
        id++;
        //qDebug()<<"STO SCRIVENDO NELLA MAPPA LA COPPIA key:"<<username<<" E value: "<<id;        // DEBUG
        users.insert(username, id);
        mutex_users->unlock();
        //creo la cartella sul file system per l'utente
        QDir dir = QDir::root();
        dir.mkpath(path+username);
        //verifico sia stata correttamente creata
        if(QDir(path+username).exists()){
            out << "ok";
            out << id;
            socket->write(blocko);
        }
    } else {
        //qDebug() << "BLEAH "<<ret;             // DEBUG
        out << "errore";
        socket->write(blocko);
    }
}


void Thread_management::login(QString username, QString password){
    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    mutex_db->lock();
    std::vector<QString> v = database->login(username, password);
    mutex_db->unlock();
    if(v.size()==2){
        //GESTIRE                           <---------- GIULIA?!?!? ----------------------------------------------
        mutex_users->lock();
        int id = users[username];
        if(id == 0){
            id = users.size();
            id++;
            users.insert(username, id);
        }
        mutex_users->unlock();
        out << "ok";
        out << id;
        socket->write(blocko);
    }else{
        out << "errore";
        socket->write(blocko);
    }
}


void Thread_management::update(int userId, QString password, QString nickname, QString icon){
    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    QString username;
    mutex_users->lock();
    QMapIterator<QString, int> i(users);
    while (i.hasNext()) {
        i.next();
        if(i.value()==userId){
            username = i.key();
            break;
        }
    }
    mutex_users->unlock();
    if(!username.isEmpty()){
        mutex_db->lock();
        if(database->aggiornaUser(username, password, nickname, icon)){
            mutex_db->unlock();
            //correttamente aggiornato nel db
            out << "ok";
            socket->write(blocko);
        }else{
            mutex_db->unlock();
//                qDebug()<<"ERRORE QUI 0";          // DEBUG
            out << "errore";
            socket->write(blocko);
        }
    }else{
//            qDebug()<<"ERRORE QUI 4";           // DEBUG
        out << "errore";
        socket->write(blocko);
    }
}


void Thread_management::getUsername(int userId){
    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    QString username;
    mutex_users->lock();
    QMapIterator<QString, int> i(users);
    while (i.hasNext()) {
        i.next();
        if(i.value()==userId){
            username = i.key();
            break;
        }
    }
    mutex_users->unlock();
    if(!username.isEmpty()){
        out << username;
        socket->write(blocko);
    }else{
        out << "errore";
        socket->write(blocko);
    }
}


void Thread_management::getNickname(int userId){
    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    QString username;
    //qDebug() << "L'UTENTE MI HA DATO COME userID... "<<userId;       // DEBUG
    mutex_users->lock();
    QMapIterator<QString, int> i(users);
    while (i.hasNext()) {
        i.next();
        //qDebug() << "ITERO... key:"<<i.key()<<" E value:"<<i.value();       // DEBUG
        if(i.value()==userId){
            username=i.key();
            break;
        }
    }
    mutex_users->unlock();
    if(!username.isEmpty()){
        //qDebug()<<"YESS";                       // DEBUG
        mutex_db->lock();
        QString nick = database->getNickname(username);       // DEBUG
        mutex_db->unlock();
        out << nick.toLocal8Bit();
        socket->write(blocko);
    }else{
        //qDebug()<<"ZIOFA";                      // DEBUG
        out << "errore";
        socket->write(blocko);
    }
}


void Thread_management::getIcon(int userId){
    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    QString username;
    mutex_users->lock();
    QMapIterator<QString, int> i(users);
    while (i.hasNext()) {
        i.next();
        if(i.value()==userId){
            username = i.key();
            break;
        }
    }
    mutex_users->unlock();
    if(!username.isEmpty()){
        mutex_db->lock();
        QString icon = database->getIconId(username);
        mutex_db->unlock();
        out << icon.toLocal8Bit();
        socket->write(blocko);
    }else{
        out << "errore";
        socket->write(blocko);
    }
}

void Thread_management::getDocs(int userId){
    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    mutex_users->lock();
    QString username;
    QMapIterator<QString, int> i(users);
    while (i.hasNext()) {
        i.next();
        if(i.value()==userId){
            username = i.key();
            break;
        }
    }
    mutex_users->unlock();

    // ****************** DA TOGLIEREEEEE *********************                         // DEBUG
//    database->creaDoc("DivinaCommedia");
//    database->creaDoc("Oibaboi");
//    database->aggiungiPartecipante("DivinaCommedia", "ilagioda@gimpteam.it");
//    database->aggiungiPartecipante("Oibaboi", "ilagioda@gimpteam.it");
    // ****************** DA TOGLIEREEEEE *********************

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
            // Salvo il nome documento corrente
//            qDebug()<< "GET_DOCS - (*it): "<<(*it);             // DEBUG
            QString doc_name = (*it);
//            qDebug()<< "GET_DOCS - docname: "<<doc_name;             // DEBUG

            // Cerco il docId del documento corrente
            mutex_docs->lock();
            int docId = documents.value(doc_name);
            mutex_docs->unlock();

            // Concateno in una stringa unica da mandare al client

            QString doc;
            if(doc_name != "nessuno"){
                 //se non ho documenti, questa cosa genera sigsev perchè giustamente non riesce a ottenere at(1)
                //ecco perchè aggiunto il controllo
                doc = doc_name.split("_").at(1) + "_" + QString::number(docId);
            }else{
                doc = doc_name+"_"+QString::number(docId);
            }
//            qDebug()<< "GET_DOCS - coppia: "<<doc;             // DEBUG

            // Mando la QString così generata al client
            out << doc.toUtf8();
         }
         socket->write(blocko);
    }else{
        out << "errore";
        socket->write(blocko);
    }
}


void Thread_management::getDocumentDatoUri(QString uri){
    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    mutex_db->lock();
    QString doc = database->recuperaDocDatoURI(uri);
    mutex_db->unlock();
    if(doc != "errore"){
        // Nome del documento relativo all'URI ottenuto dal DB correttamente
        //out << doc.toLocal8Bit();
        //cerco il documentId del documento richiesto e lo ritorno all'utente
        // Cerco il docId del documento corrente
        mutex_docs->lock();
        int docId = documents.value(doc);
        mutex_docs->unlock();
        out << docId;
        socket->write(blocko);
    }else{
        out << -1;
        socket->write(blocko);
    }
}

void Thread_management::getUri(int docId){
    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    QString docName;
    mutex_docs->lock();
    QMapIterator<QString, int> i(documents);
    while (i.hasNext()) {
        i.next();
        if(i.value()==docId){
            docName=i.key();
            break;
        }
    }
    mutex_docs->unlock();
    if(!docName.isEmpty()){
        mutex_db->lock();
//        qDebug()<<"GET_URI ----- docName: "<<docName;      // DEBUG
//        qDebug()<<"GET_URI ----- URI recuperato: "<<database->recuperaURI(docName);     // DEBUG
        out << database->recuperaURI(docName);
        mutex_db->unlock();
        socket->write(blocko);
    }else{
        out << "errore";
        socket->write(blocko);
    }
}

//l'eliminazione di un documento deve avvertire il possessore del documento che anche tutti i collaboratori
//non potranno più accedervi (messaggio di notifica). L'eliminazione del documento da parte dei collaboratori elimina
//solamente la corrispondenza con quel documento nel db.
//eliminare anche dal file system
void Thread_management::deleteDoc(int userId, int docId){
    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    //cerco il nome del documento da eliminare
    QString docName;
    mutex_docs->lock();
    QMapIterator<QString, int> i(documents);
    while (i.hasNext()) {
        i.next();
        if(i.value()==docId){
            docName=i.key();
            break;
        }
    }
    mutex_docs->unlock();

    if(docName.isEmpty()){
        out << "errore";
        socket->write(blocko);
        return;
    }

    //cerco lo username dell'utente che ha chiesto l'eliminazione (per fare
    //la verifica sul fatto che sia l'owner o meno
    QString username;
    mutex_users->lock();
    QMapIterator<QString, int> k(users);
    while (k.hasNext()) {
        k.next();
        if(k.value()==userId){
            username = k.key();
            break;
        }
    }
    mutex_users->unlock();
    if(username.isEmpty()){
        out << "errore";
        socket->write(blocko);
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
            return;
        }
        if(collaboratori.size()==1 && (collaboratori.at(0).at(0)=="errore")) {
            out << "errore";
            socket->write(blocko);
            return;
        }

        //itero sui collaboratori ed elimino il loro documento
        for(auto i:collaboratori){
            mutex_db->lock();
            if(database->rimuoviPartecipante(docName, i.at(0))==0){
                mutex_db->unlock();
                out << "errore";
                socket->write(blocko);
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
        }else{
            mutex_db->unlock();
            //elimino il documento nel file system
            QFile file (path+username+"/"+docName+".txt");
            file.remove();
            out << "ok";
            socket->write(blocko);
        }
    }else{
        //il documento rimane e viene rimosso solo il partecipante
        mutex_db->lock();
        if(database->rimuoviPartecipante(docName, username)==0){
            mutex_db->unlock();
            out << "errore";
            socket->write(blocko);
        }else{
            mutex_db->unlock();
            out << "ok";
            socket->write(blocko);
        }
    }
}

void Thread_management::getDocName(int docId){
    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    QString docName;
    mutex_docs->lock();
    QMapIterator<QString, int> i(documents);
    while (i.hasNext()) {
        i.next();
        if(i.value()==docId){
            docName=i.key();
            break;
        }
    }
    mutex_docs->unlock();
    if(!docName.isEmpty()){
        out << docName.split("_").at(1);
        socket->write(blocko);
    }else{
        out << "errore";
        socket->write(blocko);
    }
}


void Thread_management::getWorkingUsersGivenDoc(int docId){
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

    } else {
        // Documento non presente nella mappa workingUsers
        int no_doc = -1;
        out << no_doc;
        socket->write(blocko);
    }

    mutex_workingUsers->unlock();

}


//void Thread_management::disconnected(){
//    qDebug() << socketDescriptor << " Disconnected";
//    socket->deleteLater();
//    exit(0);
//}

//void Thread_management::executeJob(){
//    std::cout << "THREAD - executeJob terminata"<< std::endl;      // DEBUG
//}
