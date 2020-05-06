#include "thread_body.h"
#include <iostream>
#include <sstream>
#include <QThread>

Thread_body::Thread_body(int socketDescriptor, QObject *parent) : QObject(parent)
{
    auto thread_id = std::this_thread::get_id();
    std::stringstream ss;
    ss << thread_id;
    std::string thread_id_string = ss.str();

    std::cout << "---- ThreadBody constructor id: "<<thread_id<<" ---- "<< std::endl;      // DEBUG

    socket = new QTcpSocket();
    if (!socket->setSocketDescriptor(socketDescriptor)) {
        emit error(socket->error());
        return;
    }

    // Creo nel thread un collegamento al DB, mettendo come nome univoco di connessione "connSOCKETDESCRIPTOR"
    database = new CollegamentoDB();
    database->connettiDB("gimpdocs_db", "conn" + QString::fromStdString(thread_id_string));

    // Ridefinisco in e out relativi alla connessione corrente
    QByteArray text;
    in = new QDataStream(socket);
    in->setVersion(QDataStream::Qt_5_12);
    in->startTransaction();
}

void Thread_body::executeJob(){
    auto thread_id = std::this_thread::get_id();

    std::cout << "THREAD - executeJob; Thread: "<<thread_id<<" ---- "<< std::endl;
}
