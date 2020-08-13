#include "connection_to_server.h"
#include <stdlib.h>
#include <sstream>
#include <QtWidgets>
#include <iostream>
#include <QSet>
#include "CRDT/crdt_message.h"

connection_to_server::connection_to_server(QString port, QString ipAddress){
    QString s{"SEND"};
    std::cout << "Size di SEND: "<< s.size() << std::endl;
    this->tcpSocket=new QTcpSocket(this);
    this->port = port;
    this->ipAddress = ipAddress;
    this->tcpSocket->setReadBufferSize(0);
    //this->editor = nullptr;
    //richiedo i file di un dato utente al momento del login
    //chiudo la connessione quando viene premuto X (termina il programma)
    //connect(quitButton, SIGNAL(clicked()), this, SLOT(close())); <---------- SISTEMARE
    //connect(&file, SIGNAL(newFile(QString)),this, SLOT(showString(QString)));
    //connect(&file, SIGNAL(error(int,QString)),this, SLOT(displayError(int,QString)));
    // Ridefinisco in e out relativi alla connessione corrente
    in = new QDataStream(this->tcpSocket);
    in->setVersion(QDataStream::Qt_5_12);
//    in->startTransaction();
}
QTcpSocket *connection_to_server::getSocket(){
    qDebug()<<"FUCKING GET SOCKET!!!";      // DEBUG
    return this->tcpSocket;
}

int connection_to_server::requestTryLogOut(int userId)
{
    qDebug()<<"LOGOUT";      // DEBUG

    if(this->tcpSocket->state() == QTcpSocket::UnconnectedState){
        this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

        if (!tcpSocket->waitForConnected(Timeout)) {
            emit error(tcpSocket->error(), tcpSocket->errorString());
            return -1;
        }
    }

    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    out << "LOGOUT";
    out << userId;

    this->tcpSocket->write(buffer);

    if (!this->tcpSocket->waitForBytesWritten(Timeout)) {
        emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
        return -1;
    }

    int result;
    QDataStream in;
    in.setDevice(this->tcpSocket);
    in.setVersion(QDataStream::Qt_5_12);

    do {
        if (!this->tcpSocket->waitForReadyRead(Timeout)) {
            emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
            return -1;
        }

        in.startTransaction();
        in >> result;
    } while (!in.commitTransaction());

    // Chiudo il socket dal lato del client
    this->tcpSocket->close();

    return result;
}

int connection_to_server::requestTryLogin(QString username, QString password)
{
    qDebug()<<"LOGIN";      // DEBUG

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
    out.setVersion(QDataStream::Qt_5_12);

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
    QString err = "errore", c = "ok", d = "alreadyLogged";
    int userId = -1;
    in.setDevice(this->tcpSocket);
    in.setVersion(QDataStream::Qt_5_12);
    do {
        if (!this->tcpSocket->waitForReadyRead(Timeout)) {
            emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
            return -1;
        }

        in.startTransaction();
        in >> file;

        if(file.contains(err.toUtf8()) || file.contains(d.toUtf8())){
            break;
        }

        in >> userId;

    } while (!in.commitTransaction());

    if(file.contains(c.toUtf8())){
        return userId;
    }else{
        if(file.contains(d.toUtf8())){
            throw GUI_GenericException("Attenzione! Login già effettuato su un altro dispositivo!");
        } else {
            return -1;
        }
    }
}

std::string connection_to_server::requestCreateDocument(int userId, QString name)
{
    qDebug()<<"NEW_DOC";      // DEBUG

//    this->tcpSocket->abort();
 /*   qDebug() << this->tcpSocket->state();
    qDebug() << this->ipAddress;
    qDebug() << this->port;  ------------ DEBUG */
    if(this->tcpSocket->state() == QTcpSocket::UnconnectedState){
        this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

        if (!tcpSocket->waitForConnected(Timeout)) {
            emit error(tcpSocket->error(), tcpSocket->errorString());
            return "errore";
        }
    }
    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    out << "NEW_DOC";
    out << name;
    out << userId;

    this->tcpSocket->write(buffer);

    if (!this->tcpSocket->waitForBytesWritten(Timeout)) {
        emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
        return "errore";
    }

    QDataStream in;
    in.setDevice(this->tcpSocket);
    in.setVersion(QDataStream::Qt_5_12);
    do {
        if (!this->tcpSocket->waitForReadyRead(Timeout)) {
            emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
            return "errore";
        }

        in.startTransaction();
        in >> buffer;
    } while (!in.commitTransaction());
    QString c = "ok";
    if(buffer.contains(c.toUtf8())){
        return buffer.toStdString();
    }else{
        return "errore";
    }
    //TODO: il documento viene ritornato e aperto => gestione con CRDT                  // todo ila&paolo
}

