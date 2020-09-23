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

    std::string azione = m.getAzione();
    CRDT_Symbol simbolo = m.getSimbolo();

    mutex->lock();

    QVector<CRDT_Symbol>::iterator it = _symbols.begin();

    if(azione == "insert"){                 /* SIMBOLO INSERITO */
        if(!_symbols.empty()){
            QVector<int> posNew = m.getSimbolo().getPosizione();
            it = trovaPosizione(posNew);
        }

        _symbols.insert(it, simbolo);

    } else if(azione == "delete"){           /* SIMBOLO CANCELLATO */

        // Ricerca dicotomica
        QVector<CRDT_Symbol>::iterator it =
                std::lower_bound(_symbols.begin(), _symbols.end(), simbolo,
                [this](CRDT_Symbol s1, CRDT_Symbol s2) {return confrontaPos(s1.getPosizione(), s2.getPosizione());});

        if(it < _symbols.end() && it->getIDunivoco() == simbolo.getIDunivoco()){
            _symbols.erase(it);
        }

//        for(; it < _symbols.end(); it++){
//            CRDT_Symbol s = *it;
//            if((s.getPosizione()==simbolo.getPosizione()) && (s.getIDunivoco()==simbolo.getIDunivoco())) {
//                _symbols.erase(it);
//                break;
//            }
//        }
    }

    mutex->unlock();
}


QVector<CRDT_Symbol>::iterator CRDT_ServerEditor::trovaPosizione(QVector<int> target) {
    int esito = 0;
    QVector<CRDT_Symbol>::iterator it = _symbols.begin();

    // Controllo inserimento in coda
    if(confrontaPos(target, _symbols[_symbols.size()-1].getPosizione()) == 0)
        return _symbols.end();

    int sx = 0, dx = _symbols.size()-1, centro = (sx + dx) / 2;

    while(dx - sx > 1){
        esito = confrontaPos(target, _symbols[centro].getPosizione());
        if(esito == 1){
            // currentPos > target
            dx = centro;
        } else {
            // currentPos < target
            sx = centro;
        }

        centro = (sx + dx) / 2;
    }

    esito = confrontaPos(target, _symbols[centro].getPosizione());
    if(esito == 1){
        // currentPos > target
        it = it + centro;
    } else {
        // currentPos < target
        it = it + centro + 1;
    }

//    for(it = _symbols.begin; it < _symbols.end; it++){
//        currentPos = (*it).getPosizione();
//        esito = confrontaPos(pos, currentPos);
//        if(esito)
//            break;
//    }

//    if(!esito)
//        it = _symbols.end();

    return it;
}


/*
 * ESITO = 1 --> currentPos > target/pos
 * ESITO = 0 --> currentPos < target/pos
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
    QFile file(percorsoFile);
    if (file.open(QIODevice::WriteOnly)){
        mutex->lock();
        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_5_12);
        out << this->_symbols;
        file.close();
        mutex->unlock();
    }
}


void CRDT_ServerEditor::loadFromFilesystem(){
    QFile file(percorsoFile);
    if (file.open(QIODevice::ReadWrite)){
        mutex->lock();
        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_5_12);
        this->_symbols.clear();     // Svuoto il vettore di _symbols per sicurezza (Nota: non dovrebbe servire *in teoria*)
        in >> this->_symbols;
        file.close();
        mutex->unlock();
    }
}


QVector<CRDT_Symbol> CRDT_ServerEditor::getSymbols(){
    return _symbols;
}
