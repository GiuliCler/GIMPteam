#ifndef GIMPDOCS_H
#define GIMPDOCS_H

#include <QDialog>
#include "gui_login.h"
#include "stub.h"

namespace Ui {
class GIMPdocs;
}

class GIMPdocs : public QDialog
{
    Q_OBJECT

public:
    explicit GIMPdocs(QWidget *parent = nullptr);
    ~GIMPdocs();
    void loadCentralWidget(QWidget* widget);

private:
    Ui::GIMPdocs *ui;
    QHBoxLayout *layout;
    QWidget *centralWidget;
};

#endif // GIMPDOCS_H
