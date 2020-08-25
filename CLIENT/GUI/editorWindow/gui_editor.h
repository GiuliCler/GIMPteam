#ifndef GUI_EDITOR_H
#define GUI_EDITOR_H

#include "ui_gui_editor.h"
#include "gui_colorsmanager.h"
#include <QWidget>
#include <QMap>
#include <QColor>

class CRDT_controller;
class GUI_ToolsBar;
class GUI_UsersBar;
class GUI_MyTextEdit;
class GIMPdocs;

enum menuTools {UNDO_ON, UNDO_OFF, REDO_ON, REDO_OFF, CUT_ON, CUT_OFF, COPY_ON, COPY_OFF, PASTE_ON, PASTE_OFF, A_LEFT, A_CENTER, A_RIGHT, A_JUSTIFIED, BOLD_ON, BOLD_OFF, ITALIC_ON, ITALIC_OFF, UNDERLINED_ON, UNDERLINED_OFF, STRIKETHROUGH_ON, STRIKETHROUGH_OFF};

class GUI_Editor : public QWidget
{
    Q_OBJECT
public:
    int documentId;
    //indica se il testo è evidenziato coi colori degli utenti per identificarli
    bool usersColors;
    GIMPdocs *gimpParent;
    GUI_ToolsBar *childToolsBar;
    GUI_UsersBar *childUsersBar;
    GUI_MyTextEdit *childMyTextEdit;
    CRDT_controller *crdtController;


    explicit GUI_Editor(QWidget *parent, int documentId, QString docName, int siteCounter);
    ~GUI_Editor();
    inline static QString getObjectName(){ return "GUI_Editor";}
    QColor *getUserColor(int userId);

    //mi serve perchè non posso fare le connect direttamente nel costruttore. Quando sono nel costruttore, la ui2 non è ancora stata caricata quindi la connect va fatta in un secondo momento
    void connectMenuBarActions();
    //non posso falro nel costruttore perchè quando costruisco il widget, il cambio di window deve ancora avvenire
    void setUpEditor();

public slots:
    void closeDocument();
    void forcedCloseDocument();
    void launchSetUi1();
    void on_actionApplyUsersColors();
    void on_actionApplyTextColors();

    void on_actionUndo();
    void on_actionRedo();
    void on_actionCut();
    void on_actionCopy();
    void on_actionPaste();
    void on_actionBold();
    void on_actionItalic();
    void on_actionUnderlined();
    void on_actionStrikethrough();
    void on_actionLeft();
    void on_actionCenter();
    void on_actionRight();
    void on_actionJustified();

    void setMenuToolStatus(menuTools code);
    //lo scopo di queste 2 funzioni è di venire chiamate da un più basso livello quando viene aggiunto o rimosso un nuovo utente che sta lavorando allo stesso document
    void addUserToEditorGUI(int userid, QString nickname, QString iconId);
    void removeUserFromEditorGUI(int userid);
    void addContributorToCurrentDocument(int userid, QString nickname, QString iconId);

private:

    QString docName;
    QString uri;
    Ui::GUI_Editor *ui;
    GUI_ColorsManager colorsManager;
    QMap<int, QColor*> userColorMap;

    //void forgetUserColor(int userId);
    void fillOnlineUsersList();
    void fillContibutorUsersList();

signals:
    void menuTools_event(menuTools code);

};

#endif // GUI_EDITOR_H
