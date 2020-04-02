#include "thread_management.h"
#include <QMutexLocker>
#include <iostream>

Thread_management::Thread_management(){}

void Thread_management::run(){
    while (!this->isInterruptionRequested()) {
        // do your job here!
    }
}
