#ifndef CRDT_CONTROLLER_H
#define CRDT_CONTROLLER_H

#include <QObject>
#include "../GUI/editorWindow/gui_mytextedit.h"
#include "../GUI/editorWindow/gui_toolsbar.h"


class CRDT_controller : public QObject
{
    Q_OBJECT

private:
    GUI_MyTextEdit& textEdit;
    GUI_ToolsBar& toolbar;
public:
    CRDT_controller(GUI_MyTextEdit& textEdit, GUI_ToolsBar& toolbar);

public slots:
    void setItalic();
};

#endif // CRDT_CONTROLLER_H
