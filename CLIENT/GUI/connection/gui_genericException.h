#ifndef GUI_GENERICEXCEPTION_H
#define GUI_GENERICEXCEPTION_H

#include <QException>

class GUI_GenericException : public QException
{
    //Q_OBJECT
public:
    QString message;

    explicit GUI_GenericException(QString const& message) : message(message) {};
    ~GUI_GenericException() {};

    void raise() const override { throw *this; }
    GUI_GenericException *clone() const override { return new GUI_GenericException(*this); }

};

#endif // GUI_GENERICEXCEPTION_H
