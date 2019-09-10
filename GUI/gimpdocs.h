#ifndef GIMPDOCS_H
#define GIMPDOCS_H

#include <QDialog>
#include "gui_login.h"
#include "stub.h"
#include "gui_icons.h"

//se proprio non posso usarla me la tengo qui per fare copia incolla
//#define PARENT static_cast<GIMPdocs*>(this->parent())

namespace Ui {
class GIMPdocs;
}

class GIMPdocs : public QDialog
{
    Q_OBJECT

public:
    long userid;

    explicit GIMPdocs(QWidget *parent = nullptr);
    ~GIMPdocs();
    void loadCentralWidget(QWidget* widget);

private:
    Ui::GIMPdocs *ui;
    QHBoxLayout *layout;
    QWidget *centralWidget;
};

#endif // GIMPDOCS_H
