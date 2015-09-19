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

    for (int i = 0; i < 81; ++i) {
        if (i%9 == 0) cout << endl;
        int index = i;
        typedef int var;
        var c = (index*17+index*index/3)%4;
        cout << c << ' ';
    }

    return app.exec();
}
