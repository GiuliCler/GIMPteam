#include "thread_management.h"
#include <iostream>
#include <sstream>
#include "server.h"

Thread_management::Thread_management(int socketDescriptor, QObject *parent): QThread(parent), socketDescriptor(socketDescriptor){
//    qDebug()<< "THREAD management - Costruttore del thread con descrittore "<<socketDescriptor;          // DEBUG
//    std::cout << "THREAD management - Costruttore id: " << std::this_thread::get_id()<<std::endl;        // DEBUG
//    qDebug()<< "THREAD management - Fine costruttore del thread con descrittore "<<socketDescriptor;     // DEBUG
}

Thread_management::~Thread_management(){
//    std::cout<<"STO DISTRUGGENDO IL THREAD_MANAGEMENT"<<std::endl;              // DEBUG
}

void Thread_management::run(){

//    auto thread_id = std::this_thread::get_id();                                      // DEBUG
//    std::cout << "THREAD management - run - Thread_id: "<<thread_id<< std::endl;      // DEBUG

    Server* babbo = qobject_cast<Server*>(this->parent());

    qRegisterMetaType<CRDT_Message>("CRDT_Message");
    body = new Thread_body(socketDescriptor, babbo->thread());

    QObject::connect(body->socket, &QTcpSocket::readyRead, body, &Thread_body::readData);
    QObject::connect(body, &Thread_body::messageToServer, babbo, &Server::dispatchMessage, Qt::QueuedConnection);
    QObject::connect(babbo, &Server::dispatchMessage, body, &Thread_body::processMessage, Qt::QueuedConnection);

    QObject::connect(babbo, &Server::checkPeriodicoClientConnessi, body, &Thread_body::checkPeriodicoClientConnessiSlot);

    QObject::connect(body, &Thread_body::finished, this, &Thread_management::quit);
    QObject::connect(body, &Thread_body::finished, body, &Thread_body::deleteLater);
    QObject::connect(this, &Thread_management::finished, this, &Thread_management::deleteLater);

    this->exec();
}
