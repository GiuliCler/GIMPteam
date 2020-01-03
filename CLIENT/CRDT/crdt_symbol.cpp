#include "crdt_symbol.h"

CRDT_Symbol::CRDT_Symbol(char car, int clientID, int num, std::vector<int> vet): carattere(car), posizione(vet){
    this->id = std::to_string(clientID) + "_" + std::to_string(num);
};

char CRDT_Symbol::getCarattere() const{
    return this->carattere;
}

std::string CRDT_Symbol::getIDunivoco() const{
    return this->id;
}

std::vector<int> CRDT_Symbol::getPosizione() const{
    return this->posizione;
}
