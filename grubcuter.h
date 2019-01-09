#ifndef GRUBCUTER_H
#define GRUBCUTER_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QImage>
#include <map>
#include <QDebug>
#include <iostream>

using namespace cv;
using namespace std;

class grubcuter
{
public:
    grubcuter();
    grubcuter(QImage image, multimap<int, int> backgroundpiexls, multimap<int, int> foregroundpiexls,
              int x, int y, int w, int h);
    void grubCut(multimap<int, int> backgroundpiexls, multimap<int, int> foregroundpiexls);
    QImage getQImage();

private:
    Mat image;
    Mat mask;
    Mat binMask;
    Mat res;
    Rect rect;
    Mat bgdModel, fgdModel;
    const int iterCount = 3;

    void setRectInMask();
    void setLblsInMask(multimap<int, int> backgroundpiexls, multimap<int, int> foregroundpiexls);
    void getBinMask();

    Mat QImage_to_Mat( const QImage &image);
    QImage cvMat_to_QImage(const Mat &mat );
};

#endif // GRUBCUTER_H
