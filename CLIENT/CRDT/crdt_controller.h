#ifndef CRDT_CONTROLLER_H
#define CRDT_CONTROLLER_H

#include <QObject>
#include "../GUI/editorWindow/gui_mytextedit.h"
#include "../GUI/editorWindow/gui_toolsbar.h"
#include "crdt_sharededitor.h"


class CRDT_SharedEditor;

class CRDT_controller : public QObject
{
    Q_OBJECT

private:
    GUI_Editor *parent;
    GUI_MyTextEdit& textEdit;
    CRDT_SharedEditor crdt;
    menuTools lastOp;
    bool rememberFormatChange;
    bool validateSpin;
    bool validateFontCombo;
    bool processingMessage = false;

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

    void undo();
    void redo();

public:
    CRDT_controller(GUI_Editor *parent, GUI_MyTextEdit& textEdit);
    void setCurrentTextColor(QColor color);

    void remoteInsert(int pos, QChar c, QTextCharFormat fmt, Qt::Alignment align);
    void remoteDelete(int pos);

private slots:
    void menuCall(menuTools op);
    void currentCharFormatChanged(const QTextCharFormat &format);
    void cursorMoved();
    void contentChanged(int pos, int del, int add);
    void selectionChanged();
    void clipboardDataChanged();
    void undoAvailableChanged(bool available);
    void redoAvailableChanged(bool available);

signals:
    void menuSet(menuTools set);
};

#endif // CRDT_CONTROLLER_H