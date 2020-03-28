#include "gimpdocs.h"
#include "connection/gui_server.h"
#include "editorWindow/gui_editor.h"

GIMPdocs::GIMPdocs(QWidget *parent) : QMainWindow(parent), userid(-1)
{
    ui1 = new Ui::GIMPdocs;
    ui2 = new Ui::GUI_EditWindow;

    QFont font("Calisto MT");
    font.setPixelSize(14);
    //font.setStyleHint(QFont::Monospace);
    QApplication::setFont(font);

    regularWindowSize = this->size();
    alreadyMaximized = false;

    setUi1(new GUI_Server(this));
}

GIMPdocs::~GIMPdocs(){
    delete ui1;
    delete ui2;
}

void GIMPdocs::setUi1(QWidget *widget){
    //serve ad annullare showMaximized e lo metto qui perchè se lo metto dopo la set central window mi sballa il corner topLeft della window
    showNormal();

    ui1->setupUi(this);
    this->setCentralWidget(widget);

    //la resize serve in ogni caso perchè anche se torno maximized, se poi tolgo il maximized voglio comunque riavere la vecchia size (che avevo prima di aprire l'editor. Senza la resize, togliendo il maximized, mi metterebbe la size dell'editor non massimizzato
    //la adjustSize, che dovrebbe adeguare la size al contenuto, in realtà serve solo come trucco magico per poter usare la resize. Per qualche strana ragione, senza la adjustSize la resize viene eseguita prima della setCentralWwidget
    adjustSize();
    //questa ripristina le dimensioni precedenti alla showMaximized
    resize(regularWindowSize);

    //se prima di aprire un document era già maximized lo rimetto maximized
    if(alreadyMaximized)
        showMaximized();
}

void GIMPdocs::setUi2(QWidget *widget){

    //serve per quando chiudo il document e voglio ripristinare la vecchia size
    alreadyMaximized = isMaximized();
    if(!alreadyMaximized)
        regularWindowSize = this->size();

    //prima di caricare l'altra Ui la riporto a not-maximized a prescindere, altrimenti mi da problemi quando setto a maximized l'editor
    showNormal();

    ui2->setupUi(this);
    this->setCentralWidget(widget);

    //voglio che mi venga sempre aperta maximized
    showMaximized();

    //devo attivare qui le connect e non posso farlo prima nel costruttore perchè quando chiamo il costruttore ui2 non è ancora stato caricato
    static_cast<GUI_Editor*>(widget)->connectMenuBarActions();
    static_cast<GUI_Editor*>(widget)->changeWindowName();
}

//Warning! May return a nullptr if the user hasn't set up the correction
connection_to_server *GIMPdocs::getConnection(){
   return c;
}

void GIMPdocs::setConnection(connection_to_server *connection){
    c = connection;
}

