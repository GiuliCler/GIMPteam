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
    bool rememberFormatChange;
public:
    CRDT_controller(GUI_MyTextEdit& textEdit, GUI_ToolsBar& toolbar);

private slots:
    void setLeft();
    void setCenter();
    void setRight();
    void setJustified();

    void setBold();
    void setItalic();
    void setStrikethrough();
    void setUnderlined();

    void setSize(int size);
    void setFont(const QFont &f);

    void copy();
    void cut();
    void paste();

    void setTextColor(QColor color);

    void currentCharFormatChanged(const QTextCharFormat &format);
    void cursorMoved();
    void contentChanged(int pos, int add, int del);
};

#endif // CRDT_CONTROLLER_H
