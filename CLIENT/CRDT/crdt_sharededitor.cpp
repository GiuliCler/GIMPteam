#include "crdt_sharededitor.h"
#include "crdt_symbol.h"
#include "crdt_message.h"
#include "crdt_controller.h"
#include "GUI/connection/gui_reconnection.h"

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

CRDT_SharedEditor::CRDT_SharedEditor(CRDT_controller *parent, connection_to_server *connection, int siteId, int siteCounter): parent(parent), connection(connection), _siteId(siteId), _counter(siteCounter){

        // Recupero il file da caricare nell'editor
        int pos = 0;
        QByteArray file = connection->getFileTMP();
        QDataStream data(&file, QIODevice::ReadOnly);
        data >> _symbols;

        // Aggiorno lo shared editor
        for(auto it = _symbols.begin();it<_symbols.end();it++, pos++) {
            parent->remoteInsert(pos, it->getCarattere(), it->getFormat(), it->getAlignment());
        }

        QObject::connect(connection, &connection_to_server::sigProcessMessage, this, &CRDT_SharedEditor::process, Qt::QueuedConnection);
}


int CRDT_SharedEditor::getSiteId() const{
    return this->_siteId;
}

int CRDT_SharedEditor::getSiteIdAt(int pos){
    return _symbols[pos].getSiteId();
}

QVector<int> CRDT_SharedEditor::generaPrimaPosizione(int index){

    // Generazione della posizione (senza siteId) del primo elemento da inserire

    QVector<int> posizione, posPREV, posNEXT;

    if(index<0)
        index = 0;
    if(index>_symbols.size())
        index = _symbols.size();

    if(_symbols.empty()){           /* VETTORE DI SIMBOLI ANCORA VUOTO */
        posizione.push_back(0);
    }
    else if (_symbols.size() == index) {        /* INSERIMENTO IN CODA */
        int dim = _symbols.at(_symbols.size()-1).getPosizione()[0] + 1;
        posizione.push_back(dim);
    }
    else{                               /* VETTORE DI SIMBOLI GIA' CON SIMBOLI */
        if(index == 0){                 /* INSERIMENTO IN TESTA */
            int dim = _symbols.at(index).getPosizione()[0] - 1;
            posizione.push_back(dim);
        } else {                        /* INSERIMENTO ALL'INTERNO DEL VETTORE */
            posPREV = _symbols[index - 1].getPosizione();
            posNEXT = _symbols[index].getPosizione();
            posizione = generaPosizione(posPREV, posNEXT);
        }
    }

    // Aggiungo al fondo del vettore di interi il siteId
    posizione.push_back(_siteId);

    return posizione;
}


QVector<int> CRDT_SharedEditor::generaPosizione(QVector<int> prev, QVector<int> next){
    QVector<int> pos;
    int delta;
    auto SX = prev.begin();
    auto DX = next.begin();

    /*  delta > 1 ==> mi fermo e metto come cifra SX+1
     *  delta == 1 ==> scrivo SX, guardo la cifra successiva di SX
     *                 (se esiste) e la metto in pos (incrementata)
     *                (se non esiste) metto come 0 cifra successiva in pos
     *  delta == 0 ==> confronto quelli sopra finche...
     *              - trovo SX < DX ... confronto il loro delta eheh
     *              - finisce il SX ... guardo la cifra successiva di DX e la metto in pos (decrementata)
     */

    while((*SX)==(*DX)&&(SX<prev.end())){
        pos.push_back((*SX));
        SX++;
        DX++;
    }

    if((*SX)<(*DX)){                  /* CASO DI USCITA DAL WHILE: (*i)<(*j) */
        delta = *DX - *SX;
        if(delta > 1){
            pos.push_back((*SX) + 1);
            SX++;
        } else if (delta == 1){
            pos.push_back((*SX));
            SX++;
            if(SX!=prev.end()){       /* esiste ancora una cifra nel vettore prev */
                pos.push_back((*SX) + 1);
                SX++;
            }else{                    /* il vettore prev è finito */
                pos.push_back(0);
            }
        }
    }
    else if(SX==prev.end()){         /* CASO DI USCITA DAL WHILE: prev finito */
        pos.push_back((*DX)-1);
    }

    return pos;
}


