#include "gimpdocs.h"
#include "gui_login.h"
#include "editorWindow/gui_editor.h"

GIMPdocs::GIMPdocs(QWidget *parent) : QMainWindow(parent), userid(-1)
{
    ui1 = new Ui::GIMPdocs;
    ui2 = new Ui::GUI_EditWindow;

    regularWindowSize = this->size();
    alreadyMaximized = false;
    setUi1(new GUI_Login(this));
}

GIMPdocs::~GIMPdocs(){
    delete ui1;
    delete ui2;
}

void GIMPdocs::setUi1(QWidget *widget){
    //serve ad annullare showMaximized e lo metto qui perchè se lo metto dopo la set central window mi sballa il corner topLeft della window
    if(!alreadyMaximized)
        showNormal();

    ui1->setupUi(this);
    this->setCentralWidget(widget);

    if(alreadyMaximized){
        //la resize (consigliata dal forum) serve perchè altrimenti mi mostra una window non maximized ma che non so perchè conta come maximized
        resize(maximumWidth(), maximumHeight());
        //è importante che showMaximized venga lanciato dopo il cambio di ui perchè sì, atrimenti fa casini e non massimizza
        showMaximized();
    }
    else {
        //la adjustSize, che dovrebbe adeguare la size al contenuto, in realtà serve solo come trucco magico per poter usare la resize. Per qualche strana ragione, senza la adjustSize la resize viene eseguita prima della setCentralWwidget
        adjustSize();
        //questa ripristina le dimensioni precedenti alla showMaximized
        resize(regularWindowSize);
    }
}

void GIMPdocs::setUi2(QWidget *widget){

    alreadyMaximized = isMaximized();
    if(!alreadyMaximized)
        regularWindowSize = this->size();

    ui2->setupUi(this);
    this->setCentralWidget(widget);

    //la resize (consigliata dal forum) serve perchè altrimenti mi mostra una window non maximized ma che non so perchè conta come maximized
    resize(maximumWidth(), maximumHeight());
    //è importante che showMaximized venga lanciato dopo il cambio di ui perchè sì, atrimenti fa casini e non massimizza
    showMaximized();

    //devo attivare qui le connect e non posso farlo prima nel costruttore perchè quando chiamo il costruttore ui2 non è ancora stato caricato
    static_cast<GUI_Editor*>(widget)->connectMenuBarActions();
    static_cast<GUI_Editor*>(widget)->setupTextEdit();
}
