#include "mainwindow.h"
#include <QApplication>
#include<reader.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    reader read;
    read.readFile(":/person.bmp");
    w.show();

    return a.exec();
}


