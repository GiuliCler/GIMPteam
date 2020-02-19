#include "server.h"
#include "threaded.h"

#include <stdlib.h>

//! [0]
Server::Server(QObject *parent)
    : QTcpServer(parent), socketDescriptor(socketDescriptor)
{
    //qui ci andrà la lista di files sul file system del server
    /*fortunes << tr("You've been leading a dog's life. Stay off the furniture.")
             << tr("You've got to think about tomorrow.")
             << tr("You will be surprised by a loud noise.")
             << tr("You will feel hungry again in another hour.")
             << tr("You might have mail.")
             << tr("You cannot kill time without injuring eternity.")
             << tr("Computers are not intelligent. They only think they are.");
*/
    //connessione col DB
    this->database = new CollegamentoDB();
    this->database->connettiDB("gimpdocs_db");
}
//! [0]

//! [1] 
void Server::incomingConnection(qintptr socketDescriptor)
{
    socket=new QTcpSocket(this);
    // This method will get called every time a client tries to connect.
    // We create an object that will take care of the communication with this client
    if (!socket->setSocketDescriptor(socketDescriptor)) {
        emit error(socket->error());
        return;
    }
    //connect(socket, &QTcpSocket::disconnected, this, &Server::disconnectFromClient);
    connect(socket, &QTcpSocket::readyRead, this, &Server::runServer);
}
void Server::runServer()
{

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
      userId++;
      out << userId;
     }else{
      out << "errore";
     }
    socket->write(blocko);
    }
     c = "LOGIN";
     if(text.contains(c.toUtf8())){
        QByteArray username, password;
        in >> username;
        in >> password;
        std::vector<std::string> v = this->database->login(username.toStdString(),password.toStdString());
        if(v.size()==2){
           out << "ok";
        }else{
           out << "errore";
        }
        socket->write(blocko);
      }

     c = "UPDATE";
     if(text.contains(c.toUtf8())){
     QByteArray userId, username, password, nickname, icon;
     in >> username;
     in >> password;
     in >> nickname;
     in >> icon;
     if(this->database->aggiornaUser(username.toStdString(),password.toStdString(), nickname.toStdString(), icon.toStdString())){
       //correttamente inseriti nel db
       out << "ok";
      }else{
       out << "errore";
      }
     socket->write(blocko);
     }

     c = "NEW_DOC";
     if(text.contains(c.toUtf8())){
     QByteArray userId, name;
     in >> name;
     in >> userId;
     //TODO: e lo userId???
     if(this->database->creaDoc(name.toStdString())){
       //correttamente inseriti nel db
       out << "ok";
      }else{
       out << "errore";
      }
     socket->write(blocko);
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
      }else{
       out << "errore";
      }
     socket->write(blocko);
     }

    socket->disconnectFromHost();
    socket->waitForDisconnected();
}

/*void Server::disconnectFromClient()
{
    socket->disconnectFromHost();
    socket->waitForDisconnected();
}*/


