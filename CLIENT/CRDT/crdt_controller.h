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
    GIMPdocs *gimpDocs;
    GUI_Editor *editorParent;
    connection_to_server *connection;
    GUI_MyTextEdit& textEdit;
    bool highlightUsers;
    CRDT_SharedEditor crdt;
    menuTools lastOp;
    bool rememberFormatChange;
    bool validateSpin;
    bool validateFontCombo;
    bool processingMessage = false;
    int defaultFontPointSize = 12;
    int deletedAmountOnPaste;
    Qt::Alignment alignBeforePaste = Qt::AlignLeft;

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
    QMap<int, int> usersCursors;
    QMap<int, QList<CRDT_Message>> userBuffers;
    int cursorMovable_sem;
    CRDT_controller(GIMPdocs *gimpdocs, GUI_Editor *parent, GUI_MyTextEdit& textEdit, int siteId, int siteCounter);
    void setCurrentTextColor(QColor color);
    void remoteInsert(int pos, QString s, QTextCharFormat fmt, Qt::Alignment align);
    void remoteDelete(int start, int cnt);

    GIMPdocs* getGimpDocs();

~CRDT_controller();
private slots:
    void currentCharFormatChanged(const QTextCharFormat &format);
    void cursorMoved();
    void contentChanged(int pos, int del, int adds);
    void selectionChanged();
    void clipboardDataChanged();
    void undoAvailableChanged(bool available);
    void redoAvailableChanged(bool available);

public slots:
    void menuCall(menuTools op);
    void setUsersColors(bool value);
    void remoteMove(int userId, int pos);
    void remoteStopCursor();
    void remoteStartCursor(int userId);
    void remoteChangeAlign(Qt::Alignment al);

signals:
    void menuSet(menuTools set);
    void updateCursorPosition(int userId, QPoint position);
    void notifyDeletedStack();
};

#endif // CRDT_CONTROLLER_H
