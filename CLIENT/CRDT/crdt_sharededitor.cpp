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
        QObject::connect(connection, &connection_to_server::sigProcessMessage, this, &CRDT_SharedEditor::process);
}

int CRDT_SharedEditor::getSiteId() const{
    return this->_siteId;
}

void CRDT_SharedEditor::localInsert(int index, QChar value, QTextCharFormat fmt, Qt::Alignment align){
    QVector<int> posizione, posPREV, posNEXT;

    std::cout << "Adding " << value.toLatin1() << " to CRDT in pos " << index << std::endl; // DEBUG

    if(index<0 || index>_symbols.size())
        throw std::exception();     //TODO eccezioniiii

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
            //printf("Index-1: %d\n", index-1);       // DEBUG ------
            //printf("Index: %d\n", index);           // DEBUG ------
            posizione = generaPosizione(posPREV, posNEXT);
        }
    }

    posizione.push_back(_siteId);
    //printf("%d\n", _siteId);       // DEBUG ------

    /* Creazione del nuovo simbolo e inserimento nella corretta posizione all'interno del vettore _symbols */
    auto simbolo = new CRDT_Symbol(value, this->_siteId, this->_counter++, posizione, fmt, align);
    auto it = _symbols.begin()+index;
    _symbols.insert(it, *simbolo);

    /* Creazione del messaggio e invio al NetworkServer */
    CRDT_Message* messaggio = new CRDT_Message("insert", *simbolo, this->_siteId);
//    _server.send(*messaggio);     --> chiamata alla funzione send di connection_to_server
    connection->requestSendMessage(messaggio);

//    std::cout<<"*************************************"<<std::endl;                       // DEBUG -------
//    std::cout<<"PRINT (localInsert): "<<this->print()<<std::endl;                        // DEBUG -------
//    std::cout<<"*************************************"<<std::endl;                       // DEBUG -------
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

    //printf("Pos: ");     // DEBUG ------

    while((*SX)==(*DX)&&(SX<prev.end())){
        pos.push_back((*SX));
        //printf("%d ", (*SX));       // DEBUG ------
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
            //printf("%d ", (*SX)+1);       // DEBUG ------
            SX++;
        } else if (delta == 1){
            pos.push_back((*SX));
            //printf("%d ", (*SX));       // DEBUG ------
            SX++;
            if(SX!=prev.end()){       /* esiste ancora una cifra nel vettore prev */
                pos.push_back((*SX) + 1);
                //printf("%d ", (*SX)+1);       // DEBUG ------
                SX++;
            }else{                    /* il vettore prev è finito */
                pos.push_back(0);
                //printf("0 ");       // DEBUG ------
            }
        }
    }
    else if(SX==prev.end()){         /* CASO DI USCITA DAL WHILE: prev finito */
        pos.push_back((*DX)-1);
        //printf("%d ", (*DX)-1);       // DEBUG ------
    }

    return pos;
}

void CRDT_SharedEditor::localErase(int index){
    /* Recupero dal vettore di simboli il simbolo da eliminare */
    CRDT_Symbol simbolo = _symbols[index];

    std::cout<< "Ho pescato... "<< simbolo.getCarattere().toLatin1() <<" -- "<<simbolo.getIDunivoco()<<std::endl;            // DEBUG ----

    /* Elimino il simbolo */
    auto it = _symbols.begin()+index;
    _symbols.erase(it);

    //std::cout<< "Sto creando un messaggio per eliminare... "<<simbolo.getCarattere()<<" -- "<<simbolo.getIDunivoco()<<std::endl;            // DEBUG ----

    /* Creazione del messaggio e invio al NetworkServer */
    CRDT_Message* messaggio = new CRDT_Message("delete", simbolo, this->_siteId);
//    _server.send(*messaggio);
    connection->requestSendMessage(messaggio);
}

void CRDT_SharedEditor::process(const CRDT_Message& m){

//        std::cout<<"*************************************"<<std::endl;         // DEBUG -------
//        std::cout<<"PRINT (prima): "<<this->print()<<std::endl;                        // DEBUG -------
//        std::cout<<"*************************************"<<std::endl;         // DEBUG -------

        std::string azione = m.getAzione();
        CRDT_Symbol simbolo = m.getSimbolo();
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

//            qDebug()<<"AAAAAAA "<<count;        // DEBUG ----------

            parent->remoteInsert(count, simbolo.getCarattere(), simbolo.getFormat(), simbolo.getAlignment());

        } else if(azione == "delete"){           /* SIMBOLO CANCELLATO */
            std::cout<<"(dispatch nell'ed "<<_siteId<<"): elimino un carattere di id "<<simbolo.getIDunivoco()<<std::endl;     // DEBUG ------
            for(; it < _symbols.end(); it++){
                CRDT_Symbol s = *it;
                //std::cout<<s.getCarattere()<<" "<<s.getIDunivoco()<<std::endl;      // DEBUG -------------
                if((s.getPosizione()==simbolo.getPosizione()) && (s.getIDunivoco()==simbolo.getIDunivoco())) {
                    _symbols.erase(it);
                    parent->remoteDelete(it - _symbols.begin());
                    break;
                }
            }
        }

//        std::cout<<"*************************************"<<std::endl;         // DEBUG -------
//        std::cout<<"PRINT (dopo): "<<this->print()<<std::endl;                        // DEBUG -------
//        std::cout<<"*************************************"<<std::endl;         // DEBUG -------
}

QVector<CRDT_Symbol>::iterator CRDT_SharedEditor::trovaPosizione(QVector<int> pos) {
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

std::string CRDT_SharedEditor::to_string() {
    std::string documento = "";
    for(auto i=_symbols.begin(); i<_symbols.end(); i++)
        documento += (*i).getCarattere().toLatin1();
    return documento;
}

/* funzione per debug - mostra l'elenco dei caratteri e le rispettive posizioni*/
std::string CRDT_SharedEditor::print(){
    std::string posizioni = "\nSiteId del mio editor: " + std::to_string(_siteId) + "\n";
    for(const CRDT_Symbol &s: _symbols){
        posizioni += s.getCarattere().toLatin1();
        posizioni += " -- IDunivoco (siteID_siteCOUNTER): " + s.getIDunivoco();
        posizioni += " -- [ ";
        QVector<int> vet = s.getPosizione();
        for(int num: vet){
            posizioni += std::to_string(num) + " ";
        }
        posizioni += "]\n";
    }

    return posizioni;
}
