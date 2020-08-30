#include "connection_to_server.h"
#include <stdlib.h>
#include <sstream>
#include <QtWidgets>
#include <iostream>
#include <QSet>
#include <QPrinter>
#include "CRDT/crdt_message.h"

connection_to_server::connection_to_server(QString port, QString ipAddress): fileTMP(), readBuffer(), readBuffer_size(0){
    this->tcpSocket=new QTcpSocket(this);
    this->port = port;
    this->ipAddress = ipAddress;
    connect(this, &connection_to_server::error, this, &connection_to_server::displayError);
}

QTcpSocket *connection_to_server::getSocket(){
    qDebug()<<"FUCKING GET SOCKET!!!";      // DEBUG
    return this->tcpSocket;
}

QByteArray connection_to_server::getFileTMP(){
    return std::move(fileTMP);
}

int connection_to_server::requestTryLogOut(int userId)
{
    qDebug()<<"LOGOUT";      // DEBUG

    if(this->tcpSocket->state() == QTcpSocket::UnconnectedState){
        this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

        if (!tcpSocket->waitForConnected(Timeout)) {
            //emit error(tcpSocket->error(), tcpSocket->errorString());
            throw GUI_ConnectionException("Timeout Expired.");
            //return -1;
        }
    }

    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    QByteArray comando = "LOGOUT";

    out << comando;
    out << userId;

    if(!writeData(buffer))
        throw GUI_ConnectionException("writeData ERROR. Server not connected.");
        //return -1;

    if(!this->tcpSocket->waitForReadyRead(Timeout)){
        //emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
        throw GUI_ConnectionException("Timeout Expired.");
        //return -1;
    }
    QByteArray data = readData();
    QDataStream in_data(&data, QIODevice::ReadOnly);
    in_data.setVersion(QDataStream::Qt_5_12);

    int result;
    in_data >> result;

    if(result == -1){
        throw GUI_GenericException("Logout ERROR.");
    }

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
            //emit error(tcpSocket->error(), tcpSocket->errorString());
            throw GUI_ConnectionException("Timeout Expired.");
            //return -1;
        }
    }
    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    QByteArray comando = "LOGIN";

    out << comando;
    out << username;
    out << password;

    if(!writeData(buffer))
        throw GUI_ConnectionException("writeData ERROR. Server not connected.");
        //return -1;

    if(!this->tcpSocket->waitForReadyRead(Timeout)){
        //emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
        throw GUI_ConnectionException("Timeout Expired.");
        //return -1;
    }
    QByteArray data = readData();
    QDataStream in_data(&data, QIODevice::ReadOnly);
    in_data.setVersion(QDataStream::Qt_5_12);

    QByteArray esito;
    QString err = "erroreLogin", good = "ok", err2 = "alreadyLogged";
    int userId = -1;

    in_data >> esito;

    if(!esito.contains(err.toUtf8()) && !esito.contains(err2.toUtf8())){
        in_data >> userId;
        return userId;
    }

    if(esito.contains(err2.toUtf8())){
        throw GUI_GenericException("Warning! Already logged on another device!");
    } else {
        throw GUI_GenericException("Login ERROR. Incorrect password or username.");
    }
}

std::string connection_to_server::requestCreateDocument(int userId, QString name)
{
    qDebug()<<"NEW_DOC";      // DEBUG

//    this->tcpSocket->abort();
    if(this->tcpSocket->state() == QTcpSocket::UnconnectedState){
        this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

        if (!tcpSocket->waitForConnected(Timeout)) {
            //emit error(tcpSocket->error(), tcpSocket->errorString());
            throw GUI_ConnectionException("Timeout Expired.");
            //return "errore";
        }
    }

    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    QByteArray comando = "NEW_DOC";

    out << comando;
    out << name;
    out << userId;

    if(!writeData(buffer))
        throw GUI_ConnectionException("writeData ERROR. Server not connected.");
        //return "errore";

    if(!this->tcpSocket->waitForReadyRead(Timeout)){
        //emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
        throw GUI_ConnectionException("Timeout Expired.");
        //return "errore";
    }
    QByteArray data = readData();
    QDataStream in_data(&data, QIODevice::ReadOnly);
    in_data.setVersion(QDataStream::Qt_5_12);

    QByteArray esito;
    in_data >> esito;

    QString good = "ok", err = "erroreGiaCreato";
    if(esito.contains(good.toUtf8())){
        return esito.toStdString();
    }else if(esito.contains(err.toUtf8())){
        throw GUI_GenericException("ERROR. Document name already taken.");
    }else{
        throw GUI_GenericException("Create document ERROR.");
    }
}

