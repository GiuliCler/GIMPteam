#ifndef CRDT_SYMBOL_H
#define CRDT_SYMBOL_H

#include <string>
#include <vector>

class CRDT_Symbol
{
private:
    char carattere;
    std::string id;
    std::vector<int> posizione;

public:
    CRDT_Symbol(char car, int clientID, int num, std::vector<int> vet);
    char getCarattere() const;
    std::string getIDunivoco()const;
    std::vector<int> getPosizione() const;
};

#endif // CRDT_SYMBOL_H
