#include "connection_to_server.h"
#include <stdlib.h>
#include <sstream>
#include <QtWidgets>
#include <iostream>
#include <QSet>

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

int connection_to_server::requestTryLogOut(int userId)
{
    this->tcpSocket->close();
    return 1;
}

int connection_to_server::requestTryLogin(QString username, QString password)
{
    this->tcpSocket->abort();
    if(this->tcpSocket->state() == QTcpSocket::UnconnectedState){
        this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

        if (!tcpSocket->waitForConnected(Timeout)) {
            emit error(tcpSocket->error(), tcpSocket->errorString());
            return -1;
        }
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
//    this->tcpSocket->abort();
 /*   qDebug() << this->tcpSocket->state();
    qDebug() << this->ipAddress;
    qDebug() << this->port;  ------------ DEBUG */
    if(this->tcpSocket->state() == QTcpSocket::UnconnectedState){
        this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

        if (!tcpSocket->waitForConnected(Timeout)) {
            emit error(tcpSocket->error(), tcpSocket->errorString());
            return -1;
        }
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

    int docId;
    QDataStream in;
    in.setDevice(this->tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);
    do {
        if (!this->tcpSocket->waitForReadyRead(Timeout)) {
            emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
            return -1;
        }

        in.startTransaction();
        in >> buffer;
        in >> docId;
    } while (!in.commitTransaction());
    QString c = "ok";
    if(buffer.contains(c.toUtf8())){
        //TODO: settare il nome del documento nella barra in alto.
        return docId;
    }else{
        return -1;
    }
    //TODO: il documento viene ritornato e aperto => gestione con CRDT
}

std::string connection_to_server::requestDocName(int docId){
//    this->tcpSocket->abort();
    if(this->tcpSocket->state() == QTcpSocket::UnconnectedState){
        this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

        if (!tcpSocket->waitForConnected(Timeout)) {
            emit error(tcpSocket->error(), tcpSocket->errorString());
            return "errore";
        }
    }
    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);

    out << "GET_DOC_NAME";
    out << docId;

    this->tcpSocket->write(buffer);

    if (!this->tcpSocket->waitForBytesWritten(Timeout)) {
        emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
        return "errore";
    }

    //ora attendo una risposta dal server, sul login al db
    QByteArray docName;
    QDataStream in;
    in.setDevice(this->tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);

    do {
        if (!this->tcpSocket->waitForReadyRead(Timeout)) {
            emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
            return "errore";
        }

        in.startTransaction();
        in >> docName;
    } while (!in.commitTransaction());
    docName.replace('\0',"");
    return docName.toStdString();
}

int connection_to_server::requestNewAccount(QString username, QString password, QString nickname, QString icon)
{
    this->tcpSocket->abort();
    if(this->tcpSocket->state() == QTcpSocket::UnconnectedState){
        this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

        if (!tcpSocket->waitForConnected(Timeout)) {
            emit error(tcpSocket->error(), tcpSocket->errorString());
            return -1;
        }
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
//    this->tcpSocket->abort();
    if(this->tcpSocket->state() == QTcpSocket::UnconnectedState){
        this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

        if (!tcpSocket->waitForConnected(Timeout)) {
            emit error(tcpSocket->error(), tcpSocket->errorString());
            return -1;
        }
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

long connection_to_server::requestDocDatoUri(QString uri){
//    this->tcpSocket->abort();
    if(this->tcpSocket->state() == QTcpSocket::UnconnectedState){
        this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

        if (!tcpSocket->waitForConnected(Timeout)) {
            emit error(tcpSocket->error(), tcpSocket->errorString());
            return -1;
        }
    }
    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);

    out << "GET_DOCUMENT_DATO_URI";
    out << uri;

    this->tcpSocket->write(buffer);

    if (!this->tcpSocket->waitForBytesWritten(Timeout)) {
        emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
        return -1;
    }

    //ora attendo una risposta dal server, sul login al db
    int file;
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
    return file;
}

std::string connection_to_server::requestUri(int docId){
//    this->tcpSocket->abort();
    if(this->tcpSocket->state() == QTcpSocket::UnconnectedState){
        this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

        if (!tcpSocket->waitForConnected(Timeout)) {
            emit error(tcpSocket->error(), tcpSocket->errorString());
            return "errore";
        }
    }

    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);

    out << "GET_URI";
    out << docId;

    this->tcpSocket->write(buffer);

    if (!this->tcpSocket->waitForBytesWritten(Timeout)) {
        emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
        return "errore";
    }

    //ora attendo una risposta dal server, sul login al db
    QString uri;
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

    return uri.toLocal8Bit().constData();
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

std::shared_ptr<QMap<QString, int>> connection_to_server::getKnownDocuments(int userId){
    QMap<QString, int> ritorno;
//    this->tcpSocket->abort();
    if(this->tcpSocket->state() == QTcpSocket::UnconnectedState){
        this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

        if (!tcpSocket->waitForConnected(Timeout)) {
            emit error(tcpSocket->error(), tcpSocket->errorString());
            return std::make_shared<QMap<QString, int>>(ritorno);
        }
    }
    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);

    out << "GET_DOCS";
    out << userId;

    this->tcpSocket->write(buffer);

    if (!this->tcpSocket->waitForBytesWritten(Timeout)) {
        emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
        throw GUI_ConnectionException();
    }

    int num;
    QByteArray doc;
    QVector<QString> vet;
    QDataStream in;
    in.setDevice(this->tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);

    do {
        if (!this->tcpSocket->waitForReadyRead(Timeout)) {
            emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
            throw GUI_ConnectionException();
        }

        in.startTransaction();
        in >> num;

//        qDebug()<<"CONNECTION_TO_SERVER - num_doc RICEVUTO: "<<num;     // DEBUG

        for(int i=0; i<num; i++){
            in >> doc;
//            qDebug()<<"CONNECTION_TO_SERVER - Arrivato dal server... "<<QString::fromStdString(doc.toStdString());       // DEBUG
            vet.push_back(QString::fromStdString(doc.toStdString()));
        }

    } while (!in.commitTransaction());

//    qDebug()<<"CONNECTION_TO_SERVER - vet.size(): "<<vet.size();     // DEBUG

    // Conversione del QVector<QString> in <QMap<QString, int>>
    for(auto it=vet.begin(); it<vet.end(); it++){
        QString stringa = (*it);
        QStringList list = stringa.split('_');
        QString doc_name = list.at(0);
        int docId = list.at(1).toInt();

        if(doc_name == "nessuno")
            break;

        ritorno.insert(doc_name, docId);
//        qDebug()<<"CONNECTION_TO_SERVER - Salvo la coppia (doc_name, docId): ("<<doc_name<<","<<docId<<")";       // DEBUG
    }

    return std::make_shared<QMap<QString, int>>(ritorno);
}

std::string connection_to_server::requestGetNickname(int userId){
//    this->tcpSocket->abort();
// debug:    qDebug() << this->tcpSocket->state();

    if(this->tcpSocket->state() == QTcpSocket::UnconnectedState){
        this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

        if (!tcpSocket->waitForConnected(Timeout)) {
            emit error(tcpSocket->error(), tcpSocket->errorString());
            return "errore";
        }
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
//    this->tcpSocket->abort();
    if(this->tcpSocket->state() == QTcpSocket::UnconnectedState){
        this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

        if (!tcpSocket->waitForConnected(Timeout)) {
            emit error(tcpSocket->error(), tcpSocket->errorString());
            return "errore";
        }
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
//    this->tcpSocket->abort();
//    qDebug() << this->tcpSocket->state();

    if(this->tcpSocket->state() == QTcpSocket::UnconnectedState){
        this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

        if (!tcpSocket->waitForConnected(Timeout)) {
            emit error(tcpSocket->error(), tcpSocket->errorString());
            return "errore";
        }
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

std::string connection_to_server::requestDeleteDoc(int userId,int documentId){
//    this->tcpSocket->abort();
    if(this->tcpSocket->state() == QTcpSocket::UnconnectedState){
        this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

        if (!tcpSocket->waitForConnected(Timeout)) {
            emit error(tcpSocket->error(), tcpSocket->errorString());
            return "errore";
        }
    }
    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);

    out << "DELETE_DOC";
    out << userId;
    out << documentId;

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
    QString c = "errore";
    if(file.contains(c.toUtf8())){
        return "errore";
    }else{
        return "ok";
    }
}

QString connection_to_server::getDocumentName(int docId){
//    this->tcpSocket->abort();
    if(this->tcpSocket->state() == QTcpSocket::UnconnectedState){
        this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

        if (!tcpSocket->waitForConnected(Timeout)) {
            emit error(tcpSocket->error(), tcpSocket->errorString());
            return "errore";
        }
    }

    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);

    out << "GET_DOCNAME";
    out << docId;

    this->tcpSocket->write(buffer);

    if (!this->tcpSocket->waitForBytesWritten(Timeout)) {
        emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
        return "errore";
    }

    QString doc_name;
    QDataStream in;
    in.setDevice(this->tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);

    do {
        if (!this->tcpSocket->waitForReadyRead(Timeout)) {
            emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
            return "errore";
        }

        in.startTransaction();
        in >> doc_name;
    } while (!in.commitTransaction());

    return doc_name;
}

std::shared_ptr<QSet<int>> connection_to_server::getWorkingUsersOnDocument(int docId){
    std::shared_ptr<QSet<int>> ritorno;
    QSet<int> vet;
//    this->tcpSocket->abort();
    if(this->tcpSocket->state() == QTcpSocket::UnconnectedState){
        this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

        if (!tcpSocket->waitForConnected(Timeout)) {
            emit error(tcpSocket->error(), tcpSocket->errorString());
            vet.insert(-1);
            return std::make_shared<QSet<int>>(vet);
        }
    }

    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);

    out << "GET_WORKINGUSERS_ONADOC";
    out << docId;

    this->tcpSocket->write(buffer);

    if (!this->tcpSocket->waitForBytesWritten(Timeout)) {
        emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
        throw GUI_ConnectionException();
    }

    QDataStream in;
    in.setDevice(this->tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);

    int num, id;


    do {
        if (!this->tcpSocket->waitForReadyRead(Timeout)) {
            emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
            throw GUI_ConnectionException();
        }

        in.startTransaction();
        in >> num;

//        qDebug()<<"GET_WORKINGUSERS_ONADOC - Ricevuto num_working_users: "<<num;     // DEBUG

        // Controllo il caso di documento non risulta presente nella mappa del server workingUsers
        // NOTA PER ILA: controllare che "continue" funzioni... Eventualmente mettere "break" -------------------
        if(num == -1)
            continue;

        for(int i=0; i<num; i++){
            in >> id;
//            qDebug()<<"GET_WORKINGUSERS_ONADOC - Arrivato dal server... ID:"<<id;       // DEBUG
            if(id == -1)
                break;
            vet.insert(id);
        }

    } while (!in.commitTransaction());

//    qDebug()<<"GET_WORKINGUSERS_ONADOC - vet.size(): "<<vet.size();     // DEBUG

    return std::make_shared<QSet<int>>(vet);
}

void connection_to_server::displayError(int socketError, const QString &message) {
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
