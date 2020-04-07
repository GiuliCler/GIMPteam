#include "thread_management.h"
#include <QMutexLocker>
#include <iostream>

Thread_management::Thread_management(){}

void Thread_management::run(){
    while (!this->isInterruptionRequested()) {

//    CODICE DI PROVA - CONSUMATORE
//        std::cout<<"THREAD - Prima della wait"<<std::endl;
//        mutex_jobs->lock();
//        cv_jobs->wait(mutex_jobs);
//        std::cout<<"THREAD - Leggo con la first: "<<jobs.first()<<std::endl;
//        mutex_jobs->unlock();




    }

//    std::cout<<"Fine thread"<<std::endl;

}
