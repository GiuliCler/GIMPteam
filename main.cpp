#include "gimpdocs.h"
#include <QApplication>
//#include "gui_login.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GIMPdocs w;
    w.show();

    /*GUI_Login login;
    login.show();*/

    return a.exec();
}
