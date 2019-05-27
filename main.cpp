#include "mainwindow.h"
#include "cutwindow.h"
#include "display.h"
#include "clothinfo.h"
#include <QApplication>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   // clothinfo c;
    MainWindow w;

    w.show();
    //display d;
    //d.resize(1200, 800);
    //d.show();
    return a.exec();

}


