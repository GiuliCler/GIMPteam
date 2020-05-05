#include "testint.h"
#include <iostream>
#include <sstream>
#include <QThread>

TestInt::TestInt(QObject *parent) : QObject(parent)
{

}

void TestInt::print(){
    auto thread_id = std::this_thread::get_id();
//    std::stringstream ss;
//    ss << thread_id;
//    std::string thread_id_string = ss.str();

//    std::cout << "---- THREAD TestInt id: "<<thread_id<<" ---- "<< std::endl;      // DEBUG
    std::cout << "TestInt: " << this->n << "; THREAD_ID: " << thread_id <<std::endl;
}