std::string connection_to_server::openDoc(int userId, int docId)
{
    qDebug()<<"OPEN_DOC";      // DEBUG

//    this->tcpSocket->abort();
    if(this->tcpSocket->state() == QTcpSocket::UnconnectedState){
        this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

        if (!tcpSocket->waitForConnected(Timeout)) {
            //emit error(tcpSocket->error(), tcpSocket->errorString());
            throw GUI_ConnectionException("Timeout Expired.");
            //return "errore";
        }
    }

    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    QByteArray comando = "OPEN_DOC";

    out << comando;
    out << docId;
    out << userId;

    if(!writeData(buffer))
        throw GUI_ConnectionException("writeData ERROR. Server not connected.");
        //return "errore";

    if(!this->tcpSocket->waitForReadyRead(Timeout)){
        //emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
        throw GUI_ConnectionException("Timeout Expired.");
        //return "errore";
    }
    QByteArray data = readData();
    QDataStream in_data(&data, QIODevice::ReadOnly);
    in_data.setVersion(QDataStream::Qt_5_12);

    QByteArray esito;
    in_data >> esito;

    QString good = "ok", inesist = "doc-inesistente";
    if(esito.contains(good.toUtf8())){

        readDataFile();

        return esito.toStdString();

    } else if (esito.contains(inesist.toUtf8())){
        emit unavailableSharedDocument(docId);
        throw GUI_GenericException("Warning! Impossible to open the selected document. The owner has deleted it.");
    }

    throw GUI_GenericException("Open document ERROR.");
}


std::string connection_to_server::requestDocIdDatoUri(QString uri, int userId){
    qDebug()<<"GET_DOCID_DATO_URI";      // DEBUG

//    this->tcpSocket->abort();
    if(this->tcpSocket->state() == QTcpSocket::UnconnectedState){
        this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

        if (!tcpSocket->waitForConnected(Timeout)) {
            //emit error(tcpSocket->error(), tcpSocket->errorString());
            throw GUI_ConnectionException("Timeout Expired.");
            //return "errore";
        }
    }

    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    QByteArray comando = "GET_DOCID_DATO_URI";

    out << comando;
    out << uri;
    out << userId;

    if(!writeData(buffer))
        throw GUI_ConnectionException("writeData ERROR. Server not connected.");
        //return "errore";

    if(!this->tcpSocket->waitForReadyRead(Timeout)){
        //emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
        throw GUI_ConnectionException("Timeout Expired.");
        //return "errore";
    }
    QByteArray data = readData();
    QDataStream in_data(&data, QIODevice::ReadOnly);
    in_data.setVersion(QDataStream::Qt_5_12);

    QByteArray esito;
    in_data >> esito;

    QString good = "ok";
    QString inesistente = "erroreUriInesistente";
    if(esito.contains(inesistente.toUtf8())){
        throw GUI_GenericException("ERROR: no document with the provided URI exists.");
    }

    if(esito.contains(good.toUtf8())){

//        readDataFile();

        return esito.toStdString();

    } else {
        throw GUI_GenericException("Open document given uri ERROR.");
    }
}


std::string connection_to_server::requestDocName(int docId){

    qDebug()<<"GET_DOC_NAME";      // DEBUG

//    this->tcpSocket->abort();
    if(this->tcpSocket->state() == QTcpSocket::UnconnectedState){
        this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

        if (!tcpSocket->waitForConnected(Timeout)) {
            //emit error(tcpSocket->error(), tcpSocket->errorString());
            throw GUI_ConnectionException("Timeout Expired.");
            //return "errore";
        }
    }

    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    QByteArray comando = "GET_DOC_NAME";

    out << comando;
    out << docId;

    if(!writeData(buffer))
        throw GUI_ConnectionException("writeData ERROR. Server not connected.");
        //return "errore";

    if(!this->tcpSocket->waitForReadyRead(Timeout)){
        //emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
        throw GUI_ConnectionException("Timeout Expired.");
        //return "errore";
    }
    QByteArray data = readData();
    QDataStream in_data(&data, QIODevice::ReadOnly);
    in_data.setVersion(QDataStream::Qt_5_12);

    QByteArray docName;
    in_data >> docName;

    docName.replace('\0',"");       // TODO: siamo sicuri che serva questa riga?

    QString err = "erroreRetrieveDocName";
    if(docName.contains(err.toUtf8())){
        throw GUI_GenericException("ERROR. Impossible to retrieve the document name.");
    }

    return docName.toStdString();
}

