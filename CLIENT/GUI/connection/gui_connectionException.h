#ifndef GUI_CONNECTIONEXCEPTION_H
#define GUI_CONNECTIONEXCEPTION_H

#include <QException>

class GUI_ConnectionException : public QException
{
    //Q_OBJECT
public:
    QString message;

    explicit GUI_ConnectionException() : message("") {};
    explicit GUI_ConnectionException(QString const& message) : message(message) {};
    ~GUI_ConnectionException() {};

    void raise() const override { throw *this; }
    GUI_ConnectionException *clone() const override { return new GUI_ConnectionException(*this); }
};

#endif // GUI_CONNECTIONEXCEPTION_H
