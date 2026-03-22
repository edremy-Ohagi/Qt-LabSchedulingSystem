#include "edrmainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    edrMainWindow w;
    w.show();
    return a.exec();
}
