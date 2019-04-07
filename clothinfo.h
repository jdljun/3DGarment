#ifndef CLOTHINFO_H
#define CLOTHINFO_H
#include <QMainWindow>
#include <QPointF>
#include <iostream>
#include "basic.h"
using namespace  std;
class clothinfo  //默认服装在图像偏中间的位置 否则无法可能获取到正确结果
{
public:
    clothinfo();
    clothinfo(QImage image);
    void analysis();
    void boundchange();
    void borderline();
    void panelcut();

    QImage image;
    QPointF leftuppoint;
    QPointF rightuppoint;
    QPointF leftcutpoint;
    QPointF rightcutpoint;
    float shoulderwidth;
    float collarwidth;
    float proportion; //  collarwidth/shoulderwidth
private:
    int* leftborder;
    int* rightborder;

};

#endif // CLOTHINFO_H
