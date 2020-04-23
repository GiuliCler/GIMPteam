#include "server.h"
#include <stdlib.h>
#include <QThreadPool>
#include <QRunnable>
#include <QFileSystemModel>
#include <QTreeView>


Server::Server(QObject *parent): QTcpServer(parent), socketDescriptor(socketDescriptor) {

    // std::cout << "SONO NEL COSTRUTTORE Server" << std::endl;             // DEBUG -----------

    // Connessione al DB
    this->database = new CollegamentoDB();
    this->database->connettiDB("gimpdocs_db");

    // Riempimento della QMap degli utenti con gli elementi presenti sul DB
    int cont = 0;
    std::vector<QString> utenti = this->database->recuperaUtentiNelDB();
    for(auto i=utenti.begin(); i<utenti.end(); i++){
        if((*i) == "nessuno"){
            break;
        }
        this->users.insert(QString::fromStdString((*i).toStdString()), cont++);
    }

    // Riempimento della QMap dei documenti con gli elementi presenti sul DB
    cont = 0;
    std::vector<QString> documenti = this->database->recuperaDocsNelDB();
    for(auto i=documenti.begin(); i<documenti.end(); i++){
        if((*i) == "nessuno"){
            break;
        }
        this->documents.insert(QString::fromStdString((*i).toStdString()), cont++);
    }

    // std::cout << "FINE COSTRUTTORE Server" << std::endl;             // DEBUG -----------



    // ILA: loop infinito........................................?
}

// ILA: classi che implementanto QRunnable ............................?

void Server::incomingConnection(qintptr socketDescriptor) {
    /*
     * This method will get called every time a client tries to connect ("when a new connection is available" cit.)
     * @param socketDescriptor: it's the native socket descriptor for the accepted connection
     * We create an object that will take care of the communication with this client
    */

    socket = new QTcpSocket(this);
    if (!socket->setSocketDescriptor(socketDescriptor)) {
        emit error(socket->error());
        return;
    }

    //std::cout << "SONO NELLA incomingConnection" << std::endl;             // DEBUG -----------

    //connect(socket, &QTcpSocket::disconnected, this, &Server::disconnectFromClient);
    connect(socket, &QTcpSocket::readyRead, this, &Server::runServer);
}

