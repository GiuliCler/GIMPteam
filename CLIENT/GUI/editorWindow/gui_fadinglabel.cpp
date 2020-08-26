#include "gui_fadinglabel.h"
#include <QGraphicsOpacityEffect>

GUI_FadingLabel::GUI_FadingLabel(QWidget *parent) : QLabel(parent){
    QGraphicsOpacityEffect *fadingLabelEffect;

    permanentText = false;

    fadingLabelEffect = new QGraphicsOpacityEffect();
    fadingLabelEffect->setOpacity(0.0f);
    setGraphicsEffect(fadingLabelEffect);

    fadingLabelAnimation = new QPropertyAnimation(fadingLabelEffect, "opacity");
    fadingLabelAnimation->setStartValue(1.0f);
    fadingLabelAnimation->setEndValue(0.0f);
}

void GUI_FadingLabel::fadingLabelSetUp(QString text, int duration, float transition){
    if(duration < 1)
        return;
    if(transition < 0 || 1 < transition)
        return;

    setText(text);
    fadingLabelAnimation->setDuration(duration);
    fadingLabelAnimation->setKeyValueAt(transition, 1.0f);
}


void GUI_FadingLabel::startFadingText(QString text){
    if(permanentText)
        return;

    if(text != NULL)
        setText(text);

    fadingLabelAnimation->start();
}

void GUI_FadingLabel::setPermanentText(QString text){
    if(permanentText == true)
        return;

    setText(text);
    static_cast<QGraphicsOpacityEffect*>(graphicsEffect())->setOpacity(1.0f);
    permanentText = true;
}

void GUI_FadingLabel::removePermanentText(){
    if(permanentText == false)
        return;

    static_cast<QGraphicsOpacityEffect*>(graphicsEffect())->setOpacity(0.0f);
    permanentText = false;
}
