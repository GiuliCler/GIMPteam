#ifndef GUI_MOUSEEVENTFILTER_H
#define GUI_MOUSEEVENTFILTER_H

#include <QObject>
#include <QEvent>


/*Ho messo in questo file anche l'evento personalizzato da lanciare*/
class GUI_SetFilterStatus : public QEvent{

public:
    bool enabled;

    explicit GUI_SetFilterStatus(bool enabled);
    static const QEvent::Type eventType = static_cast<QEvent::Type>(QEvent::User);

};

class GUI_MouseEventFilter : public QObject
{
    Q_OBJECT
public:
    explicit GUI_MouseEventFilter(QObject *parent);
    inline static QString getObjectName() {return QString("GUI_MouseEventFilter");}

    virtual bool eventFilter(QObject *watched, QEvent *event) override;

private:
    bool filter = false;

};

#endif // GUI_MOUSEEVENTFILTER_H