std::shared_ptr<QTextEdit> connection_to_server::requestDocumentText(int docId, int userId){
    qDebug()<<"GET_DOC_TEXT";      // DEBUG

//    this->tcpSocket->abort();
    if(this->tcpSocket->state() == QTcpSocket::UnconnectedState){
        this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

        if (!tcpSocket->waitForConnected(Timeout)) {
            throw GUI_ConnectionException("Timeout Expired.");
        }
    }

    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    QByteArray comando = "GET_DOC_TEXT";

    out << comando;
    out << docId;
    out << userId;

    if(!writeData(buffer))
        throw GUI_ConnectionException("writeData ERROR. Server not connected.");

    if(!this->tcpSocket->waitForReadyRead(Timeout)){
        throw GUI_ConnectionException("Timeout Expired.");
    }
    QByteArray data = readData();
    QDataStream in_data(&data, QIODevice::ReadOnly);
    in_data.setVersion(QDataStream::Qt_5_12);

    //ora attendo una risposta dal server
    QByteArray esito;
    in_data >> esito;

    QString good = "ok", inesist = "doc-inesistente";
    if(esito.contains(good.toUtf8())){

        readDataFile();

        QByteArray file = this->getFileTMP();

        QDataStream data(&file, QIODevice::ReadOnly);
        QVector<CRDT_Symbol> simboli;
        data >> simboli;

        std::shared_ptr<QTextEdit> documento (new QTextEdit());

        for(auto it = simboli.begin();it<simboli.end();it++) {
            documento->textCursor().insertText(it->getCarattere(), it->getFormat());
            if(documento->alignment() != it->getAlignment())
                documento->setAlignment(it->getAlignment());
         }

        return documento;

    } else if (esito.contains(inesist.toUtf8())){
        emit unavailableSharedDocument(docId);
        throw GUI_GenericException("Warning! Impossible to export to pdf the selected document. The owner has deleted it.");
    }

    throw GUI_GenericException("Export to PDF ERROR.");
}



int connection_to_server::requestNewAccount(QString username, QString password, QString nickname, QString icon)
{
    qDebug()<<"CREATE";      // DEBUG

    this->tcpSocket->abort();
    if(this->tcpSocket->state() == QTcpSocket::UnconnectedState){
        this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

        if (!tcpSocket->waitForConnected(Timeout)) {
            //emit error(tcpSocket->error(), tcpSocket->errorString());
            throw GUI_ConnectionException("Timeout Expired.");
            //return -1;
        }
    }

    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    QByteArray comando = "CREATE";

    out << comando;
    out << username;
    out << password;
    out << nickname;
    out << icon;

    if(!writeData(buffer))
        throw GUI_ConnectionException("writeData ERROR. Server not connected.");
        //return -1;

    if(!this->tcpSocket->waitForReadyRead(Timeout)){
        //emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
        throw GUI_ConnectionException("Timeout Expired.");
        //return -1;
    }
    QByteArray data = readData();
    QDataStream in_data(&data, QIODevice::ReadOnly);
    in_data.setVersion(QDataStream::Qt_5_12);

    //ora attendo una risposta dal server, sul login al db
    QByteArray esito;
    in_data >> esito;

    QString err = "erroreNellaCreazioneDelProfilo";
    QString err2 = "usernameEsistente";

    if(esito.contains(err2.toUtf8())){
       throw GUI_GenericException("ERROR: the chosen username already exists. Please, select another one.");
    }

    if(esito.contains(err.toUtf8())){
        throw GUI_GenericException("New account ERROR.");
    }

    int id;
    in_data >> id;
    return id;
}

long connection_to_server::requestUpdateAccount( int userId, QString password, QString nickname, QString icon)
{
    qDebug()<<"UPDATE";      // DEBUG

//    this->tcpSocket->abort();
    if(this->tcpSocket->state() == QTcpSocket::UnconnectedState){
        this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

        if (!tcpSocket->waitForConnected(Timeout)) {
           //emit error(tcpSocket->error(), tcpSocket->errorString());
            throw GUI_ConnectionException("Timeout Expired.");
            //return -1;
        }
    }

    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    QByteArray comando = "UPDATE";

    out << comando;
    out << userId;
    out << password;
    out << nickname;
    out << icon;

    if(!writeData(buffer))
        throw GUI_ConnectionException("writeData ERROR. Server not connected.");
        //return -1;

    if(!this->tcpSocket->waitForReadyRead(Timeout)){
        //emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
        throw GUI_ConnectionException("Timeout Expired.");
        //return -1;
    }
    QByteArray data = readData();
    QDataStream in_data(&data, QIODevice::ReadOnly);
    in_data.setVersion(QDataStream::Qt_5_12);

    QByteArray esito;
    in_data >> esito;

    QString good = "ok";
    if(esito.contains(good.toUtf8())){
        return 0;
    }else{
        throw GUI_GenericException("Update account ERROR.");
    }
}

std::string connection_to_server::requestUri(int docId){

    qDebug()<<"GET_URI";      // DEBUG

//    this->tcpSocket->abort();
    if(this->tcpSocket->state() == QTcpSocket::UnconnectedState){
        this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

        if (!tcpSocket->waitForConnected(Timeout)) {
            //emit error(tcpSocket->error(), tcpSocket->errorString());
            throw GUI_ConnectionException("Timeout Expired.");
            //return "errore";
        }
    }

    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    QByteArray comando = "GET_URI";

    out << comando;
    out << docId;

    if(!writeData(buffer))
        throw GUI_ConnectionException("writeData ERROR. Server not connected.");
        //return "errore";

    if(!this->tcpSocket->waitForReadyRead(Timeout)){
        //emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
        throw GUI_ConnectionException("Timeout Expired.");
        //return "errore";
    }
    QByteArray data = readData();
    QDataStream in_data(&data, QIODevice::ReadOnly);
    in_data.setVersion(QDataStream::Qt_5_12);

    QByteArray uri;
    in_data >> uri;

    QString inesist = "doc-inesistente";
    if(uri.contains(inesist.toUtf8())){
        emit unavailableSharedDocument(docId);
        throw GUI_GenericException("Warning! Impossible to retrive the URI of the selected document. The owner has deleted it.");
    }

    return uri.toStdString();
}

