#include "server.h"
#include "thread_management.h"
#include "crdt/crdt_message.h"
#include <stdlib.h>
#include <QThreadPool>
#include <QRunnable>
#include <QFileSystemModel>
#include <QTreeView>
#include <QMutex>
#include <QPair>
#include <QWaitCondition>
#include <queue>

//Thread_management* thread_mgm;

//QVector<QPair<QString, int>> jobs;
//QWaitCondition* cv_jobs = new QWaitCondition();
//QMutex* mutex_jobs = new QMutex();

QMutex* mutex_users = new QMutex();
QMutex* mutex_docs = new QMutex();
QMutex* mutex_workingUsers = new QMutex();
QMutex* mutex_db = new QMutex();

QMap<QString, int> users;
QMap<QString, int> documents;

//TODO: valutare il path, al momento quello di Giulia
QString path = "C:/Users/giuli/Desktop/PROGETTO MALNATI/GIMPteam/Server/Files/";

// QMap formata da coppie (docId, [userId1, userId2, userId3, ...])
// NOTA: workingUsers può contenere righe di documenti CON ALMENO UNO USER ONLINE E ATTIVO
//       --> se la riga contiente solo più un utente e tale utente si discollega/non lavora più a tale documento, la riga viene cancellata
//       --> tale riga verrà ricreata non appena un altro utente (o anche lo stesso) si ricollegherà/aprirà di nuovo tale documento
QMap<int, QVector<int>> workingUsers;

// Coda formata da coppie (messaggio, contatore)
std::queue<QPair<CRDT_Message, int>> codaMessaggi;

Server::Server(QObject *parent): QTcpServer(parent), socketDescriptor(socketDescriptor) {

    qDebug()<< "Dentro al costruttore di Server";           // DEBUG

    // Connessione al DB
    database = new CollegamentoDB();
    mutex_db->lock();
    database->connettiDB("gimpdocs_db", "connServer");
    mutex_db->unlock();

    // Riempimento della QMap degli utenti con gli elementi presenti sul DB
    int cont = 0;
    mutex_db->lock();
    std::vector<QString> utenti = database->recuperaUtentiNelDB();
    mutex_db->unlock();
    mutex_users->lock();
    for(auto i=utenti.begin(); i<utenti.end(); i++){
        if((*i) == "nessuno"){
            break;
        }
        users.insert(QString::fromStdString((*i).toStdString()), cont++);
    }
    mutex_users->unlock();

    // Riempimento della QMap dei documenti con gli elementi presenti sul DB
    cont = 0;
    mutex_db->lock();
    std::vector<QString> documenti = database->recuperaDocsNelDB();
    mutex_db->unlock();
    mutex_docs->lock();
    for(auto i=documenti.begin(); i<documenti.end(); i++){
        if((*i) == "nessuno"){
            break;
        }
        documents.insert(QString::fromStdString((*i).toStdString()), cont++);
    }
    mutex_docs->unlock();

//    // Creo thread_management
//    thread_mgm = new Thread_management();
//    connect(thread_mgm, SIGNAL(finished()), thread_mgm, SLOT(deleteLater()));

//    // Faccio partire thread_management (mod. detach)
//    thread_mgm->start();

//    CODICE DI PROVA - PRODUTTORE
//    mutex_jobs->lock();
//    qDebug()<<"SERVER - Prima della prepend: "<<jobs.first();
//    jobs.prepend(2);
//    qDebug()<<"SERVER - Dopo la prepend: "<<jobs.first();
//    mutex_jobs->unlock();
//    std::this_thread::sleep_for(std::chrono::seconds(3));
//    cv_jobs->wakeAll();     // non fa un tubo

    qDebug()<<"Fine costruttore di Server";          // DEBUG

}

Server::~Server(){

    qDebug()<<"Dentro al distruttore di Server";         // DEBUG

    // Sveglio il thread_management addormentato nella wait
//     cv_jobs->wakeAll();

    // Distruggo thread_management
//    NOTA: faccio magari un vettore in cui mantengo tutti i puntatori ai thread
//    if (thread_mgm != nullptr && thread_mgm->isRunning()) {
//        thread_mgm->requestInterruption();
//        thread_mgm->wait();
//    }

    qDebug()<<"Fine distruttore di Server";         // DEBUG

}

void Server::incomingConnection(qintptr socketDescriptor) {
    /*
     * This method will get called every time a client tries to connect ("when a new connection is available" cit.)
     * @param socketDescriptor: it's the native socket descriptor for the accepted connection
     * We create an object that will take care of the communication with this client
    */

    qDebug()<< "SERVER - Sono nella incomingConnection";       // DEBUG
    std::cout << "---- SERVER incomingConnection id: " << std::this_thread::get_id() << " ---- " << std::endl;       // DEBUG

    // Creo thread_management
    Thread_management* thread_mgm = new Thread_management(socketDescriptor, this);
    connect(thread_mgm, SIGNAL(finished()), thread_mgm, SLOT(deleteLater()));

    // Faccio partire thread_management (mod. detach)
    thread_mgm->start();

//    socket = new QTcpSocket(this);
//    if (!socket->setSocketDescriptor(socketDescriptor)) {
//        emit error(socket->error());
//        return;
//    }

    qDebug()<< "SERVER - Fine incomingConnection";      // DEBUG
}

void Server::runServer() {
    qDebug()<< "SERVER - Sono nella runServer";      // DEBUG
}

void Server::testRicezione(){
    std::cout << "Si può fare!" << std::endl;
}