void CRDT_SharedEditor::localInsert(int index, QChar value, QTextCharFormat fmt, Qt::Alignment align, QVector<int> posizione){

//    std::cout << "localInsert - Adding " << value.toLatin1() << " to CRDT in pos " << index << std::endl;      // DEBUG

    /* Creazione del nuovo simbolo e inserimento nella corretta posizione all'interno del vettore _symbols */
    CRDT_Symbol simbolo{value, this->_siteId, this->_counter++, posizione, fmt, align};
    auto it = _symbols.begin()+index;
    _symbols.insert(it, simbolo);

    /* Creazione del messaggio e invio al NetworkServer */
    CRDT_Message messaggio{"insert", simbolo, this->_siteId};
    try {
        connection->requestSendMessage(messaggio);
    } catch (GUI_ConnectionException &exception){
        GUI_Reconnection::GUI_ReconnectionWrapper(parent->getGimpDocs());
        parent->getGimpDocs()->returnToLogin();
    }

}


void CRDT_SharedEditor::localErase(int index){
    /* Recupero dal vettore di simboli il simbolo da eliminare */
    CRDT_Symbol simbolo = _symbols[index];

//    std::cout<< "localErase - Deleting "<< simbolo.getCarattere().toLatin1() <<" -- "<<simbolo.getIDunivoco()<<std::endl;        // DEBUG

    /* Elimino il simbolo */
    auto it = _symbols.begin()+index;
    _symbols.erase(it);

    /* Creazione del messaggio e invio al NetworkServer */
    CRDT_Message messaggio{"delete", simbolo, this->_siteId};
    try {
        connection->requestSendMessage(messaggio);
    } catch (GUI_ConnectionException &exception){
        GUI_Reconnection::GUI_ReconnectionWrapper(parent->getGimpDocs());
        parent->getGimpDocs()->returnToLogin();
    }

}


void CRDT_SharedEditor::process(const CRDT_Message& m){
    int userId = m.getCreatore();

    if(!parent->userBuffers.contains(userId)){
        std::cout << "Discarding message from unknown user " << userId << std::endl;
        return;
    }

    if(parent->userBuffers[userId].empty()){
        std::cout << "Adding in empty buffer of user " << userId << std::endl;
        parent->userBuffers[userId].append(m);
        return;
    }

    std::string azione = m.getAzione();
    CRDT_Symbol simbolo = m.getSimbolo();
    CRDT_Message head = parent->userBuffers[userId][0];

    if(azione != head.getAzione()){
        std::cout << "Changing op type in buffer of user " << userId << std::endl;
        processBuffer(userId);
        parent->userBuffers[userId].append(m);
        return;
    }

    if(azione == "insert" &&
            (simbolo.getFormat() != head.getSimbolo().getFormat() || simbolo.getAlignment() != head.getSimbolo().getAlignment()
            || parent->userBuffers[userId].size() > 2000)){
            processBuffer(userId);
    }
    parent->userBuffers[userId].append(m);
}


