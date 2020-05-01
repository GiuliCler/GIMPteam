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

public slots:
    //DEBUG: il campo position è poi da togliere
    void addUserCursor(int userId, QPoint position, QColor color);
    void removeUserCursor(int userId);
};

#endif // GUI_MYTEXTEDIT_H
