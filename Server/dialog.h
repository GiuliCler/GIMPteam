#ifndef DIALOG_H
#define DIALOG_H

#include <QWidget>
#include "server.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
QT_END_NAMESPACE

class Dialog : public QWidget
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);
    QSslKey key;
    QSslCertificate cert;

private:
    QLabel *statusLabel;
    QPushButton *quitButton;
    Server server;
};

#endif
