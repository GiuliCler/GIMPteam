#include "crdt_servereditor.h"
#include <QFile>
#include <iostream>
#include <QDebug>
#include <QLinkedList>

CRDT_ServerEditor::CRDT_ServerEditor(QString percorsoFile, QObject *parent): QObject(parent), percorsoFile(percorsoFile) {
    mutex = new QMutex();
}


CRDT_ServerEditor::~CRDT_ServerEditor(){
    delete mutex;
}

void CRDT_ServerEditor::processBuffer(std::shared_ptr<QLinkedList<CRDT_Message>> incomingMessagesBuffer){

    mutex->lock();

    //'sto while serve per quel controllo per cui se la prima lettera da inserire c'è già la poppo dal buffer e ci riprovo colla seconda
    while(!incomingMessagesBuffer->isEmpty()){

        CRDT_Message m = incomingMessagesBuffer->first();
        std::string azione = m.getAzione();
        CRDT_Symbol simbolo = m.getSimbolo();

        QVector<CRDT_Symbol>::iterator it = _symbols.begin();

        if(azione == "insert"){                 // SIMBOLO INSERITO

            if(!_symbols.empty()){

                // Implementazione simil-TLB:
                // confronto posNew con posCursSX (pos-1) e posCursDX (pos)
                // se pos-1 < 0, sono in testa
                // se pos = end, sono in coda
                // se pos è in mezzo a posCursSX e posCursDX --> inserisco
                // altrimenti, ricerca dicotomica (trovaPosizione originale)

                QVector<int> posNew = simbolo.getPosizione();
                int esitoDX, esitoSX;
                int userId = m.getCreatore();                                       // Recupero dal messaggio lo userId di chi sta scrivendo
                int indexCursore = std::min(usersCursors.value(userId), _symbols.size());              // Recupero il cursore di tale user

                if(indexCursore <= 0){
                    //il cursore in TLB era in testa
                    esitoSX = 0;

                    indexCursore = 0;
                } else {
                    QVector<int> posCursoreSX = _symbols[indexCursore-1].getPosizione();       // Recupero posizione immediatamente prima del cursore
                    esitoSX = confrontaPos(posNew, posCursoreSX);
                }

                if(_symbols.size() <= indexCursore){
                    //il cursore in TLB era in coda
                    esitoDX = 1;

                    //nel caso sia maggiore
                    indexCursore = _symbols.size();
                } else {
                    QVector<int> posCursoreDX = _symbols[indexCursore].getPosizione();      // Recupero posizione corrispondente al cursore
                    esitoDX = confrontaPos(posNew, posCursoreDX);
                }

                // Caso in cui posCursoreSX < posNew < posCursoreDX
                if(esitoSX == 0 && esitoDX == 1)
                    it = _symbols.begin() + indexCursore;
                else
                    it = trovaPosizione(posNew);
            }

            int pos = it - _symbols.begin();

            //check whether the symbol is already present in the CRDT
            if(it != _symbols.begin() && (it-1)->getIDunivoco() == simbolo.getIDunivoco()){
                incomingMessagesBuffer->removeFirst();
                usersCursors[m.getCreatore()] = pos;
                continue;
            }

            //alloco spazio inserendo il primo
            _symbols.insert(it, incomingMessagesBuffer->size(), simbolo);
            incomingMessagesBuffer->removeFirst();
            pos++;

            while(!incomingMessagesBuffer->isEmpty()){
                _symbols[pos] = incomingMessagesBuffer->first().getSimbolo();
                incomingMessagesBuffer->removeFirst();
                pos++;
            }

            // Aggiorno il cursore dell'utente che ha scritto
            usersCursors[m.getCreatore()] = pos;

        } else if(azione == "delete"){           // SIMBOLO CANCELLATO

            if(_symbols.empty()){
                incomingMessagesBuffer->clear();
                continue;
            }


            // Implementazione simil-TLB:
            // confronto posNew con posCursDX
            // se il simbolo è proprio in posCursDX --> cancella
            // altrimenti, ricerca dicotomica (trovaPosizione originale)

            //Promemoria: quello che cerchiamo è il primo del buffer, ovvero l'ultimo a destra nella selezione
            QVector<int> posOld = simbolo.getPosizione();
            bool cursoreInTesta = false, cursoreInCoda = false;
            int userId = m.getCreatore();                                       // Recupero dal messaggio lo userId di chi sta scrivendo
            int indexCursore = usersCursors.value(userId);              // Recupero il cursore di tale user

            if(indexCursore <= 0){
                indexCursore = 0;
                cursoreInTesta = true;
            }

            if(_symbols.size() <= indexCursore){      // Controllo se il cursore dello user è in coda al documento
                indexCursore = _symbols.size();
                cursoreInCoda = true;
            }

            if(!cursoreInCoda && posOld == _symbols[indexCursore].getPosizione())               // Per vedere se lo user ha premuto il tasto CANC
                it = _symbols.begin() + indexCursore;
            else if(!cursoreInTesta && posOld == _symbols[indexCursore-1].getPosizione())       // Per vedere se lo user ha premuto il tasto <-
                it = _symbols.begin() + indexCursore-1;
            else
                it = std::lower_bound(_symbols.begin(), _symbols.end(), simbolo,
                    [this](CRDT_Symbol s1, CRDT_Symbol s2) {return confrontaPos(s1.getPosizione(), s2.getPosizione());});


            int pos = it - _symbols.begin();

            if(_symbols.end() <= it || it->getIDunivoco() != simbolo.getIDunivoco()){
                incomingMessagesBuffer->removeFirst();
                usersCursors[m.getCreatore()] = pos;
                continue;
            }


            int count = 0;
            auto it2 = incomingMessagesBuffer->begin();

            while(it2 != incomingMessagesBuffer->end() && it >= _symbols.begin() && it->getIDunivoco() == it2->getSimbolo().getIDunivoco()){
                count++;
                it--;
                it2++;
            }

            _symbols.erase(it + 1, it + 1 + count);
            incomingMessagesBuffer->erase(incomingMessagesBuffer->begin(), it2);

            // Aggiorno il cursore dell'utente che ha cancellato
            usersCursors[m.getCreatore()] = pos + 1 - count;
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

int CRDT_ServerEditor::countBlockingCursors(){
    mutex->lock();
    int n = 0;
    for(bool val : usersMovingCursors)
        if(!val)
            n++;
    mutex->unlock();
    return n;
}
