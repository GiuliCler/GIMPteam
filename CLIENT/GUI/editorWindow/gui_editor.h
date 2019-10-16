#ifndef GUI_EDITOR_H
#define GUI_EDITOR_H

#include "ui_gui_editor.h"
#include "../gimpdocs.h"
#include "gui_colorsmanager.h"
#include <QWidget>
#include <QMap>
#include <QColor>

class CRDT_controller;

class GUI_Editor : public QWidget
{
    Q_OBJECT
public:
    long documentId;
    GIMPdocs *gimpParent;
    CRDT_controller *crdtController;
    QMap<long, QColor*> userColorMap;
    //indica se il testo è colorato coi colori degli utenti per identificarli
    bool usersColors;

    explicit GUI_Editor(QWidget *parent, long documentId);
    ~GUI_Editor();
    inline static QString getObjectName(){ return "GUI_Editor";}
    //lo scopo di queste 2 funzioni è di venire chiamate da un più basso livello quando viene aggiunto o rimosso un nuovo utente che sta lavorando allo stesso document
    //si occupano sia del cursore che dell'icona che del colore
    void addUserToEditorGUI(long userid);
    void removeUserFromEditorGUI(long userid);
    void addContributorToCurrentDocument(long userid);
    void removeContributorFromCurrentDocument(long userid);

    //mi serve perchè non posso fare le connect direttamente nel costruttore. Quando sono nel costruttore, la ui2 non è ancora stata caricata quindi la connect va fatta in un secondo momento
    void connectMenuBarActions();

public slots:
    void launchSetUi1();
    void on_actionApplyUsersColors();
    void on_actionApplyTextColors();

private:
    Ui::GUI_Editor *ui;
    GUI_ColorsManager colorsManager;

    QColor *getUserColor(long userId);
    void forgetUserColor(long userId);

};

#endif // GUI_EDITOR_H
