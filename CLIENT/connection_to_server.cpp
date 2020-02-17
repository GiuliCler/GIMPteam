#include "connection_to_server.h"

#include <QtWidgets>

connection_to_server::connection_to_server(QString port, QString ipAddress){
    this->tcpSocket=new QTcpSocket(this);
    //connect(tcpSocket, &QIODevice::readyRead, this, &connection_to_server::requestNewAccount);
    //connect(tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),this, &connection_to_server::displayError);

    this->port = port;
    this->ipAddress = ipAddress;

    //richiedo i file di un dato utente al momento del login
    //chiudo la connessione quando viene premuto X (termina il programma)
    //connect(quitButton, SIGNAL(clicked()), this, SLOT(close())); <---------- SISTEMARE
    /*connect(&file, SIGNAL(newFile(QString)),
            this, SLOT(showFile(QString)));
    connect(&file, SIGNAL(error(int,QString)),
            this, SLOT(displayError(int,QString)));*/


}

long connection_to_server::requestTryLogin(QString username, QString password)
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
        return 1; //TODO: da sistemare anche qui per userid
    }else{
        return -1;
    }
}

long connection_to_server::requestNewAccount(QString username, QString password, QString nickname, QString icon)
{
    long n=0; ///ATTENZIONE! è DA SISTEMARE, SERVE PER TENERE LO USERID
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
        return n++;
    }else{
        return -1;
    }
}

long connection_to_server::requestUpdateAccount( QString username, QString password, QString nickname, QString icon)
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