void Server::runServer() {
    //TODO: valutare il path, al momento quello di Giulia
    QString path = "C:/Users/giuli/Desktop/PROGETTO MALNATI/Server/Files/";
    QByteArray text;
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_12);

    in.startTransaction();
    in >> text;
    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    QString c = "CREATE";
    if(text.contains(c.toUtf8())){
        //std::cout << "SONO DENTRO LA CREATE" << std::endl;             // DEBUG -----------
        QString username, password, nickname, icon;
        in >> username;
        in >> password;
        in >> nickname;
        in >> icon;
        //std::cout << "PRIMA DELLA signup, USERNAME:"<<username.toStdString() << std::endl;             // DEBUG -----------
        int ret = this->database->signup(QString::fromStdString(username.toStdString()), QString::fromStdString(password.toStdString()), QString::fromStdString(nickname.toStdString()), QString::fromStdString(icon.toStdString()));
        if(ret == 1){
            //std::cout << "OK" << std::endl;             // DEBUG -----------
            // Dati correttamente inseriti nel DB
            int id = this->users.size();
            id++;
            //std::cout<<"STO SCRIVENDO NELLA MAPPA LA COPPIA key:"<<username.toStdString()<<" E value: "<<id<<std::endl;   // DEBUG -----------
            this->users.insert(QString::fromStdString(username.toStdString()), id);

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
            //std::cout << "BLEAH "<<ret<< std::endl;             // DEBUG -----------
            out << "errore";
            socket->write(blocko);
        }
    }

    c = "LOGIN";
    if(text.contains(c.toUtf8())){
        QString username, password;
        in >> username;
        in >> password;
        std::vector<QString> v = this->database->login(QString::fromStdString(username.toStdString()), QString::fromStdString(password.toStdString()));
        if(v.size()==2){
            int id = this->users[QString::fromStdString(username.toStdString())];
            if(id == 0){
                id = this->users.size();
                id++;
                this->users.insert(QString::fromStdString(username.toStdString()), id);
            }
            out << "ok";
            out << id;
            socket->write(blocko);
        }else{
            out << "errore";
            socket->write(blocko);
        }
    }

    c = "UPDATE";
    if(text.contains(c.toUtf8())){
        QString password, nickname, icon;
        int userId;
        QString username;
        in >> userId;
        in >> password;
        in >> nickname;
        in >> icon;
        QMapIterator<QString, int> i(this->users);
        while (i.hasNext()) {
            i.next();
            if(i.value()==userId){
                username = i.key();
                break;
            }
        }

        if(!username.isEmpty()){
            if(this->database->aggiornaUser(username, QString::fromStdString(password.toStdString()), QString::fromStdString(nickname.toStdString()), QString::fromStdString(icon.toStdString()))){
                //correttamente aggiornato nel db
                out << "ok";
                socket->write(blocko);
            }else{
                out << "errore";
                socket->write(blocko);
            }
        }else{
            out << "errore";
            socket->write(blocko);
        }
    }

    c = "GET_USERNAME";
    if(text.contains(c.toUtf8())){
        int userId;
        QString username;
        in >> userId;
        QMapIterator<QString, int> i(this->users);
        while (i.hasNext()) {
            i.next();
            if(i.value()==userId){
                username = i.key();
                break;
            }
        }
        if(!username.isEmpty()){
            out << username;
            socket->write(blocko);
        }else{
            out << "errore";
            socket->write(blocko);
        }
    }

    c = "GET_NICKNAME";
    if(text.contains(c.toUtf8())){
        //std::cout << "SONO DENTRO LA GET_NICKNAME" << std::endl;             // DEBUG -----------
        int userId;
        QString username;
        in >> userId;
        //std::cout << "L'UTENTE MI HA DATO COME userID... "<<userId<<std::endl;     // DEBUG -----------
        QMapIterator<QString, int> i(this->users);
        while (i.hasNext()) {
            //username = i.key();
            i.next();
            //std::cout << "ITERO... key:"<<i.key().toStdString()<<" E value:"<<i.value() << std::endl;    // DEBUG -----------
            if(i.value()==userId){
                username=i.key();
                break;
            }
        }
        if(!username.isEmpty()){
            //std::cout<<"YESS"<<std::endl;                       // DEBUG -----------
            QString nick = this->database->getNickname(username);       // DEBUG -----------
            //std::cout<<"VALORE DI RITORNO DELLA getNickname: "<<prova.toStdString()<<std::endl;   // DEBUG -----------
            out << nick.toLocal8Bit();
            socket->write(blocko);
        }else{
            //std::cout<<"ZIOFA"<<std::endl;                      // DEBUG -----------
            out << "errore";
            socket->write(blocko);
        }
    }

    c = "GET_ICON";
    if(text.contains(c.toUtf8())){
        //std::cout << "SONO DENTRO LA GET_ICON" << std::endl;             // DEBUG -----------
        int userId;
        QString username;
        in >> userId;
        QMapIterator<QString, int> i(this->users);
        while (i.hasNext()) {
            i.next();
            if(i.value()==userId){
                username = i.key();
                break;
            }
        }
        if(!username.isEmpty()){
            out << this->database->getIconId(username).toLocal8Bit();
            socket->write(blocko);
        }else{
            out << "errore";
            socket->write(blocko);
        }
    }

    c = "GET_DOCS";
    if(text.contains(c.toUtf8())){
        int userId;
        QString username;
        in >> userId;

        QMapIterator<QString, int> i(this->users);
        while (i.hasNext()) {
            i.next();
            if(i.value()==userId){
                username = i.key();
                break;
            }
        }
        if(!username.isEmpty()){
            // Recupero i documenti per cui l'utente e' abilitato ad accedere
            std::vector<QString> documenti = this->database->recuperaDocs(username);

            // Trasformo il std::vector in QVector
            QVector<QString> documenti_qt = QVector<QString>::fromStdVector(documenti);

            // Mando al client il numero di elementi/documenti che verranno inviati
            int num_doc = documenti_qt.size();
            out << num_doc;

            std::cout << "GET_DOCS - num_doc MANDATO AL CLIENT: "<<num_doc<< std::endl;             // DEBUG -----------

            // Mando al client i nomi dei documenti a cui l'utente può accedere singolarmente
            for(auto it = documenti_qt.begin(); it<documenti_qt.end(); it++){
                // Salvo il nome documento corrente
                QString doc_name = (*it);

                // Cerco il docId del documento corrente
                int docId = documents.value(doc_name);

                // Concateno in una stringa unica da mandare al client
                QString doc = doc_name + "_" + QString::number(docId);
                std::cout << "GET_DOCS - MANDATA AL CLIENT LA COPPIA: "<<doc.toStdString()<< std::endl;             // DEBUG -----------

                // Mando la QString così generata al client
                out << doc.toLocal8Bit();
            }
            socket->write(blocko);
        }else{
            out << "errore";
            socket->write(blocko);
        }
    }

    c = "NEW_DOC";
    if(text.contains(c.toUtf8())){
        QString docName;
        int userId;
        in >> docName;
        in >> userId;
        QString username;
        //controllo che ci sia la cartella del dato utente
        QMapIterator<QString, int> i(this->users);
        while (i.hasNext()) {
            i.next();
            if(i.value()==userId){
                username=i.key();
                break;
            }
        }

        if(!username.isEmpty() && QDir(path+username).exists()){
            if(this->database->creaDoc(QString::fromStdString(docName.toStdString()))){
                // Documento creato e correttamente inserito nel DB
                // Associazione nome_doc - docId nella QMap
                int id = this->documents.size();
                id++;
                this->documents.insert(QString::fromStdString(docName.toStdString()),id);
                // Creazione del file
                QString filename = QString::fromStdString(docName.toStdString());

                //DUBBIO SULL'ESTENSIONE DEL FILE!! Al momento li faccio txt
                QFile file(path+username+"/"+filename+".txt");
                if (file.open(QIODevice::WriteOnly | QIODevice::Text)){
                    QTextStream out(&file);
                    //ATTENZIONE: per scrivere sul file:
                    // out << "The magic number is: " << 49 << "\n";  // DEBUG -----------


                    // *******************************************************
                    // PAOLO TODO: gestione CRDT
                    // *******************************************************
                }
                // Associazione username - nome_doc nella tabella utente_doc del DB
                if(this->database->aggiungiPartecipante(QString::fromStdString(docName.toStdString()),username) != 2){
                    out << "ok";
                    out << id;
                    socket->write(blocko);
                }else{
                    out << "errore";
                    socket->write(blocko);
                }
            }
            // ********************************************************************************
            // GIULIA TODO: gestire meglio il "ritorno" e le modifiche su file -> crdt
            // ********************************************************************************
        } else {
            // Errore nella creazione della entry relativa al documento nel DB
            out << "errore";
            socket->write(blocko);
        }
    }

    c = "GET_DOCUMENT_DATO_URI";
    if(text.contains(c.toUtf8())){
        QByteArray uri;
        in >> uri;
        QString doc = this->database->recuperaDocDatoURI(QString::fromStdString(uri.toStdString()));
        if(doc != "errore"){
            // Nome del documento relativo all'URI ottenuto dal DB correttamente
    // ***************************************************************************************************
    // GIULIA TODO:
    // CERCARE DOCUMENTO NEL FILE SYSTEM CON NOME UGUALE A QUELLO CONTENUTO NELLA VARIABILE
    // doc ED INVIARLO INDIETRO AL CLIENTE
    // ***************************************************************************************************
            out << doc.toLocal8Bit();
            socket->write(blocko);
        }else{
            out << "errore";
            socket->write(blocko);
        }
    }

    c = "GET_URI";
    if(text.contains(c.toUtf8())){
        int docId;
        QString docName;
        in >> docId;
        QMapIterator<QString, int> i(this->documents);
        while (i.hasNext()) {
            i.next();
            if(i.value()==docId){
                docName=i.key();
                break;
            }
        }
        if(!docName.isEmpty()){
            out << this->database->recuperaURI(docName).toLocal8Bit();
            socket->write(blocko);
        }else{
            out << "errore";
            socket->write(blocko);
        }
    }

    socket->disconnectFromHost();
    socket->waitForDisconnected();
}

/*void Server::disconnectFromClient()
{
    socket->disconnectFromHost();
    socket->waitForDisconnected();
}*/
