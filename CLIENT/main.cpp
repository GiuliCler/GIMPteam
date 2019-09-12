#include <QApplication>
#include "GUI/gimpdocs.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GIMPdocs w;
    w.show();

    return a.exec();
}
