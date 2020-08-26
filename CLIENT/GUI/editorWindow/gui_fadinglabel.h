#ifndef GUI_FADINGLABEL_H
#define GUI_FADINGLABEL_H

#include <QLabel>
#include "../gimpdocs.h"
#include <QPropertyAnimation>

class GUI_FadingLabel : public QLabel
{
    Q_OBJECT
public:
    QWidget *content;

    explicit GUI_FadingLabel(QWidget *parent = nullptr);
    void fadingLabelSetUp(QString text, int duration, float transition);
    void startFadingText(QString text = NULL);

    //è anche possibile lasciare il testo fisso
    void setPermanentText(QString text);
    void removePermanentText();

private:
    //se c'è un testo che deve rimanere permanente scelgo di non sovrascriverlo
    bool permanentText;
    QPropertyAnimation *fadingLabelAnimation;


};

#endif // GUI_FADINGLABEL_H