std::shared_ptr<QMap<int, QString>> connection_to_server::getKnownDocuments(int userId){

    qDebug()<<"GET_DOCS";      // DEBUG

    QMap<int, QString> ritorno;
//    this->tcpSocket->abort();
    if(this->tcpSocket->state() == QTcpSocket::UnconnectedState){
        this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

        if (!tcpSocket->waitForConnected(Timeout)) {
            //emit error(tcpSocket->error(), tcpSocket->errorString());
            throw GUI_ConnectionException("Timeout Expired.");
            //return std::make_shared<QMap<QString, int>>(ritorno);
        }
    }

    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    QByteArray comando = "GET_DOCS";

    out << comando;
    out << userId;

    if(!writeData(buffer))
        throw GUI_ConnectionException("writeData ERROR. Server not connected.");

    if(!this->tcpSocket->waitForReadyRead(Timeout)){
        //emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
        throw GUI_ConnectionException("Timeout Expired.");
    }
    QByteArray data = readData();
    QDataStream in_data(&data, QIODevice::ReadOnly);
    in_data.setVersion(QDataStream::Qt_5_12);

    int num;
    in_data >> num;

    if(num == -1){
        // In caso di errore...
        throw GUI_GenericException("ERROR. Impossible to retrieve the user's documents.");
        //return std::make_shared<QMap<QString, int>>(ritorno);
    }

//    qDebug()<<"CONNECTION_TO_SERVER - num_doc RICEVUTO: "<<num;     // DEBUG

    QByteArray doc;
    QVector<QString> vet;
    for(int i=0; i<num; i++){
        in_data >> doc;
//        qDebug()<<"CONNECTION_TO_SERVER - Arrivato dal server... "<<QString::fromStdString(doc.toStdString());       // DEBUG
        vet.push_back(QString::fromStdString(doc.toStdString()));
    }

//    qDebug()<<"CONNECTION_TO_SERVER - vet.size(): "<<vet.size();     // DEBUG

    // Conversione del QVector<QString> in <QMap<int, QString>>
    for(auto it=vet.begin(); it<vet.end(); it++){
        QString stringa = (*it);

        if(stringa == "nessuno")
            break;

        QStringList list = stringa.split('_');
        QString doc_name = list.at(0);
        int docId = list.at(1).toInt();

        ritorno.insert(docId, doc_name);
//        qDebug()<<"CONNECTION_TO_SERVER - Salvo la coppia (doc_name, docId): ("<<doc_name<<","<<docId<<")";       // DEBUG
    }

    return std::make_shared<QMap<int, QString>>(ritorno);
}

std::string connection_to_server::requestGetNickname(int userId){

    qDebug()<<"GET_NICKNAME";      // DEBUG

//    this->tcpSocket->abort();

    if(this->tcpSocket->state() == QTcpSocket::UnconnectedState){
        this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

        if (!tcpSocket->waitForConnected(Timeout)) {
            //emit error(tcpSocket->error(), tcpSocket->errorString());
            throw GUI_ConnectionException("Timeout Expired.");
            //return "errore";
        }
    }

    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    QByteArray comando = "GET_NICKNAME";

    out << comando;
    out << userId;

    if(!writeData(buffer))
        throw GUI_ConnectionException("writeData ERROR. Server not connected.");
        //return "errore";

    if(!this->tcpSocket->waitForReadyRead(Timeout)){
        emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
        throw GUI_ConnectionException("Timeout Expired.");
        //return "errore";
    }
    QByteArray data = readData();
    QDataStream in_data(&data, QIODevice::ReadOnly);
    in_data.setVersion(QDataStream::Qt_5_12);

    QByteArray nickname;
    in_data >> nickname;

    nickname.replace('\0',"");      // TODO: siamo sicuri che serva questa riga?

    QString err = "erroreGetNickname";
    if(nickname.contains(err.toUtf8())){
        throw GUI_GenericException("ERROR. Impossible to retrieve the user's nickname.");
    }

    return nickname.toStdString();
}

std::string connection_to_server::requestIconId(int userId){

    qDebug()<<"GET_ICON";      // DEBUG

//    this->tcpSocket->abort();
    if(this->tcpSocket->state() == QTcpSocket::UnconnectedState){
        this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

        if (!tcpSocket->waitForConnected(Timeout)) {
            //emit error(tcpSocket->error(), tcpSocket->errorString());
            throw GUI_ConnectionException("Timeout Expired.");
            //return "errore";
        }
    }

    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    QByteArray comando = "GET_ICON";

    out << comando;
    out << userId;

    if(!writeData(buffer))
        throw GUI_ConnectionException("writeData ERROR. Server not connected.");
        //return "errore";

    if(!this->tcpSocket->waitForReadyRead(Timeout)){
        emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
        throw GUI_ConnectionException("Timeout Expired.");
        //return "errore";
    }
    QByteArray data = readData();
    QDataStream in_data(&data, QIODevice::ReadOnly);
    in_data.setVersion(QDataStream::Qt_5_12);

    QByteArray iconId;
    in_data >> iconId;

    iconId.replace('\0',"");            // TODO: siamo sicuri che serva questa riga?

    QString err = "erroreGetIcon";
    if(iconId.contains(err.toUtf8())){
        throw GUI_GenericException("ERROR. Impossible to retrieve the user's icon.");
    }

    return iconId.toStdString();
}

