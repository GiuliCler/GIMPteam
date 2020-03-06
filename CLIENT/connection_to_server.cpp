#include "connection_to_server.h"
#include <stdlib.h>
#include <sstream>
#include <QtWidgets>

connection_to_server::connection_to_server(QString port, QString ipAddress){
    this->tcpSocket=new QTcpSocket(this);
    this->port = port;
    this->ipAddress = ipAddress;

    //richiedo i file di un dato utente al momento del login
    //chiudo la connessione quando viene premuto X (termina il programma)
    //connect(quitButton, SIGNAL(clicked()), this, SLOT(close())); <---------- SISTEMARE
    //connect(&file, SIGNAL(newFile(QString)),this, SLOT(showString(QString)));
    //connect(&file, SIGNAL(error(int,QString)),this, SLOT(displayError(int,QString)));

}

int connection_to_server::requestTryLogin(QString username, QString password)
{
    this->tcpSocket->abort();
    this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

    if (!tcpSocket->waitForConnected(Timeout)) {
        emit error(tcpSocket->error(), tcpSocket->errorString());
        return -1;
    }
    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);

    out << "LOGIN";
    out << username;
    out << password;

    this->tcpSocket->write(buffer);

    if (!this->tcpSocket->waitForBytesWritten(Timeout)) {
        emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
        return -1;
    }

    //ora attendo una risposta dal server, sul login al db
    QByteArray file;
    QDataStream in;
    int userId;
    in.setDevice(this->tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);
    do {
        if (!this->tcpSocket->waitForReadyRead(Timeout)) {
            emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
            return -1;
        }

        in.startTransaction();
        in >> file;
        in >> userId;
    } while (!in.commitTransaction());
    QString c = "ok";
    if(file.contains(c.toUtf8())){
        return userId;
    }else{
        return -1;
    }
}

long connection_to_server::requestCreateDocument(int userId, QString name)
{
    this->tcpSocket->abort();
    this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

    if (!tcpSocket->waitForConnected(Timeout)) {
        emit error(tcpSocket->error(), tcpSocket->errorString());
        return -1;
    }
    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);

    out << "NEW_DOC";
    out << name;
    out << userId;

    this->tcpSocket->write(buffer);

    if (!this->tcpSocket->waitForBytesWritten(Timeout)) {
        emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
        return -1;
    }

    //ora attendo una risposta dal server, sul login al db
    QByteArray file;
    QDataStream in;
    in.setDevice(this->tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);
    do {
        if (!this->tcpSocket->waitForReadyRead(Timeout)) {
            emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
            return -1;
        }

        in.startTransaction();
        in >> file;
    } while (!in.commitTransaction());
    QString c = "ok";
    if(file.contains(c.toUtf8())){
        return 0;
    }else{
        return -1;
    }
    //TODO: il documento viene ritornato e aperto => gestione con CRDT
}

int connection_to_server::requestNewAccount(QString username, QString password, QString nickname, QString icon)
{
    this->tcpSocket->abort();
    this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

    if (!tcpSocket->waitForConnected(Timeout)) {
        emit error(tcpSocket->error(), tcpSocket->errorString());
        return -1;
    }
    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);

    out << "CREATE";
    out << username;
    out << password;
    out << nickname;
    out << icon;

    this->tcpSocket->write(buffer);

    if (!this->tcpSocket->waitForBytesWritten(Timeout)) {
        emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
        return -1;
    }

    //ora attendo una risposta dal server, sul login al db
    QByteArray file;
    int id;
    QDataStream in;
    in.setDevice(this->tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);
    do {
        if (!this->tcpSocket->waitForReadyRead(Timeout)) {
            emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
            return -1;
        }

        in.startTransaction();
        in >> file;
        in >> id;
    } while (!in.commitTransaction());
    QString c = "errore";
    if(file.contains(c.toUtf8())){
        return -1;
    }else{
        return id;
    }
}

long connection_to_server::requestUpdateAccount( int userId, QString password, QString nickname, QString icon)
{
    this->tcpSocket->abort();
    this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

    if (!tcpSocket->waitForConnected(Timeout)) {
        emit error(tcpSocket->error(), tcpSocket->errorString());
        return -1;
    }
    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);

    out << "UPDATE";
    out << userId;
    out << password;
    out << nickname;
    out << icon;

    this->tcpSocket->write(buffer);

    if (!this->tcpSocket->waitForBytesWritten(Timeout)) {
        emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
        return -1;
    }

    //ora attendo una risposta dal server, sul login al db
    QByteArray file;
    QDataStream in;
    in.setDevice(this->tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);
    do {
        if (!this->tcpSocket->waitForReadyRead(Timeout)) {
            emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
            return -1;
        }

        in.startTransaction();
        in >> file;
    } while (!in.commitTransaction());
    QString c = "ok";
    if(file.contains(c.toUtf8())){
        return 0;
    }else{
        return -1;
    }
}

