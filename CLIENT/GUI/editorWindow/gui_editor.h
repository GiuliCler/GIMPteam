#ifndef GUI_EDITOR_H
#define GUI_EDITOR_H

#include <QWidget>
#include "ui_gui_editor.h"
#include "../gimpdocs.h"
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
    QMap<long, QColor> userColorMap;

    explicit GUI_Editor(QWidget *parent, long documentId);
    ~GUI_Editor();
    inline static QString getObjectName(){ return "GUI_Editor";}
    //lo scopo di queste 2 funzioni è di venire chiamate da un più basso livello quando viene aggiunto o rimosso un nuovo utente che sta lavorando allo stesso document
    //si occupano sia del cursore che dell'icona che del colore
    void addUserToEditorGUI(long userid);
    void removeUserFromEditorGUI(long userid);

private slots:
    //debug
    void timerSlot();

private:
    Ui::GUI_Editor *ui;

    //debug
    QTimer *timer;

    void setUsersBar();

};

#endif // GUI_EDITOR_H