std::string connection_to_server::requestGetUsername(int userId){

    qDebug()<<"GET_USERNAME";      // DEBUG

//    this->tcpSocket->abort();

    if(this->tcpSocket->state() == QTcpSocket::UnconnectedState){
        this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

        if (!tcpSocket->waitForConnected(Timeout)) {
            //emit error(tcpSocket->error(), tcpSocket->errorString());
            throw GUI_ConnectionException("Timeout Expired.");
            //return "errore";
        }
    }

    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    QByteArray comando = "GET_USERNAME";

    out << comando;
    out << userId;

    if(!writeData(buffer))
        throw GUI_ConnectionException("writeData ERROR. Server not connected.");
        //return "errore";

    if(!this->tcpSocket->waitForReadyRead(Timeout)){
        emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
        throw GUI_ConnectionException("Timeout Expired.");
        //return "errore";
    }
    QByteArray data = readData();
    QDataStream in_data(&data, QIODevice::ReadOnly);
    in_data.setVersion(QDataStream::Qt_5_12);

    QByteArray username;
    in_data >> username;

    username.replace('\0',"");         // TODO: siamo sicuri che serva questa riga?

    QString err = "erroreGetUsername";
    if(username.contains(err.toUtf8())){
        throw GUI_GenericException("ERROR. Impossible to retrieve the user's username.");
    }

    return username.toStdString();
}

std::string connection_to_server::requestDeleteDoc(int userId,int documentId){

    qDebug()<<"DELETE_DOC";      // DEBUG

//    this->tcpSocket->abort();
    if(this->tcpSocket->state() == QTcpSocket::UnconnectedState){
        this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

        if (!tcpSocket->waitForConnected(Timeout)) {
            //emit error(tcpSocket->error(), tcpSocket->errorString());
            throw GUI_ConnectionException("Timeout Expired.");
            //return "errore";
        }
    }

    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    QByteArray comando = "DELETE_DOC";

    out << comando;
    out << userId;
    out << documentId;

    if(!writeData(buffer))
        throw GUI_ConnectionException("writeData ERROR. Server not connected.");
        //return "errore";

    if(!this->tcpSocket->waitForReadyRead(Timeout)){
        emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
        throw GUI_ConnectionException("Timeout Expired.");
        //return "errore";
    }
    QByteArray data = readData();
    QDataStream in_data(&data, QIODevice::ReadOnly);
    in_data.setVersion(QDataStream::Qt_5_12);

    QByteArray esito;
    in_data >> esito;

    QString err = "erroreDeleteDoc", inesist = "doc-inesistente";
    if(esito.contains(err.toUtf8())){
        throw GUI_GenericException("Delete document ERROR.");
    } else if (esito.contains(inesist.toUtf8())){
        emit unavailableSharedDocument(documentId);
        throw GUI_GenericException("Warning! Impossible to delete the selected document. The owner has already deleted it.");
    } else {
        return "ok";
    }
}

int connection_to_server::getDocumentOwner(int docId){

    qDebug()<<"GET_DOC_OWNER";      // DEBUG

//    this->tcpSocket->abort();
    if(this->tcpSocket->state() == QTcpSocket::UnconnectedState){
        this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

        if (!tcpSocket->waitForConnected(Timeout)) {
            //emit error(tcpSocket->error(), tcpSocket->errorString());
            throw GUI_ConnectionException("Timeout Expired.");
            //return -1;
        }
    }

    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    QByteArray comando = "GET_DOC_OWNER";

    out << comando;
    out << docId;

    if(!writeData(buffer))
        throw GUI_ConnectionException("writeData ERROR. Server not connected.");
        //return -1;

    if(!this->tcpSocket->waitForReadyRead(Timeout)){
        emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
        throw GUI_ConnectionException("Timeout Expired.");
        //return -1;
    }
    QByteArray data = readData();
    QDataStream in_data(&data, QIODevice::ReadOnly);
    in_data.setVersion(QDataStream::Qt_5_12);

    int ownerId;
    in_data >> ownerId;

    if(ownerId == -1){
         throw GUI_GenericException("ERROR. Impossible to retrieve the owner's id.");
    }
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
            //emit error(tcpSocket->error(), tcpSocket->errorString());
            throw GUI_ConnectionException("Timeout Expired.");
            //vet.insert(-1);
            //return std::make_shared<QSet<int>>(vet);
        }
    }

    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    QByteArray comando = "GET_CONTRIBUTORS_ONADOC";

    out << comando;
    out << docId;

    if(!writeData(buffer))
        throw GUI_ConnectionException("writeData ERROR. Server not connected.");

    if(!this->tcpSocket->waitForReadyRead(Timeout)){
        emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
        throw GUI_ConnectionException("Timeout Expired.");
    }
    QByteArray data = readData();
    QDataStream in_data(&data, QIODevice::ReadOnly);
    in_data.setVersion(QDataStream::Qt_5_12);

    int num, id;
    in_data >> num;

