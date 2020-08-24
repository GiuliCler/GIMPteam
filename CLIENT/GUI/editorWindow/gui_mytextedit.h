#ifndef GUI_MYTEXTEDIT_H
#define GUI_MYTEXTEDIT_H

#include "../gimpdocs.h"
#include "gui_coloredcursor.h"
#include "gui_editor.h"
#include <QTextEdit>
#include <QMap>

class GUI_MyTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    GUI_Editor *editorParent;
    //la mappa serve per i cursori degli altri users
    QMap<int, GUI_ColoredCursor*> cursorsMap;

    explicit GUI_MyTextEdit(QWidget *parent);
    static QString getObjectName() {return QString("GUI_MyTextEdit");}
    void setupTextEdit();

protected:
    virtual void paintEvent(QPaintEvent *pEvent) override;

signals:
    void updateCursorPosition(int userId, QPoint position);

public slots:
    void addUserCursor(int userId, QPoint position, QColor color);
    void removeUserCursor(int userId);
    void on_updateCursorPosition_emitted(int userId, QPoint position);
};

#endif // GUI_MYTEXTEDIT_H
