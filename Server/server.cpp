#include "server.h"
#include "thread_management.h"
#include "crdt/crdt_message.h"
#include "crdt/crdt_servereditor.h"
#include <stdlib.h>
#include <QThreadPool>
#include <QRunnable>
#include <QFileSystemModel>
#include <QTreeView>
#include <QMutex>
#include <QPair>
#include <queue>

QMutex* mutex_users = new QMutex();
QMutex* mutex_docs = new QMutex();
QMutex* mutex_workingUsers = new QMutex();
QMutex* mutex_db = new QMutex();
QMutex* mutex_logged_users = new QMutex();
QMutex* mutex_files = new QMutex();

QMap<QString, int> users;
QMap<QString, int> documents;
QVector<QString> logged_users;

// workingUsers --> QMap formata da coppie (docId, [userId1, userId2, userId3, ...])
// NOTA: workingUsers può contenere righe di documenti CON ALMENO UNO USER ONLINE E ATTIVO
//       --> se la riga contiente solo più un utente e tale utente si discollega/non lavora più a tale documento, la riga viene cancellata
//       --> tale riga verrà ricreata non appena un altro utente (o anche lo stesso) si ricollegherà/aprirà di nuovo tale documento
QMap<int, QVector<int>> workingUsers;

// files --> QMap formata da coppie (docId, CRDT_ServerEditor*)
QMap<int, CRDT_ServerEditor*> files;

QString path = "Files/";

Server::Server(QObject *parent): QTcpServer(parent) {

    qDebug()<< "Dentro al costruttore di Server";           // DEBUG

    // Connessione al DB
    database = new CollegamentoDB();
    mutex_db->lock();
    database->connettiDB("gimpdocs_db", "connServer");
    mutex_db->unlock();

    // Riempimento della QMap degli utenti con gli elementi presenti sul DB
    mutex_db->lock();
    QVector<QPair<QString, int>> utenti = database->recuperaUtentiNelDB();
    mutex_db->unlock();
    mutex_users->lock();
    for(auto i=utenti.begin(); i<utenti.end(); i++){
        QString username = (*i).first;
        int userId = (*i).second;
        users.insert(username, userId);
    }
    mutex_users->unlock();

    // Riempimento della QMap dei documenti con gli elementi presenti sul DB
    int cont = 1;
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

    // Faccio partire il timer associato al check client connessi/crashati (chiamato ogni 5 minuti)
    startTimer(std::chrono::minutes(5));

    qDebug()<<"Fine costruttore di Server";          // DEBUG

}

void Server::incomingConnection(qintptr socketDescriptor) {
    /*
     * This method will get called every time a client tries to connect ("when a new connection is available" cit.)
     * @param socketDescriptor: it's the native socket descriptor for the accepted connection
     * We create an object that will take care of the communication with this client
    */

    qDebug()<< "SERVER - Sono nella incomingConnection";       // DEBUG
    std::cout << "SERVER incomingConnection id: " << std::this_thread::get_id()<< std::endl;       // DEBUG

    // Creo thread_management
    Thread_management* thread_mgm = new Thread_management(socketDescriptor, this);
    connect(thread_mgm, SIGNAL(finished()), thread_mgm, SLOT(deleteLater()));

    // Faccio partire thread_management (mod. detach)    
    thread_mgm->start();

    qDebug()<< "SERVER - Fine incomingConnection";      // DEBUG
}

void Server::timerEvent(QTimerEvent *event){

    qDebug() << "** checkPeriodicoClientConnessiSlot - Server - Timer ID: "<<event->timerId()<<" **";           // DEBUG

    // Server(thread principale) emette un segnale che arriva a tutti i thread_body di thread_management che son stati creati finora
    // I thread_body eseguono un certo slot associato a tale segnale
    // In tale slot i thread_management si chiedono "il mio socket è ancora nello stato connectedState?"
    // - il socket è ancora in connectedState --> non succede nulla (return)
    // - il socket non è in connectedState --> client crashato, chiudo l'eventuale doc aperto, cancello lo user dai logged_users e faccio suicidare il thread_management
    emit checkPeriodicoClientConnessi();
}
