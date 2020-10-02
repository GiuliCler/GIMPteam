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

        int count = 0;

        if(!_symbols.empty()){
            QVector<int> posNew = simbolo.getPosizione();

            // Implementazione simil-TLB:
            // confronto posNew con posCursSX (pos-1) e posCursDX (pos)
            // se pos-1 < 0, sono in testa
            // se pos = end, sono in coda
            // se pos è in mezzo a posCursSX e posCursDX --> inserisco
            // altrimenti, ricerca dicotomica (trovaPosizione originale)

            bool inserimTesta = false, inserimCoda = false;
            QVector<int> posCursoreDX, posCursoreSX;
            int esitoDX, esitoSX;
            int user = m.getCreatore();                                       // Recupero dal messaggio lo userId di chi sta scrivendo
            int indexCursore = usersCursors.value(user);              // Recupero il cursore di tale user

            if(indexCursore == 0)                    // Controllo se il cursore dello user è in testa al documento
                inserimTesta = true;

            if(indexCursore >= _symbols.size()){      // Controllo se il cursore dello user è in coda al documento
                inserimCoda = true;
                if(indexCursore > _symbols.size())
                    indexCursore = _symbols.size();
            }

            if(!inserimTesta){
                posCursoreSX = _symbols[indexCursore-1].getPosizione();       // Recupero posizione immediatamente prima del cursore
                esitoSX = confrontaPos(posNew, posCursoreSX);
            } else {
                esitoSX = 0;
            }

            if(!inserimCoda){
                posCursoreDX = _symbols[indexCursore].getPosizione();      // Recupero posizione corrispondente al cursore
                esitoDX = confrontaPos(posNew, posCursoreDX);
            } else {
                esitoDX = 1;
            }

            // confrontaPos fornisce... ESITO = 1 --> posCursoreXX > posNew ; ESITO = 0 --> posCursoreXX < posNew
            if(!esitoSX && esitoDX){
                // Caso in cui posCursoreSX < posNew < posCursoreDX
                it = _symbols.begin() + indexCursore;
                count = indexCursore;
            } else {
                it = trovaPosizione(posNew);
                count = it - _symbols.begin();
            }
        }

//        std::cout<<"Sto INSERENDO all'indice: "<<count<<std::endl;          // DEBUG
        _symbols.insert(it, simbolo);

//        Aggiorno il cursore dell'utente che ha scritto
        usersCursors[m.getCreatore()] = count + 1;
//        std::cout<<"(insert) Sto mettendo il cursore all'indice: "<<parent->usersCursors[m.getCreatore()]<<std::endl;          // DEBUG

    } else if(azione == "delete"){           /* SIMBOLO CANCELLATO */

        if(_symbols.isEmpty())
            return;

        QVector<int> posNew = simbolo.getPosizione();

        // Implementazione simil-TLB:
        // confronto posNew con posCursDX
        // se il simbolo è proprio in posCursDX --> cancella
        // altrimenti, ricerca dicotomica (trovaPosizione originale)

        bool cursoreInTesta = false, cursoreInCoda = false;
        QVector<int> posCursoreDX, posCursoreSX;
        int user = m.getCreatore();                                       // Recupero dal messaggio lo userId di chi sta scrivendo
        int indexCursore = usersCursors.value(user);              // Recupero il cursore di tale user

        if(indexCursore > _symbols.size())
            indexCursore = _symbols.size();

        if(indexCursore == 0)                    // Controllo se il cursore dello user è in testa al documento
            cursoreInTesta = true;

        if(indexCursore >= _symbols.size()){      // Controllo se il cursore dello user è in coda al documento
            cursoreInCoda = true;
        }

        if(cursoreInTesta){
            if(posNew == _symbols[indexCursore].getPosizione()){              // Confronto posNew con pos di indexCursore per vedere se lo user ha premuto il tasto CANC
                it = _symbols.begin() + indexCursore;
            } else {
                // Ricerca dicotomica
                it = std::lower_bound(_symbols.begin(), _symbols.end(), simbolo,
                     [this](CRDT_Symbol s1, CRDT_Symbol s2) {return confrontaPos(s1.getPosizione(), s2.getPosizione());});
            }
        } else if(cursoreInCoda){
            if(posNew == _symbols[indexCursore-1].getPosizione()) {           // Confronto posNew con pos di indexCursore-1 per vedere se lo user ha premuto il tasto <-
                it = _symbols.begin() + indexCursore-1;
            } else {
                // Ricerca dicotomica
                it = std::lower_bound(_symbols.begin(), _symbols.end(), simbolo,
                     [this](CRDT_Symbol s1, CRDT_Symbol s2) {return confrontaPos(s1.getPosizione(), s2.getPosizione());});
            }
        } else {
            if(posNew == _symbols[indexCursore-1].getPosizione()) {          // Confronto posNew con pos di indexCursore-1 per vedere se lo user ha premuto il tasto <-
                it = _symbols.begin() + indexCursore-1;
            } else if(posNew == _symbols[indexCursore].getPosizione()){      // Confronto posNew con pos di indexCursore per vedere se lo user ha premuto il tasto CANC
                it = _symbols.begin() + indexCursore;
            } else {
                // Ricerca dicotomica
                it = std::lower_bound(_symbols.begin(), _symbols.end(), simbolo,
                     [this](CRDT_Symbol s1, CRDT_Symbol s2) {return confrontaPos(s1.getPosizione(), s2.getPosizione());});
            }
        }

        // Aggiorno il cursore dell'utente che ha cancellato
        usersCursors[m.getCreatore()] = it - _symbols.begin();
//        std::cout<<"(delete) Sto mettendo il cursore all'indice: "<<parent->usersCursors[m.getCreatore()]<<std::endl;          // DEBUG

        if(it < _symbols.end() && it->getIDunivoco() == simbolo.getIDunivoco()){
//            std::cout<<"Sto CANCELLANDO all'indice: "<<it - _symbols.begin()<<std::endl;          // DEBUG
            _symbols.erase(it);
        }

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

    if(pos.size() < currentPos.size())
        return 1;
    else
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


void CRDT_ServerEditor::addUserToCursorMaps(int userId){
    mutex->lock();
    usersMovingCursors.insert(userId, true);
    usersCursors.insert(userId, 0);
    mutex->unlock();
}

void CRDT_ServerEditor::removeUserFromCursorMaps(int userId){
    mutex->lock();
    usersMovingCursors.remove(userId);
    usersCursors.remove(userId);
    mutex->unlock();
}

void CRDT_ServerEditor::updateCursorMap(int userId, int pos){
    mutex->lock();
    usersCursors[userId] = qMin(pos, _symbols.size());
    mutex->unlock();
}

void CRDT_ServerEditor::updateUsersMovingCursors(int userId, bool v){
    mutex->lock();
    usersMovingCursors[userId] = v;
    mutex->unlock();
}

bool CRDT_ServerEditor::getUserMovingCursor(int userId){
    mutex->lock();
    bool val = usersMovingCursors[userId];
    mutex->unlock();
    return val;
}