//    qDebug()<<"GET_COLLABORATORS_ONADOC - Ricevuto num_collaborators: "<<num;     // DEBUG

    for(int i=0; i<num; i++){

        in_data >> id;

        if(id == -1){
            break;
        }
        if(id == -2){
            //errore, lo metto come userId
            //vet.insert(-1);
            //break;
            throw GUI_GenericException("ERROR. Impossible to retrieve the document contributors.");
        }

        vet.insert(id);
    }

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
            //emit error(tcpSocket->error(), tcpSocket->errorString());
            //vet.insert(-1);
            //return std::make_shared<QSet<int>>(vet);
            throw GUI_ConnectionException("Timeout Expired.");
        }
    }

    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    QByteArray comando = "GET_WORKINGUSERS_ONADOC";

    out << comando;
    out << docId;

    if(!writeData(buffer))
        throw GUI_ConnectionException("writeData ERROR. Server not connected.");

    if(!this->tcpSocket->waitForReadyRead(Timeout)){
        emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
        throw GUI_ConnectionException("Timeout Expired.");
    }
    QByteArray data = readData();
    QDataStream in_data(&data, QIODevice::ReadOnly);
    in_data.setVersion(QDataStream::Qt_5_12);

    int num, id;
    in_data >> num;

//    qDebug()<<"GET_WORKINGUSERS_ONADOC - Ricevuto num_working_users: "<<num;     // DEBUG

    // Controllo il caso di documento non risulta presente nella mappa del server workingUsers
    if(num != -1){
        for(int i=0; i<num; i++){
            in_data >> id;
//            qDebug()<<"GET_WORKINGUSERS_ONADOC - Arrivato dal server... ID:"<<id;       // DEBUG
            if(id == -1)
                break;
            vet.insert(id);
        }
        //    qDebug()<<"GET_WORKINGUSERS_ONADOC - vet.size(): "<<vet.size();     // DEBUG

            return std::make_shared<QSet<int>>(vet);
    }
    throw GUI_GenericException("ERROR. Impossible to retrieve the working users on the document.");
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
        //emit error(tcpSocket->error(), tcpSocket->errorString());
        return;
    }

    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    QByteArray comando = "SEND";

    out << comando;
    out << *messaggio;

    writeData(buffer);
}

bool connection_to_server::pingServer(){

    qDebug()<<"PING";      // DEBUG

      if(this->tcpSocket->state() == QTcpSocket::UnconnectedState){
          this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

          if (!tcpSocket->waitForConnected(Timeout)) {
              return false;
          }else{
              return true;
          }
      }
}



void connection_to_server::requestSendMovedCursor(int userId, int pos){

    qDebug()<<"MOVECURSOR";      // DEBUG

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
    QByteArray comando = "MOVECURSOR";

    out << comando;
    out << userId;
    out << pos;

    writeData(buffer);
}


void connection_to_server::connectEditor(){

    qDebug()<<"CONNECT EDITOR - Lettura residui da readBuffer. Size: " << readBuffer.size();      // DEBUG

    if(readBuffer.size() > 0){
        // Mentre ricevevo il file, mi è arrivato anche qualcos'altro che ho messo nel buffer ma che non ho ancora processato
        qint32 size = 0;
        while ((size == 0 && readBuffer.size() >= 4) || (size > 0 && readBuffer.size() >= size))
        {
            if(this->tcpSocket->bytesAvailable() > 0){
                // Mentre sto processando ciò che stava ancora nel buffer, mi sono arrivate altre cose
                readBuffer.append(this->tcpSocket->readAll());
            }

            if (size == 0 && readBuffer.size() >= 4){
                size = ArrayToInt(readBuffer.mid(0, 4));
                readBuffer_size = size;
                readBuffer.remove(0, 4);
            }
            if (size > 0 && readBuffer.size() >= size){
                QByteArray data = readBuffer.mid(0, size);
                readBuffer.remove(0, size);
                size = 0;
                readBuffer_size = size;
                receiveMessage(data);
            }
        }
    }

    qDebug()<<"CONNECT EDITOR - Connect";      // DEBUG

    connect(this->tcpSocket, &QTcpSocket::readyRead, this, &connection_to_server::acceptData);
    connect(this, &connection_to_server::dataReceived, this, &connection_to_server::receiveMessage);

    qDebug()<<"CONNECT EDITOR - Lettura residui tcpSocket->bytesAvailable";      // DEBUG

    if(this->tcpSocket->bytesAvailable() > 0){
        // Dopo aver ricevuto il file e svuotato eventualmente il buffer di cose residue, mi è arrivato qualcosa di non ancora letto
        acceptData();
    }
}

