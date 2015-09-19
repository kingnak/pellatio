#include "qtquick1applicationviewer.h"
#include <QApplication>
#include "pellatiomainwindow.h"

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    PellatioMainWindow w;
    w.start();

    return app.exec();
}
