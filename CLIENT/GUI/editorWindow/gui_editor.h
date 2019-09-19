#ifndef GUI_EDITOR_H
#define GUI_EDITOR_H

#include <QWidget>
#include "ui_gui_editor.h"
#include "../gimpdocs.h"
#include <QTimer>
#include <QLabel>

class GUI_Editor : public QWidget
{
    Q_OBJECT
public:
    long documentId;
    GIMPdocs *gimpParent;

    explicit GUI_Editor(QWidget *parent, long documentId);
    ~GUI_Editor();
    inline static QString getObjectName(){ return "GUI_Editor";}



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
