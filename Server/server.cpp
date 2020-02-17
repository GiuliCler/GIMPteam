#include "server.h"
#include "threaded.h"

#include <stdlib.h>

//! [0]
Server::Server(QObject *parent)
    : QTcpServer(parent), socketDescriptor(socketDescriptor), socket(new QTcpSocket(this))
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
    // This method will get called every time a client tries to connect.
    // We create an object that will take care of the communication with this client
    //Threaded *thread = new Threaded(this, this->database);
    if (!socket->setSocketDescriptor(socketDescriptor)) {
        emit error(socket->error());
        return;
    }
    // connect the signals coming from the object that will take care of the
    // communication with this client to the slots in the central server
        connect(socket, &QTcpSocket::disconnected, this, &Server::disconnectFromClient);
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
                    out << "0";
                    socket->write(blocko);
                }else{
                    out << "-1";
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
                    out << "0";
                    socket->write(blocko);
                }else{
                    out << "-1";
                    socket->write(blocko);
                }
            }

    socket->disconnectFromHost();
    socket->waitForDisconnected();
}

void Server::disconnectFromClient()
{
    socket->disconnectFromHost();
    socket->waitForDisconnected();
}