std::string connection_to_server::openDoc(int userId, int docId)
{
    qDebug()<<"OPEN_DOC";      // DEBUG

//    this->tcpSocket->abort();
 /*   qDebug() << this->tcpSocket->state();
    qDebug() << this->ipAddress;
    qDebug() << this->port;  ------------ DEBUG */
    if(this->tcpSocket->state() == QTcpSocket::UnconnectedState){
        this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

        if (!tcpSocket->waitForConnected(Timeout)) {
            emit error(tcpSocket->error(), tcpSocket->errorString());
            return "errore";
        }
    }
    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    out << "OPEN_DOC";
    out << docId;
    out << userId;

    this->tcpSocket->write(buffer);

    if (!this->tcpSocket->waitForBytesWritten(Timeout)) {
        emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
        return "errore";
    }

    QDataStream in;
    in.setDevice(this->tcpSocket);
    in.setVersion(QDataStream::Qt_5_12);
    do {
        if (!this->tcpSocket->waitForReadyRead(Timeout)) {
            emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
            return "errore";
        }

        in.startTransaction();
        in >> buffer;
    } while (!in.commitTransaction());

    QString c = "ok";
    QString d = "doc-inesistente";
    if(buffer.contains(c.toUtf8())){
        return buffer.toStdString();
    }else if(buffer.contains(d.toUtf8())){
//        emit unavailableSharedDocument(docId);
        return "errore";
    }

    return "errore";

    //TODO: il documento viene ritornato e aperto => gestione con CRDT                  // todo ila&paolo
}

std::string connection_to_server::requestDocName(int docId){

    qDebug()<<"GET_DOC_NAME";      // DEBUG

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
    out.setVersion(QDataStream::Qt_5_12);

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
    in.setVersion(QDataStream::Qt_5_12);

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
    qDebug()<<"CREATE";      // DEBUG

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
    out.setVersion(QDataStream::Qt_5_12);

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
    QString c = "errore";
    int id = -1;

    QDataStream in;
    in.setDevice(this->tcpSocket);
    in.setVersion(QDataStream::Qt_5_12);
    do {
        if (!this->tcpSocket->waitForReadyRead(Timeout)) {
            emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
            return -1;
        }

        in.startTransaction();
        in >> file;

        if(file.contains(c.toUtf8()))
            break;

        in >> id;

    } while (!in.commitTransaction());

    return id;
}

long connection_to_server::requestUpdateAccount( int userId, QString password, QString nickname, QString icon)
{
    qDebug()<<"UPDATE";      // DEBUG

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
    out.setVersion(QDataStream::Qt_5_12);

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
    QByteArray buff;
    QDataStream in;
    in.setDevice(this->tcpSocket);
    in.setVersion(QDataStream::Qt_5_12);
    do {
        if (!this->tcpSocket->waitForReadyRead(Timeout)) {
            emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
            return -1;
        }

        in.startTransaction();
        in >> buff;
    } while (!in.commitTransaction());

    QString c = "ok";
    if(buff.contains(c.toUtf8())){
        return 0;
    }else{
        return -1;
    }
}

