#include "thread_management.h"
#include <iostream>
#include <sstream>
#include "server.h"

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
    std::cout << "---- THREAD run id: "<<thread_id<<" ---- "<< std::endl;      // DEBUG

    body = new Thread_body(socketDescriptor);
    QObject::connect(body->socket, &QTcpSocket::readyRead, body, &Thread_body::executeJob);
    Server* babbo = qobject_cast<Server*>(this->parent());
    QObject::connect(body, &Thread_body::testNotifica, babbo, &Server::dispatchNotifica);
    QObject::connect(babbo, &Server::dispatchNotifica, body, &Thread_body::receiveNotifica);

    this->exec();
}
