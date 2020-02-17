#include "threaded.h"

#include <QtNetwork>


Threaded::Threaded(QObject *parent, CollegamentoDB *DB)
    : QThread(parent), DB(*DB)
{
}

/*void Threaded::runServer(QTcpSocket *tcpSocket)
{



    QString text;
    //QByteArray block;
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_5_10);
    //sleep(20);
    in.startTransaction();
    in >> text; //è vuota text, ma che caccio... non capisco perchè...


    QByteArray blocko;
    QDataStream out(&blocko, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);

    if(text == "CREATE"){
        QString username, password, nickname, icon;
        in >> username;
        in >> password;
        in >> nickname;
        in >> icon;
        if(DB.signup(username.toStdString(),password.toStdString(), nickname.toStdString(), icon.toStdString())){
            //correttamente inseriti nel db
            out << "0";
            tcpSocket->write(blocko);
        }else{
            out << "-1";
            tcpSocket->write(blocko);
        }
    }

    if(text == "LOGIN"){
        QString username, password;
        in >> username;
        in >> password;
        std::vector<std::string> v = DB.login(username.toStdString(),password.toStdString());
        if(v.size()==2){
            out << "0";
            tcpSocket->write(blocko);
        }else{
            out << "-1";
            tcpSocket->write(blocko);
        }
    }

    //tcpSocket.disconnectFromHost();
    //tcpSocket.waitForDisconnected();
}

void Threaded::disconnectFromClient(QTcpSocket *tcpSocket)
{
    tcpSocket->disconnectFromHost();
    tcpSocket->waitForDisconnected();
}*/