std::string connection_to_server::requestDocDatoUri(QString uri, int userId){
    qDebug()<<"GET_DOCUMENT_DATO_URI";      // DEBUG

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
    out.setVersion(QDataStream::Qt_5_12);

    out << "GET_DOCUMENT_DATO_URI";
    out << uri;
    out << userId;

    this->tcpSocket->write(buffer);

    if (!this->tcpSocket->waitForBytesWritten(Timeout)) {
        emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
        return "errore";
    }

    //ora attendo una risposta dal server, sul login al db
    QByteArray file;
    QDataStream in;
    in.setDevice(this->tcpSocket);
    in.setVersion(QDataStream::Qt_5_12);
    do {
        if (!this->tcpSocket->waitForReadyRead(Timeout)) {
            emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
            return "errore";
        }

        in.startTransaction();
        in >> file;
    } while (!in.commitTransaction());

    QString c = "ok";
    if(file.contains(c.toUtf8())){
        return file.toStdString();
    }else{
        return "errore";
    }
}

std::string connection_to_server::requestUri(int docId){

    qDebug()<<"GET_URI";      // DEBUG

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
    out.setVersion(QDataStream::Qt_5_12);

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
    in.setVersion(QDataStream::Qt_5_12);

    do {
        if (!this->tcpSocket->waitForReadyRead(Timeout)) {
            emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
            return "errore";
        }

        in.startTransaction();
        in >> uri;
    } while (!in.commitTransaction());

    return uri.toStdString();
}

std::shared_ptr<QMap<QString, int>> connection_to_server::getKnownDocuments(int userId){

    qDebug()<<"GET_DOCS";      // DEBUG

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
    out.setVersion(QDataStream::Qt_5_12);

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
    in.setVersion(QDataStream::Qt_5_12);

    do {
        if (!this->tcpSocket->waitForReadyRead(Timeout)) {
            emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
            throw GUI_ConnectionException();
        }

        in.startTransaction();
        in >> num;

        if(num == -1){
            // In caso di errore...
            return std::make_shared<QMap<QString, int>>(ritorno);
        }

        qDebug()<<"CONNECTION_TO_SERVER - num_doc RICEVUTO: "<<num;     // DEBUG

        for(int i=0; i<num; i++){
            in >> doc;
            qDebug()<<"CONNECTION_TO_SERVER - Arrivato dal server... "<<QString::fromStdString(doc.toStdString());       // DEBUG
            vet.push_back(QString::fromStdString(doc.toStdString()));
        }

    } while (!in.commitTransaction());

    qDebug()<<"CONNECTION_TO_SERVER - vet.size(): "<<vet.size();     // DEBUG

    // Conversione del QVector<QString> in <QMap<QString, int>>
    for(auto it=vet.begin(); it<vet.end(); it++){
        QString stringa = (*it);

        if(stringa == "nessuno")
            break;

        QStringList list = stringa.split('_');
        QString doc_name = list.at(0);
        int docId = list.at(1).toInt();

        ritorno.insert(doc_name, docId);
        qDebug()<<"CONNECTION_TO_SERVER - Salvo la coppia (doc_name, docId): ("<<doc_name<<","<<docId<<")";       // DEBUG
    }

    return std::make_shared<QMap<QString, int>>(ritorno);
}