void connection_to_server::disconnectEditor(int userId, int docId){

    qDebug()<<"DISCONNECT EDITOR";      // DEBUG

    disconnect(this->tcpSocket, &QTcpSocket::readyRead, this, &connection_to_server::acceptData);
    disconnect(this, &connection_to_server::dataReceived, this, &connection_to_server::receiveMessage);

    if(this->tcpSocket->state() == QTcpSocket::UnconnectedState){
        this->tcpSocket->connectToHost(this->ipAddress, this->port.toInt());

        if (!tcpSocket->waitForConnected(Timeout)) {
            //emit error(tcpSocket->error(), tcpSocket->errorString());
            return;
        }
    }

    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    QByteArray comando = "DISCONNECT_FROM_DOC";

    out << comando;
    out << docId;
    out << userId;

    if(!writeData(buffer))
        throw GUI_ConnectionException("writeData ERROR. Server not connected.");

    //this->editor = nullptr;
}


void connection_to_server::receiveMessage(QByteArray data){

    QDataStream in_data(&data, QIODevice::ReadOnly);
    in_data.setVersion(QDataStream::Qt_5_12);

    QByteArray action;
    in_data >> action;

    qDebug() << "SLOT CLIENT receiveMessage - action ricevuta: "<<QString::fromStdString(action.toStdString());      // DEBUG

    QString c = "OFFLINEUSER";
    if(action.contains(c.toUtf8())){
        //aggiorna la lista degli utenti online
        int userGetOffline;
        in_data >> userGetOffline;
//        std::cout << userGetOffline<< std::endl;        // DEBUG
        //this->editor->removeUserFromEditorGUI(userGetOffline);
         emit sigOfflineUser(userGetOffline);
    }

    c = "ONLINEUSER";
    if(action.contains(c.toUtf8())){
        //aggiorna la lista degli utenti online
        int userGetOnline;
        QByteArray iconId, nickname;
        in_data >> userGetOnline;
        in_data >> iconId;
        in_data >> nickname;

        iconId.replace('\0',"");                                            // TODO: siamo sicuri che serva questa riga?
        QString icona = QString::fromStdString(iconId.toStdString());

        nickname.replace('\0',"");                                          // TODO: siamo sicuri che serva questa riga?
        QString nick = QString::fromStdString(nickname.toStdString());

        //std::cout << userGetOnline << "icona: " + icona << " nickname: " + nick << std::endl;     // DEBUG
        //this->editor->addUserToEditorGUI(userGetOnline);
        emit sigOnlineUser(userGetOnline, nick, icona);
    }

    c = "NEWCONTRIBUTOR";
    if(action.contains(c.toUtf8())){
        //aggiorna la lista degli utenti online
        int userNewContributor;
        QByteArray iconId, nickname;
        in_data >> userNewContributor;
        in_data >> iconId;
        in_data >> nickname;

        iconId.replace('\0',"");                                            // TODO: siamo sicuri che serva questa riga?
        QString icona = QString::fromStdString(iconId.toStdString());

        nickname.replace('\0',"");                                          // TODO: siamo sicuri che serva questa riga?
        QString nick = QString::fromStdString(nickname.toStdString());

        //std::cout << userNewContributor << "icona: " + icona << " nickname: " + nick << std::endl;
        emit sigNewContributor(userNewContributor, nick, icona);
    }

    c = "FORCECLOSING";
    if(action.contains(c.toUtf8())){

        qDebug()<<"FORCED DISCONNECT EDITOR";      // DEBUG

        disconnect(this->tcpSocket, &QTcpSocket::readyRead, this, &connection_to_server::acceptData);
        disconnect(this, &connection_to_server::dataReceived, this, &connection_to_server::receiveMessage);

        emit forceCloseEditor();
    }

    c = "MOVECURSOR";
    if(action.contains(c.toUtf8())){
        int userId, pos;
        in_data >> userId;
        in_data >> pos;
        qDebug() << "SLOT CLIENT receiveMessage - MOVE - user: "<< userId << "; pos: " << pos;    //DEBUG
        emit sigMoveCursor(userId,pos);
    }

    c = "CRDT";
    if(action.contains(c.toUtf8())){
        CRDT_Message m;
        in_data >> m;
        qDebug() << "SLOT CLIENT receiveMessage - CRDT - m.getAction(): "<<QString::fromStdString(m.getAzione());    //DEBUG
        emit sigProcessMessage(m);
    }
}


bool connection_to_server::writeData(QByteArray data){
    if(this->tcpSocket->state() == QAbstractSocket::ConnectedState) {

        this->tcpSocket->write(IntToArray(data.size()));          // ... write size of data

        this->tcpSocket->write(data);                             // ... write the data itself

        if (!this->tcpSocket->waitForBytesWritten(Timeout)) {
            emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
            throw GUI_ConnectionException("Timeout Expired.");
            //return false;
        }

        return true;

    } else {
        return false;
    }
}


