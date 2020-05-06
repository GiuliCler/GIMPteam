#include "thread_management.h"
#include <iostream>
#include <sstream>

Thread_management::Thread_management(int socketDescriptor, QObject *parent): QThread(parent), socketDescriptor(socketDescriptor){
    qDebug()<< "THREAD - Costruttore del thread con descrittore "<<socketDescriptor;          // DEBUG

    std::cout << "---- THREAD Costruttore id: " << std::this_thread::get_id() << " ---- " << std::endl;      // DEBUG

    qDebug()<< "THREAD - Fine costruttore del thread con descrittore "<<socketDescriptor;       // DEBUG
}


void Thread_management::run(){

    qDebug() << "THREAD - run iniziata";           // DEBUG

    // todo ila&paolo ------------------------------------------------------------------------------------------------------------------------------------
//    int timeoutReadRead = 5000;                     // todo ila : scegliere il timeout della ready read
                                                    // todo ila : scegliere funzione che mi fa la break dal while(1)
                                                    // todo ila : distruzione dei thread nel server
    auto thread_id = std::this_thread::get_id();
    std::stringstream ss;
    ss << thread_id;
    std::string thread_id_string = ss.str();

    std::cout << "---- THREAD run id: "<<thread_id<<" ---- "<< std::endl;      // DEBUG

    body = new Thread_body(socketDescriptor);
    QObject::connect(body->socket, &QTcpSocket::readyRead, body, &Thread_body::executeJob);

    this->exec();

    /*
    while(1){
        qDebug() << this->socket->state();
        if (!socket->waitForReadyRead(timeoutReadRead)) {
          //  qDebug() << "Not enough time";
            emit error(socket->error());
            socket->disconnectFromHost(); //altrimenti non accetta più connessioni da altri client...
            return;
        }
        */
}


//void Thread_management::disconnected(){
//    qDebug() << socketDescriptor << " Disconnected";
//    socket->deleteLater();
//    exit(0);
//}

