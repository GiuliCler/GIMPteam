#include "crdt_servereditor.h"
#include <QFile>
#include <iostream>
#include <QDebug>

CRDT_ServerEditor::CRDT_ServerEditor(QString percorsoFile, QObject *parent): QObject(parent), percorsoFile(percorsoFile) {
    mutex = new QMutex();
}


CRDT_ServerEditor::~CRDT_ServerEditor(){
    delete mutex;
}


void CRDT_ServerEditor::process(const CRDT_Message& m){

//    std::cout<<"*************************************"<<std::endl;         // DEBUG
//    std::cout<<"PRINT (prima): "<<this->print()<<std::endl;                // DEBUG
//    std::cout<<"*************************************"<<std::endl;         // DEBUG

    std::string azione = m.getAzione();
    CRDT_Symbol simbolo = m.getSimbolo();
    mutex->lock();
    QVector<CRDT_Symbol>::iterator it = _symbols.begin();

    if(azione == "insert"){                 /* SIMBOLO INSERITO */

        int count = 0;

        if(!_symbols.empty()){
            QVector<int> posNew = m.getSimbolo().getPosizione();
            it = trovaPosizione(posNew);
            for(QVector<CRDT_Symbol>::iterator iterat=_symbols.begin(); iterat<it; iterat++)
                count++;
        }

        _symbols.insert(it, simbolo);

    } else if(azione == "delete"){           /* SIMBOLO CANCELLATO */
//        std::cout<<"(dispatch nell'ed "<<_siteId<<"): elimino un carattere di id "<<simbolo.getIDunivoco()<<std::endl;     // DEBUG ------
        for(; it < _symbols.end(); it++){
            CRDT_Symbol s = *it;
//            std::cout<<s.getCarattere()<<" "<<s.getIDunivoco()<<std::endl;      // DEBUG
            if((s.getPosizione()==simbolo.getPosizione()) && (s.getIDunivoco()==simbolo.getIDunivoco())) {
                _symbols.erase(it);
                break;
            }
        }
    }

    mutex->unlock();

//    std::cout<<"*************************************"<<std::endl;         // DEBUG
//    std::cout<<"PRINT (dopo): "<<this->print()<<std::endl;                 // DEBUG
//    std::cout<<"*************************************"<<std::endl;         // DEBUG
}


QVector<CRDT_Symbol>::iterator CRDT_ServerEditor::trovaPosizione(QVector<int> pos) {
    QVector<int> currentPos;
    int esito = 0;
    QVector<CRDT_Symbol>::iterator it;

    for(it = _symbols.begin(); it < _symbols.end(); it++){
        currentPos = (*it).getPosizione();
        esito = confrontaPos(pos, currentPos);
        if(esito)
            break;
    }

    if(!esito)
        it = _symbols.end();

    return it;
}


/*
 * ESITO = 1 --> currentPos > pos ==> posso inserire il nuovo elemento qui
 * ESITO = 0 --> currentPos < pos ==> devo continuare la ricerca guardando il prossimo elemento
*/
int CRDT_ServerEditor::confrontaPos(QVector<int> pos, QVector<int> currentPos){
    for(int index=0; index<pos.size(); index++){
        if(currentPos.size()>index){
            if(currentPos[index] == pos[index]) {
                continue;
            } else if(currentPos[index] > pos[index]){
                return 1;
            } else {
                return 0;
            }
        } else {
            /* Caso: pos ha più elementi di currentPos => pos sta sicuramente dopo currentPos */
            return 0;
        }
    }
    return 0;
}


void CRDT_ServerEditor::saveInFilesystem(){
//    qDebug()<<"**** Sono entrato nella saveInFilesystem...";           // DEBUG
    QFile file(percorsoFile);
    if (file.open(QIODevice::WriteOnly)){
//        qDebug()<<"**** Sono riuscito ad aprire il file...";           // DEBUG
        mutex->lock();
        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_5_12);

//        for(auto i=_symbols.begin(); i<_symbols.end(); i++)                                          // DEBUG
//           std::cout<<"saveInFilesystem --"<<(*i).getCarattere().toLatin1()<<std::endl;              // DEBUG

        out << this->_symbols;
        file.close();
        mutex->unlock();
    }
}


void CRDT_ServerEditor::loadFromFilesystem(){
//    qDebug()<<"**** Sono entrato nella loadFromFilesystem...";           // DEBUG
    QFile file(percorsoFile);
    if (file.open(QIODevice::ReadWrite)){
        mutex->lock();
        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_5_12);
        this->_symbols.clear();     // Svuoto il vettore di _symbols per sicurezza (Nota: non dovrebbe servire *in teoria*)
        in >> this->_symbols;
//        for(auto i=_symbols.begin(); i<_symbols.end(); i++)                                          // DEBUG
//           std::cout<<"**** loadFromFilesystem --"<<(*i).getCarattere().toLatin1()<<std::endl;              // DEBUG
        file.close();
        mutex->unlock();
    }
}


// Nota: i mutex in questa funzione sono stati cancellati e messi fuori dalla chiamata alla funzione
QByteArray CRDT_ServerEditor::retrieveCurrentCrdt(){
    QByteArray a;
    QDataStream data(&a, QIODevice::WriteOnly);
//    mutex->lock();
    data << _symbols;
//    mutex->unlock();
    return a;
}