QByteArray connection_to_server::IntToArray(qint32 source)      //Use qint32 to ensure that the number have 4 bytes
{
    // Avoid use of cast, this is the Qt way to serialize objects
    QByteArray temp;
    QDataStream data(&temp, QIODevice::ReadWrite);
    data << source;
    return temp;
}


void connection_to_server::acceptData(){

    qint32 size = readBuffer_size;

    while (this->tcpSocket->bytesAvailable() > 0){

        readBuffer.append(this->tcpSocket->readAll());

        while ((size == 0 && readBuffer.size() >= 4) || (size > 0 && readBuffer.size() >= size))   // While can process data, process it
        {
            if (size == 0 && readBuffer.size() >= 4)        // If size of data has received completely, then store it on our global variable
            {
                size = ArrayToInt(readBuffer.mid(0, 4));
                readBuffer_size = size;
                readBuffer.remove(0, 4);
            }
            if (size > 0 && readBuffer.size() >= size)      // If data has received completely, then emit our SIGNAL with the data
            {
                QByteArray data = readBuffer.mid(0, size);
                readBuffer.remove(0, size);
                size = 0;
                readBuffer_size = size;
                emit dataReceived(data);
            }
        }
    }
}


QByteArray connection_to_server::readData(){

    qint32 size = readBuffer_size;

    while (this->tcpSocket->bytesAvailable() > 0){

        readBuffer.append(this->tcpSocket->readAll());

        while ((size == 0 && readBuffer.size() >= 4) || (size > 0 && readBuffer.size() >= size))   // While can process data, process it
        {
            if (size == 0 && readBuffer.size() >= 4)        // If size of data has received completely, then store it on our global variable
            {
                size = ArrayToInt(readBuffer.mid(0, 4));
                readBuffer_size = size;
                readBuffer.remove(0, 4);
            }
            if (size > 0 && readBuffer.size() >= size)      // If data has received completely, then emit our SIGNAL with the data
            {
                QByteArray data = readBuffer.mid(0, size);
                readBuffer.remove(0, size);
                size = 0;
                readBuffer_size = size;
                return data;
            }
        }
    }

    return "errore";
}


void connection_to_server::readDataFile(){

    // Lettura del numero di simboli contenuti nel file
    if(!this->tcpSocket->waitForReadyRead(Timeout)){
        emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
        return;
    }

    QByteArray data = readData();
    QDataStream in_num(&data, QIODevice::ReadOnly);
    in_num.setVersion(QDataStream::Qt_5_12);

    int num_simboli;
    in_num >> num_simboli;

    qDebug()<<"readDataFile - Ho letto num_simboli: "<<num_simboli;           // DEBUG

    // Lettura dei singoli simboli del file
    qint32 size = readBuffer_size;
    QVector<CRDT_Symbol> simboli;
    int i = 0;
    while(i<num_simboli){

        qDebug()<<"readDataFile - CICLO DI LETTURA i: "<<i+1<<"/"<<num_simboli;         // DEBUG

        if(readBuffer.size() >= 4){

            bool flag = false;
            while ((size == 0 && readBuffer.size() >= 4) || (size > 0 && readBuffer.size() >= size))   // While can process data, process it
            {
                if (size == 0 && readBuffer.size() >= 4)        // If size of data has received completely, then store it on our global variable
                {
                    size = ArrayToInt(readBuffer.mid(0, 4));
                    readBuffer_size = size;
                    readBuffer.remove(0, 4);
                }
                if (size > 0 && readBuffer.size() >= size)      // If data has received completely, then emit our SIGNAL with the data
                {
                    QByteArray data1;
                    data1.clear();
                    QDataStream in_simb(&data1, QIODevice::ReadWrite);
                    in_simb.setVersion(QDataStream::Qt_5_12);

                    data1 = readBuffer.mid(0, size);
                    readBuffer.remove(0, size);
                    size = 0;
                    readBuffer_size = size;

                    CRDT_Symbol s;
                    in_simb >> s;
                    simboli.push_back(s);
                    i++;

                    qDebug()<<"readDataFile - Fatto il push_back del simbolo: "<<s.getCarattere().toLatin1();              // DEBUG

                    flag = true;
                    break;
                }
            }

            if(flag)
                continue;
        }

        if(this->tcpSocket->bytesAvailable() == 0){
            if(!this->tcpSocket->waitForReadyRead(Timeout)){
                emit error(this->tcpSocket->error(), this->tcpSocket->errorString());
                return;
            }
        }

        while (this->tcpSocket->bytesAvailable() > 0){
            readBuffer.append(this->tcpSocket->readAll());
        }
    }

    // Riempio il file temporaneo con il file attuale che sto aprendo
    QDataStream a(&fileTMP, QIODevice::WriteOnly);
    a << simboli;

}


qint32 connection_to_server::ArrayToInt(QByteArray source) {
    qint32 temp;
    QDataStream data(&source, QIODevice::ReadWrite);
    data >> temp;
    return temp;
}
