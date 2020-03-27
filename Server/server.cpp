#include "server.h"
#include <stdlib.h>
#include <QThreadPool>
#include <QRunnable>


Server::Server(QObject *parent): QTcpServer(parent), socketDescriptor(socketDescriptor) {

    // Connessione al DB
    this->database = new CollegamentoDB();
    this->database->connettiDB("gimpdocs_db");

    //std::cout << "SONO NEL COSTRUTTORE Server" << std::endl;             // DEBUG -----------

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
        QByteArray username, password, nickname, icon;
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
            out << "ok";
            out << id;
            socket->write(blocko);
        } else {
            //std::cout << "BLEAH "<<ret<< std::endl;             // DEBUG -----------
            out << "errore";
            socket->write(blocko);
        }
    }

    c = "LOGIN";
    if(text.contains(c.toUtf8())){
        QByteArray username, password;
        in >> username;
        in >> password;
        std::vector<QString> v = this->database->login(QString::fromStdString(username.toStdString()), QString::fromStdString(password.toStdString()));
        if(v.size()==2){
            //GESTIRE
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
        QByteArray password, nickname, icon;
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
            i.next();
            //std::cout << "ITERO... key:"<<i.key().toStdString()<<" E value:"<<i.value() << std::endl;    // DEBUG -----------
            if(i.value()==userId){
                username=i.key();
                break;
            }
        }
        if(!username.isEmpty()){
            //std::cout<<"YESS"<<std::endl;                       // DEBUG -----------
            QString prova = this->database->getNickname(username);       // DEBUG -----------
            //std::cout<<"VALORE DI RITORNO DELLA getNickname: "<<prova.toStdString()<<std::endl;   // DEBUG -----------
            out << prova.toLocal8Bit();
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

    c = "NEW_DOC";
    if(text.contains(c.toUtf8())){
        QByteArray name;
        int userId;
        in >> name;
        in >> userId;
        //associo allo userId il docId
        if(this->database->creaDoc(QString::fromStdString(name.toStdString()))){
            int id = this->documents.size();
            id++;
            this->users.insert(QString::fromStdString(name.toStdString()),id);
            //correttamente inseriti nel db
            //creo il file
            QString filename=QString::fromStdString(name.toStdString());
            QFile file( ":/Files/"+filename );
            if (file.open(QIODevice::ReadWrite)){
                QTextStream stream( &file );
                stream << "something" << endl;
                //TODO: gestione CRDT
            }
            QString username;
            QMapIterator<QString, int> i(this->users);
            while (i.hasNext()) {
                i.next();
                if(i.value()==userId){
                    username = i.key();
                    break;
                }
            }
            if(!username.isEmpty()){
                if(this->database->aggiungiPartecipante(QString::fromStdString(name.toStdString()),username) != 2){
                    out << "ok";
                    out << id;
                    socket->write(blocko);
                }else{
                    out << "errore";
                    socket->write(blocko);
                }
            }
            //TODO: gestire meglio il "ritorno" e le modifiche su file -> crdt
        } else {
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
            //correttamente ottenuto il nome del doc con quell'uri
            //TODO: CERCARE DOCUMENTO NEL FILE SYSTEM CON NOME uguale a quello della variable doc e inviarlo
            out << doc;
            socket->write(blocko);
        }else{
            out << "errore";
            socket->write(blocko);
        }
    }

    c = "GET_URI";
    if(text.contains(c.toUtf8())){
        int docId;
        QString name;
        in >> docId;
        QMapIterator<QString, int> i(this->documents);
        while (i.hasNext()) {
            i.next();
            if(i.value()==docId){
                name=i.key();
                break;
            }
        }
        if(!name.isEmpty()){
            out << this->database->recuperaURI(name);
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