std::string connection_to_server::requestGetNickname(int userId){

    qDebug()<<"GET_NICKNAME";      // DEBUG

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
    out.setVersion(QDataStream::Qt_5_12);

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
    in.setVersion(QDataStream::Qt_5_12);

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

    qDebug()<<"GET_ICON";      // DEBUG

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
    out.setVersion(QDataStream::Qt_5_12);

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
    in.setVersion(QDataStream::Qt_5_12);

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

    qDebug()<<"GET_USERNAME";      // DEBUG

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
    out.setVersion(QDataStream::Qt_5_12);

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
    in.setVersion(QDataStream::Qt_5_12);
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

    qDebug()<<"DELETE_DOC";      // DEBUG

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
    out.setVersion(QDataStream::Qt_5_12);

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
    in.setVersion(QDataStream::Qt_5_12);
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

int connection_to_server::getDocumentOwner(int docId){

    qDebug()<<"GET_DOC_OWNER";      // DEBUG

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
    out.setVersion(QDataStream::Qt_5_12);

    out << "GET_DOC_OWNER";
    out << docId;

    this->tcpSocket->write(buffer);

    if (!this->tcpSocket->waitForBytesWritten(Timeout)) {
        emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
        return -1;
    }

    int ownerId;
    QDataStream in;
    in.setDevice(this->tcpSocket);
    in.setVersion(QDataStream::Qt_5_12);

    do {
        if (!this->tcpSocket->waitForReadyRead(Timeout)) {
            emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
            return -1;
        }

        in.startTransaction();
        in >> ownerId;
    } while (!in.commitTransaction());

    return ownerId;
}

std::shared_ptr<QSet<int>> connection_to_server::getContributors(int docId){
    qDebug()<<"GET_CONTRIBUTORS_ONADOC";      // DEBUG

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
    out.setVersion(QDataStream::Qt_5_12);

    out << "GET_CONTRIBUTORS_ONADOC";
    out << docId;

    this->tcpSocket->write(buffer);

    if (!this->tcpSocket->waitForBytesWritten(Timeout)) {
        emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
        throw GUI_ConnectionException();
    }

    QDataStream in;
    in.setDevice(this->tcpSocket);
    in.setVersion(QDataStream::Qt_5_12);

    int num, id;

    do {
        if (!this->tcpSocket->waitForReadyRead(Timeout)) {
            emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
            throw GUI_ConnectionException();
        }

        in.startTransaction();
        in >> num;

//        qDebug()<<"GET_COLLABORATORS_ONADOC - Ricevuto num_collaborators: "<<num;     // DEBUG

        for(int i=0; i<num; i++){

            in >> id;

            if(id == -1){
                break;
            }
            if(id == -2){
                //errore, lo metto come userId
                vet.insert(-1);
                break;
            }

            vet.insert(id);
        }

    } while (!in.commitTransaction());

//    qDebug()<<"GET_COLLABORATORS_ONADOC - vet.size(): "<<vet.size();     // DEBUG

    return std::make_shared<QSet<int>>(vet);
}

std::shared_ptr<QSet<int>> connection_to_server::getWorkingUsersOnDocument(int docId){

    qDebug()<<"GET_WORKINGUSERS_ONADOC";      // DEBUG

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
    out.setVersion(QDataStream::Qt_5_12);

    out << "GET_WORKINGUSERS_ONADOC";
    out << docId;

    this->tcpSocket->write(buffer);

    if (!this->tcpSocket->waitForBytesWritten(Timeout)) {
        emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
        throw GUI_ConnectionException();
    }

    QDataStream in;
    in.setDevice(this->tcpSocket);
    in.setVersion(QDataStream::Qt_5_12);

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
        if(num == -1)
            break;

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

void connection_to_server::requestSendMessage(CRDT_Message *messaggio){

    qDebug()<<"SEND";      // DEBUG

    //    this->tcpSocket->abort();
        if(this->tcpSocket->state() != QTcpSocket::ConnectedState)
            this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

        if (!tcpSocket->waitForConnected(Timeout)) {
            emit error(tcpSocket->error(), tcpSocket->errorString());
            return;
        }

        QByteArray buffer;
        QDataStream out(&buffer, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_12);

        out << "SEND";
        out << *messaggio;

        this->tcpSocket->write(buffer);

        if (!this->tcpSocket->waitForBytesWritten(Timeout)) {
            emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
            return;
        }
}

void connection_to_server::connectEditor(CRDT_SharedEditor *crdt){

    qDebug()<<"CONNECT EDITOR";      // DEBUG
    //this->editor = editor;
    // TODO
    //qui possiamo verificare se ci sono messaggi da parte del server (riguardo
    //inserimenti di altri utenti o all'avvio dell'editor, se era già stato scritto qualcosa).

    //implementabile con una connect di readyRead sul socket
    this->crdt = crdt;
    connect(this->tcpSocket, &QTcpSocket::readyRead, this, &connection_to_server::receiveMessage);
}

void connection_to_server::disconnectEditor(int userId, int docId){

    qDebug()<<"DISCONNECT EDITOR";      // DEBUG
    this->crdt = nullptr;
    disconnect(this->tcpSocket, &QTcpSocket::readyRead, this, &connection_to_server::receiveMessage);

    if(this->tcpSocket->state() == QTcpSocket::UnconnectedState){
        this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

        if (!tcpSocket->waitForConnected(Timeout)) {
            emit error(tcpSocket->error(), tcpSocket->errorString());
            return;
        }
    }

    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);

    out << "DISCONNECT_FROM_DOC";
    out << docId;
    out << userId;

    this->tcpSocket->write(buffer);

    if (!this->tcpSocket->waitForBytesWritten(Timeout)) {
        emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
        throw GUI_ConnectionException();
    }

    //this->editor = nullptr;
}


void connection_to_server::receiveMessage(){
    if(isProcessing){
        std::cout << "EHEHEH RECEIVE MESSAGE RITORNATA" << std::endl;
        return;
    }

    isProcessing = true;

    while(this->tcpSocket->bytesAvailable() > 0){
        std::cout << "Outside bytesAvailable: " << this->tcpSocket->bytesAvailable();
        while(this->tcpSocket->bytesAvailable() < 5);
        std::cout << "Inside bytesAvailable: " << this->tcpSocket->bytesAvailable() << std::endl;
        QByteArray action;
        //    do{
        //        in.startTransaction();
        *in >> action;
        //    }while(!in.commitTransaction());
        //    std::cout << "SLOT CLIENT receiveAction from server - "<<action.toStdString()<< std::endl;      // DEBUG

        QString c = "OFFLINEUSER";
        if(action.contains(c.toUtf8())){
            //aggiorna la lista degli utenti online
            int userGetOffline;
            *in >> userGetOffline;
            std::cout << userGetOffline<< std::endl;
            //this->editor->removeUserFromEditorGUI(userGetOffline);
            emit sigOfflineUser(userGetOffline);
            continue;
        }

        c = "ONLINEUSER";
        if(action.contains(c.toUtf8())){
            //aggiorna la lista degli utenti online
            int userGetOnline;
            QByteArray iconId, nickname;
            *in >> userGetOnline;
            *in >> iconId;
            *in >> nickname;
            iconId.replace('\0',"");
            std::string icona = iconId.toStdString();
            nickname.replace('\0',"");
            std::string nick = iconId.toStdString();
            std::cout << userGetOnline << "icona: " + icona << " nickname: " + nick << std::endl;
            //this->editor->addUserToEditorGUI(userGetOnline);
            emit sigOnlineUser(userGetOnline); //TODO: nel segnale vanno passati anche nick e icona
            continue;
        }

        c = "NEWCONTRIBUTOR";
        if(action.contains(c.toUtf8())){
            //aggiorna la lista degli utenti online
            int userNewContributor;
            QByteArray iconId, nickname;
            *in >> userNewContributor;
            *in >> iconId;
            *in >> nickname;
            iconId.replace('\0',"");
            std::string icona = iconId.toStdString();
            nickname.replace('\0',"");
            std::string nick = iconId.toStdString();
            std::cout << userNewContributor << "icona: " + icona << " nickname: " + nick << std::endl;
            //this->editor->addUserToEditorGUI(userGetOnline);
            emit sigNewContributor(userNewContributor); //TODO: nel segnale vanno passati anche nick e icona
            continue;
        }

        c = "CRDT";
        if(action.contains(c.toUtf8())){
            CRDT_Message m;
            //        do {
            //            in.startTransaction();
            *in >> m;
            //        } while (!in.commitTransaction());
            //            std::cout << "SLOT CLIENT receiveAction - "<<action.toStdString()<< std::endl;
            std::cout << "SLOT CLIENT messageAction - "<<m.getAzione()<< std::endl;
            if(this->crdt == nullptr)
                std::cout << "PERNACCHIAAAAAAAAAAAAAAAA PRRRRRRRRRR" << std::endl;
            else
                this->crdt->process(m);
            //            emit sigProcessMessage(m);
            //DEBUG
            continue;
            /*            if(!in.commitTransaction()){
                in >> action;
                if(action.isEmpty()){
                    break;
                }
            }
        } while (!in.commitTransaction());*/
        }
        std::cout << "WAAAATTTTAFFFUUUCK size:" << action.size() << "; Content:" << action.toStdString() << ";" << std::endl;
    }
    isProcessing = false;
}
