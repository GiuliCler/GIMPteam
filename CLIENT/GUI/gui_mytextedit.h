#ifndef GUI_MYTEXTEDIT_H
#define GUI_MYTEXTEDIT_H

#include <QTextEdit>
#include <QTimer>
#include "gui_coloredcursor.h"
#include "gimpdocs.h"
#include <QMap>
#include <QPoint>

class GUI_MyTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    GIMPdocs *gimpParent;
    //la mappa serve per i cursori degli altri users
    QMap<long, GUI_ColoredCursor*> cursorsMap;

    explicit GUI_MyTextEdit(QWidget *parent);
    static QString getObjectName() {return QString("GUI_MyTextEdit");}

protected:
    virtual void paintEvent(QPaintEvent *pEvent) override;

public slots:
    void addUserCursor(long userId, QPoint position);
};

#endif // GUI_MYTEXTEDIT_H
