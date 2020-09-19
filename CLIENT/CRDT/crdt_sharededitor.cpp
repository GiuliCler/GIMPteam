#include "crdt_sharededitor.h"
#include "crdt_symbol.h"
#include "crdt_message.h"
#include "crdt_controller.h"
#include "GUI/connection/gui_connectionToServerWrapper.h"
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
        int assolutoDX = abs((*DX));
        int assolutoSX = abs((*SX));
        if(assolutoDX > assolutoSX)
            delta = assolutoDX - assolutoSX;
        else
            delta = assolutoSX - assolutoDX;
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
    connection->requestSendMessage(messaggio);
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
    connection->requestSendMessage(messaggio);
}


void CRDT_SharedEditor::process(const CRDT_Message& m){

        std::string azione = m.getAzione();
        CRDT_Symbol simbolo = m.getSimbolo();
        QVector<CRDT_Symbol>::iterator it = _symbols.begin();

        if(azione == "insert"){                 /* SIMBOLO INSERITO */

            int count = 0;

            if(!_symbols.empty()){
                QVector<int> posNew = m.getSimbolo().getPosizione();
                it = trovaPosizione(posNew);
//                for(QVector<CRDT_Symbol>::iterator iterat=_symbols.begin(); iterat<it; iterat++)
//                    count++;
                count = it - _symbols.begin();
            }

            _symbols.insert(it, simbolo);

            parent->remoteInsert(count, simbolo.getCarattere(), simbolo.getFormat(), simbolo.getAlignment());

        } else if(azione == "delete"){           /* SIMBOLO CANCELLATO */
//            std::cout<<"(dispatch nell'ed "<<_siteId<<"): elimino un carattere di id "<<simbolo.getIDunivoco()<<std::endl;     // DEBUG
            for(; it < _symbols.end(); it++){
                CRDT_Symbol s = *it;
                if((s.getPosizione()==simbolo.getPosizione()) && (s.getIDunivoco()==simbolo.getIDunivoco())) {
                    _symbols.erase(it);
                    parent->remoteDelete(it - _symbols.begin());
                    break;
                }
            }
        }
}


QVector<CRDT_Symbol>::iterator CRDT_SharedEditor::trovaPosizione(QVector<int> target) {
    int esito = 0;
    QVector<CRDT_Symbol>::iterator it = _symbols.begin();

    // Controllo inserimento in coda
    if(confrontaPos(target, _symbols[_symbols.size()-1].getPosizione()) == 1)
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

