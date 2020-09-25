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

    explicit GUI_MyTextEdit(QWidget *parent);
    inline static QString getObjectName() {return QString("GUI_MyTextEdit");}

    void setupTextEdit();
private:
    //la mappa serve per i cursori degli altri users
    QMap<int, GUI_ColoredCursor*> cursorsMap;

protected:
    virtual void paintEvent(QPaintEvent *pEvent) override;
    void insertFromMimeData (const QMimeData * source) override;

public slots:
    void addUserCursor(int userId, QPoint position, QColor color);
    void removeUserCursor(int userId);
    void on_updateCursorPosition_emitted(int userId, QPoint position);
};

#endif // GUI_MYTEXTEDIT_H