std::string connection_to_server::requestDocDatoUri(QString uri){
    this->tcpSocket->abort();
    this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

    if (!tcpSocket->waitForConnected(Timeout)) {
        emit error(tcpSocket->error(), tcpSocket->errorString());
        return "errore";
    }
    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);

    out << "GET_DOCUMENT_DATO_URI";
    out << uri;

    this->tcpSocket->write(buffer);

    if (!this->tcpSocket->waitForBytesWritten(Timeout)) {
        emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
        return "errore";
    }

    //ora attendo una risposta dal server, sul login al db
    QByteArray file;
    QDataStream in;
    in.setDevice(this->tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);
    do {
        if (!this->tcpSocket->waitForReadyRead(Timeout)) {
            emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
            return "errore";
        }

        in.startTransaction();
        in >> file;
    } while (!in.commitTransaction());
    return std::string(file);
}

std::string connection_to_server::requestUri(long docId){
    this->tcpSocket->abort();
    this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

    if (!tcpSocket->waitForConnected(Timeout)) {
        emit error(tcpSocket->error(), tcpSocket->errorString());
        return "errore";
    }
    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);

    out << "GET_URI";
    out << QString::number(docId);

    this->tcpSocket->write(buffer);

    if (!this->tcpSocket->waitForBytesWritten(Timeout)) {
        emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
        return "errore";
    }

    //ora attendo una risposta dal server, sul login al db
    QByteArray uri;
    QDataStream in;
    in.setDevice(this->tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);

    do {
        if (!this->tcpSocket->waitForReadyRead(Timeout)) {
            emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
            return "errore";
        }

        in.startTransaction();
        in >> uri;
    } while (!in.commitTransaction());
    uri.replace('\0',"");
    return uri.toStdString();
}

//per mostrare i file (nomi)<--------TODO
void connection_to_server::showFile(const QString &next)
{
    //qui stampo il nome del file richiesto al server
    if (next == current) {
        //requestTryLogin();
        return;
    }

    current = next;
    //-----------debug-------------
    QMessageBox::information(this, "", current);

}

std::string connection_to_server::requestGetNickname(int userId){
    this->tcpSocket->abort();
    this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

    if (!tcpSocket->waitForConnected(Timeout)) {
        emit error(tcpSocket->error(), tcpSocket->errorString());
        return "errore";
    }
    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);

    out << "GET_NICKNAME";
    out << userId;

    this->tcpSocket->write(buffer);

    if (!this->tcpSocket->waitForBytesWritten(Timeout)) {
        emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
        return "errore";
    }

    //ora attendo una risposta dal server, sul login al db
    QByteArray nickname;
    QDataStream in;
    in.setDevice(this->tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);

    do {
        if (!this->tcpSocket->waitForReadyRead(Timeout)) {
            emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
            return "errore";
        }

        in.startTransaction();
        in >> nickname;
    } while (!in.commitTransaction());
    nickname.replace('\0',"");
    return nickname.toStdString();
}

std::string connection_to_server::requestIconId(int userId){
    this->tcpSocket->abort();
    this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

    if (!tcpSocket->waitForConnected(Timeout)) {
        emit error(tcpSocket->error(), tcpSocket->errorString());
        return "errore";
    }
    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);

    out << "GET_ICON";
    out << userId;

    this->tcpSocket->write(buffer);

    if (!this->tcpSocket->waitForBytesWritten(Timeout)) {
        emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
        return "errore";
    }

    //ora attendo una risposta dal server, sul login al db
    QByteArray iconId;
    QDataStream in;
    in.setDevice(this->tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);

   do {
        if (!this->tcpSocket->waitForReadyRead(Timeout)) {
            emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
            return "errore";
        }

        in.startTransaction();
        in >> iconId;
   } while (!in.commitTransaction());
    iconId.replace('\0',"");
    return iconId.toStdString();
}

std::string connection_to_server::requestGetUsername(int userId){
    this->tcpSocket->abort();
    this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

    if (!tcpSocket->waitForConnected(Timeout)) {
        emit error(tcpSocket->error(), tcpSocket->errorString());
        return "errore";
    }
    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);

    out << "GET_USERNAME";
    out << userId;

    this->tcpSocket->write(buffer);

    if (!this->tcpSocket->waitForBytesWritten(Timeout)) {
        emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
        return "errore";
    }

    //ora attendo una risposta dal server, sul login al db
    QByteArray username;
    QDataStream in;
    in.setDevice(this->tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);
    do {
        if (!this->tcpSocket->waitForReadyRead(Timeout)) {
            emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
            return "errore";
        }

        in.startTransaction();
        in >> username;
    } while (!in.commitTransaction());
    username.replace('\0',"");
    return username.toStdString();
}

void connection_to_server::responseAtRequest(){

}

void connection_to_server::displayError(int socketError, const QString &message)
{
    switch (socketError) {
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, tr("Client"),
                                 tr("The host was not found. Please check the "
                                    "host and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("Client"),
                                 tr("The connection was refused by the peer. "
                                    "Make sure the server is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
        break;
    default:
        QMessageBox::information(this, tr("Client"),
                                 tr("The following error occurred: %1.")
                                 .arg(message));
    }
}


