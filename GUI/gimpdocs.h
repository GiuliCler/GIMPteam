#ifndef GIMPDOCS_H
#define GIMPDOCS_H

#include <QMainWindow>
#include <QDebug>
#include "stub.h"
#include "gui_icons.h"
#include "ui_gimpdocs.h"

//se proprio non posso usarla me la tengo qui per fare copia incolla
//#define PARENT static_cast<GIMPdocs*>(this->parent())


class GIMPdocs : public QMainWindow
{
    Q_OBJECT

public:
    long userid;

    explicit GIMPdocs(QWidget *parent = nullptr);
    ~GIMPdocs();
    //carica il widget centrale coi dovuti controlli e chiude il precedente
    void loadCentralWidget(QWidget* widget);

private:
    Ui::GIMPdocs *ui;
    QWidget *centralWidget;
};

#endif // GIMPDOCS_H
