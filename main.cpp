#include "srca.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SRCA w;
    w.show();

    return a.exec();
}
