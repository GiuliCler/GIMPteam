#include "server.h"

#include <stdlib.h>

Server::Server(QObject *parent): QTcpServer(parent), socketDescriptor(socketDescriptor) {
    //connessione col DB
    this->database = new CollegamentoDB();
    this->database->connettiDB("gimpdocs_db");
}

void Server::incomingConnection(qintptr socketDescriptor) {
    socket = new QTcpSocket(this);
    // This method will get called every time a client tries to connect.
    // We create an object that will take care of the communication with this client
    if (!socket->setSocketDescriptor(socketDescriptor)) {
        emit error(socket->error());
        return;
    }
    //connect(socket, &QTcpSocket::disconnected, this, &Server::disconnectFromClient);
    connect(socket, &QTcpSocket::readyRead, this, &Server::runServer);
}

void Server::runServer() {
    QByteArray text;
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_10);

    in.startTransaction();
    in >> text;
    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);

    QString c = "CREATE";
    if(text.contains(c.toUtf8())){
        QByteArray username, password, nickname, icon;
        in >> username;
        in >> password;
        in >> nickname;
        in >> icon;
        if(this->database->signup(username.toStdString(),password.toStdString(), nickname.toStdString(), icon.toStdString())){
            //correttamente inseriti nel db
            int id = this->users.size();
            id++;
            this->users.insert(username.toStdString(),id);
            out << "ok";
            out << id;
            socket->write(blocko);
        } else {
            out << "errore";
            socket->write(blocko);
        }
    }

    c = "LOGIN";
    if(text.contains(c.toUtf8())){
        QByteArray username, password;
        in >> username;
        in >> password;
        std::vector<std::string> v = this->database->login(username.toStdString(),password.toStdString());
        if(v.size()==2){
            //GESTIRE
            int id = this->users[username.toStdString()]; //dovrebbe essere in realtà ritornato dal DB
            if(id == 0){
                id = this->users.size();
                id++;
                this->users.insert(username.toStdString(),id);
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
        std::string username;
        in >> userId;
        in >> password;
        in >> nickname;
        in >> icon;
        QMapIterator<std::string, int> i(this->users);
        while (i.hasNext()) {
            i.next();
            if(i.value()==userId){
                username=i.key();
                break;
            }
        }
        if(!username.empty()){
            if(this->database->aggiornaUser(username,password.toStdString(), nickname.toStdString(), icon.toStdString())){
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
        std::string username;
        in >> userId;
        QMapIterator<std::string, int> i(this->users);
        while (i.hasNext()) {
            i.next();
            if(i.value()==userId){
                username=i.key();
                break;
            }
        }
        if(!username.empty()){
            out << QString::fromStdString(username);
            socket->write(blocko);
        }else{
            out << "errore";
            socket->write(blocko);
        }
    }

    c = "GET_NICKNAME";
    if(text.contains(c.toUtf8())){
        int userId;
        std::string username;
        in >> userId;
        QMapIterator<std::string, int> i(this->users);
        while (i.hasNext()) {
            i.next();
            if(i.value()==userId){
                username=i.key();
                break;
            }
        }
        if(!username.empty()){
            out << QString::fromStdString(this->database->getNickname(username));
            socket->write(blocko);
        }else{
            out << "errore";
            socket->write(blocko);
        }
    }

    c = "GET_ICON";
    if(text.contains(c.toUtf8())){
        int userId;
        std::string username;
        in >> userId;
        QMapIterator<std::string, int> i(this->users);
        while (i.hasNext()) {
            i.next();
            if(i.value()==userId){
                username=i.key();
                break;
            }
        }
        if(!username.empty()){
            out << QString::fromStdString(this->database->getIconId(username));
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
        if(this->database->creaDoc(name.toStdString())){
            int id = this->documents.size();
            id++;
            this->users.insert(name.toStdString(),id);
            //correttamente inseriti nel db
            //creo il file
            QString filename=QString::fromStdString(name.toStdString());
            QFile file( ":/Files/"+filename );
            if ( file.open(QIODevice::ReadWrite) )
            {
                QTextStream stream( &file );
                stream << "something" << endl;
                //TODO: gestione CRT
            }
            std::string username;
            QMapIterator<std::string, int> i(this->users);
            while (i.hasNext()) {
                i.next();
                if(i.value()==userId){
                    username=i.key();
                    break;
                }
            }
            if(!username.empty()){
                if(this->database->aggiungiPartecipante(name.toStdString(),username)!=2){
                    out << "ok";
                    out << id;
                    socket->write(blocko);
                }else{
                    out << "errore";
                    socket->write(blocko);
                }
            }
            //TODO: gestire meglio il "ritorno" e le modifiche su file -> crt
        } else {
            out << "errore";
            socket->write(blocko);
        }
    }

    c = "GET_DOCUMENT_DATO_URI";
    if(text.contains(c.toUtf8())){
        QByteArray uri;
        in >> uri;
        QString doc = QString::fromStdString(this->database->recuperaDocDatoURI(uri.toStdString()));
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
        std::string name;
        in >> docId;
        QMapIterator<std::string, int> i(this->documents);
        while (i.hasNext()) {
            i.next();
            if(i.value()==docId){
                name=i.key();
                break;
            }
        }
        if(!name.empty()){
            out << QString::fromStdString(this->database->recuperaURI(name));
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