void CRDT_SharedEditor::processBuffer(int userId){

    while(!parent->userBuffers.value(userId).empty()){

        CRDT_Message m = parent->userBuffers.value(userId)[0];
        std::string azione = m.getAzione();
        CRDT_Symbol simbolo = m.getSimbolo();

        QVector<CRDT_Symbol>::iterator it = _symbols.begin();
        //        std::cout<<"Sono nella process per una... "<<azione<<std::endl;        // DEBUG

        if(azione == "insert"){                 // SIMBOLO INSERITO

            int count = 0;

            if(!_symbols.empty()){

                // Implementazione simil-TLB:
                // confronto posNew con posCursSX (pos-1) e posCursDX (pos)
                // se pos-1 < 0, sono in testa
                // se pos = end, sono in coda
                // se pos è in mezzo a posCursSX e posCursDX --> inserisco
                // altrimenti, ricerca dicotomica (trovaPosizione originale)

                QVector<int> posNew = simbolo.getPosizione();
                bool inserimTesta = false, inserimCoda = false;
                QVector<int> posCursoreDX, posCursoreSX;
                int esitoDX, esitoSX;
                int user = m.getCreatore();                                       // Recupero dal messaggio lo userId di chi sta scrivendo
                int indexCursore = parent->usersCursors.value(user);              // Recupero il cursore di tale user

                if(indexCursore > _symbols.size())
                    indexCursore = _symbols.size();

                if(indexCursore == 0)                    // Controllo se il cursore dello user è in testa al documento
                    inserimTesta = true;

                if(indexCursore >= _symbols.size()){      // Controllo se il cursore dello user è in coda al documento
                    inserimCoda = true;
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

            //check whether the symbol is already present in the CRDT
            if(it != _symbols.begin() && (it-1)->getIDunivoco() == simbolo.getIDunivoco()){
                parent->userBuffers[userId].removeFirst();
                parent->usersCursors[m.getCreatore()] = count;
                continue;
            }

            auto it2 = parent->userBuffers[userId].rbegin();
            QString s;
            QTextCharFormat fmt = simbolo.getFormat();
            Qt::Alignment align = simbolo.getAlignment();

            while(it2 != parent->userBuffers[userId].rend()){
    //            std::cout<<"Sto INSERENDO all'indice: "<<count<<"; simbolo: "<<simbolo.getCarattere().toLatin1()<<std::endl;          // DEBUG
                _symbols.insert(count, it2->getSimbolo());
                s.push_front(it2->getSimbolo().getCarattere());
                it2++;
            }

            parent->remoteInsert(count, s, fmt, align);

            // Aggiorno il cursore dell'utente che ha scritto
            parent->usersCursors[m.getCreatore()] = count + s.length();
    //            std::cout<<"(insert) Sto mettendo il cursore all'indice: "<<parent->usersCursors[m.getCreatore()]<<std::endl;          // DEBUG

            parent->userBuffers[userId].clear();

        } else if(azione == "delete"){           // SIMBOLO CANCELLATO
            if(_symbols.empty()){
                parent->userBuffers[userId].clear();
                return;
            }

            QVector<int> posNew = simbolo.getPosizione();

            // Implementazione simil-TLB:
            // confronto posNew con posCursDX
            // se il simbolo è proprio in posCursDX --> cancella
            // altrimenti, ricerca dicotomica (trovaPosizione originale)

            bool cursoreInTesta = false, cursoreInCoda = false;
            QVector<int> posCursoreDX, posCursoreSX;
            int user = m.getCreatore();                                       // Recupero dal messaggio lo userId di chi sta scrivendo
            int indexCursore = parent->usersCursors.value(user);              // Recupero il cursore di tale user

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

            int pos = it - _symbols.begin();

            if(it == _symbols.end()){
                parent->userBuffers[userId].removeFirst();
                parent->usersCursors[m.getCreatore()] = pos;
            } else{
                int count = 0;
                auto it2 = parent->userBuffers[userId].begin();

                while(it2 != parent->userBuffers[userId].end() && it >= _symbols.begin()
                      && it->getIDunivoco() == it2->getSimbolo().getIDunivoco()){
                    count++;
                    it--;
                    it2++;
                }
                if(count > 0){
                    _symbols.erase(it+1, it+count+1);
                    parent->userBuffers[userId].erase(parent->userBuffers[userId].begin(), it2);
                    parent->remoteDelete(pos-count+1, count);
                    //  std::cout<<"(delete) Sto mettendo il cursore all'indice: "<<parent->usersCursors[m.getCreatore()]<<std::endl;          // DEBUG
                    // Aggiorno il cursore dell'utente che ha cancellato
                    parent->usersCursors[m.getCreatore()] = pos - count + 1;
                } else{
                    parent->userBuffers[userId].removeFirst();
                    parent->usersCursors[m.getCreatore()] = pos;
                }
            }
            if(!parent->userBuffers[userId].empty())
                continue;
        }

    }
}



QVector<CRDT_Symbol>::iterator CRDT_SharedEditor::trovaPosizione(QVector<int> target) {
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
int CRDT_SharedEditor::confrontaPos(QVector<int> pos, QVector<int> currentPos){
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


int  CRDT_SharedEditor::getLength(){
    return _symbols.size();
}


//std::string CRDT_SharedEditor::to_string() {
//    std::string documento = "";
//    for(auto i=_symbols.begin(); i<_symbols.end(); i++)
//        documento += (*i).getCarattere().toLatin1();
//    return documento;
//}

/* funzione per debug - mostra l'elenco dei caratteri e le rispettive posizioni*/
//std::string CRDT_SharedEditor::print(){
//    std::string posizioni = "\nSiteId del mio editor: " + std::to_string(_siteId) + "\n";
//    for(const CRDT_Symbol &s: _symbols){
//        posizioni += s.getCarattere().toLatin1();
//        posizioni += " -- IDunivoco (siteID_siteCOUNTER): " + s.getIDunivoco();
//        posizioni += " -- [ ";
//        QVector<int> vet = s.getPosizione();
//        for(int num: vet){
//            posizioni += std::to_string(num) + " ";
//        }
//        posizioni += "]\n";
//    }

//    return posizioni;
//}


Qt::Alignment CRDT_SharedEditor::getAlignAt(int pos){
    return _symbols[pos].getAlignment();
}

