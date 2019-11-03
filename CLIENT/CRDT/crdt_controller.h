#ifndef CRDT_CONTROLLER_H
#define CRDT_CONTROLLER_H

#include <QObject>
#include "../GUI/editorWindow/gui_mytextedit.h"
#include "../GUI/editorWindow/gui_toolsbar.h"


class CRDT_controller : public QObject
{
    Q_OBJECT

private:
    GUI_Editor *parent;
    GUI_MyTextEdit& textEdit;
    menuTools lastOp;
    bool rememberFormatChange;
    bool validateSpin;

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

public:
    CRDT_controller(GUI_Editor *parent, GUI_MyTextEdit& textEdit);
    void setCurrentTextColor(QColor color);

private slots:
    void menuCall(menuTools op);
    void currentCharFormatChanged(const QTextCharFormat &format);
    void cursorMoved();
    void contentChanged(int pos, int add, int del);
    void selectionChanged();

signals:
    void menuSet(menuTools set);
};

#endif // CRDT_CONTROLLER_H
