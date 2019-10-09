# GIMPteam - Documentazione - DATABASE

## Tabelle
- Tabella **doc** (nome_doc*, uri)
- Tabella **utente_doc** (username*, nome_doc*, site_id, site_counter)
- Tabella **utenti** (username*, password, sale, nickname, icona)

## File
- **main.cpp** : file utilizzato unicamente per testare le funzioni di _collegamentoDB.cpp_
- **collegamentoDB.h** : file che contiene le definizioni dei metodi utilizzati per interfacciarsi con il database
- **collegamentoDB.cpp** : file che contiene le implementazioni dei metodi utilizzati per interfacciarsi con il database
- **sha256.h** : file che contiene le definizioni dei metodi e delle costanti utilizzati dall'algoritmo di hashing _sha256_
- **sha256.cpp** : file che contiene l'implementazione dell'algoritmo di hashing _sha256_

## Funzioni importanti
### collegamentoDB.cpp
_private:_
- std::string **creaURI**(std::string nomeDOC);
- void **gen_random**(char *s, const int len);

_public:_
- void **connettiDB**(const QString& dbname, const QString& hostname="localhost", const QString& username="root", const QString& pssw="");
- void **disconnettiDB**();
- std::vector\<std::string\> **login**(std::string username, std::string password);
- int **signup**(std::string username, std::string password, std::string nickname, std::string icona);
- int **creaDoc**(std::string nomeDOC);
- std::string **recuperaURI**(std::string nomeDOC);
- std::string **recuperaDocDatoURI**(std::string uri);
- std::vector\<std::string\> **recuperaDocs**(std::string username);
- std::vector\<std::string\> **recuperaCollaboratori**(std::string nomeDOC);
- std::vector\<int\> **recuperaInfoUtenteDoc**(std::string nomeDOC, std::string username);
- int **aggiungiPartecipante**(std::string nomeDOC, std::string username);
- int **rimuoviPartecipante**(std::string nomeDOC, std::string username);    
- int **aggiornaSiteCounter**(std::string nomeDOC, std::string username, int siteCount);      
- int **aggiornaUser**(std::string username, std::string nuova_password, std::string nuovo_nickname, std::string nuova_icona);
  
### sha256.cpp
_public:_
- std::string **sha256**(std::string input);
