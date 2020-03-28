#ifndef GUI_EDITOR_H
#define GUI_EDITOR_H

#include "ui_gui_editor.h"
#include "../gimpdocs.h"
#include "gui_colorsmanager.h"
#include <QWidget>
#include <QMap>
#include <QColor>

class GUI_ToolsBar;
class GUI_UsersBar;
class GUI_MyTextEdit;

enum menuTools {A_LEFT, A_CENTER, A_RIGHT, A_JUSTIFIED, BOLD_ON, BOLD_OFF, ITALIC_ON, ITALIC_OFF, UNDERLINED_ON, UNDERLINED_OFF, STRIKETHROUGH_ON, STRIKETHROUGH_OFF};

class GUI_Editor : public QWidget
{
    Q_OBJECT
public:
    int documentId;
    GIMPdocs *gimpParent;
    GUI_ToolsBar *childToolsBar;
    GUI_UsersBar *childUsersBar;
    GUI_MyTextEdit *childMyTextEdit;
    QMap<int, QColor*> userColorMap;
    //indica se il testo è colorato coi colori degli utenti per identificarli
    bool usersColors;

    explicit GUI_Editor(QWidget *parent, int documentId);
    ~GUI_Editor();
    inline static QString getObjectName(){ return "GUI_Editor";}
    //lo scopo di queste 2 funzioni è di venire chiamate da un più basso livello quando viene aggiunto o rimosso un nuovo utente che sta lavorando allo stesso document
    //si occupano sia del cursore che dell'icona che del colore
    void addUserToEditorGUI(int userid);
    void removeUserFromEditorGUI(int userid);
    void addContributorToCurrentDocument(int userid);
    void removeContributorFromCurrentDocument(int userid);

    //mi serve perchè non posso fare le connect direttamente nel costruttore. Quando sono nel costruttore, la ui2 non è ancora stata caricata quindi la connect va fatta in un secondo momento
    void connectMenuBarActions();
    //non posso falro nel costruttore perchè quando costruisco il widget, il cambio di window deve ancora avvenire
    void changeWindowName();

public slots:
    void launchSetUi1();
    void on_actionApplyUsersColors();
    void on_actionApplyTextColors();

    void on_actionBold();
    void on_actionItalic();
    void on_actionUnderlined();
    void on_actionStrikethrough();
    void on_actionLeft();
    void on_actionCenter();
    void on_actionRight();
    void on_actionJustified();

    void setMenuToolStatus(menuTools code);

private:
    Ui::GUI_Editor *ui;
    GUI_ColorsManager colorsManager;

    QColor *getUserColor(int userId);
    void forgetUserColor(int userId);

signals:
    void menuTools_event(menuTools code);

};

#endif // GUI_EDITOR_H
