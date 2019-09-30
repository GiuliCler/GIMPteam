#ifndef GUI_EDITOR_H
#define GUI_EDITOR_H

#include <QWidget>
#include "ui_gui_editor.h"
#include "../gimpdocs.h"
#include "gui_colorsmanager.h"
#include <QTimer>
#include <QLabel>
#include <QMap>
#include <QColor>

class GUI_Editor : public QWidget
{
    Q_OBJECT
public:
    long documentId;
    GIMPdocs *gimpParent;
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
    void launchSetUi1();

public slots:
    void on_actionApplyUsersColors();
    void on_actionApplyTextColors();
    //debug
    void timerSlot();

private:
    Ui::GUI_Editor *ui;
    GUI_ColorsManager colorsManager;
    //debug
    QTimer *timer;

    //void setUsersBar();

};

#endif // GUI_EDITOR_H
