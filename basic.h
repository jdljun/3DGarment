#ifndef BASIC_H
#define BASIC_H
#include<QString>
#include<iostream>
#include<QDebug>

using namespace std;

class RGB
{
public:
    quint8  b;
    quint8  g;
    quint8  r;
    quint8 rgbReserved;
};
#endif // BASIC_H
