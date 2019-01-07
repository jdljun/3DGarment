#ifndef GRUBCUTER_H
#define GRUBCUTER_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QImage>
#include <map>
#include <QDebug>

using namespace cv;
using namespace std;

class grubcuter
{
public:
    grubcuter();
    grubcuter(QImage image, multimap<int, int> backgroundpiexls, multimap<int, int> foregroundpiexls,
              int x, int y, int w, int h);
    void grubCut();
    QImage getQImage();

private:
    const Mat* image;
    Mat mask;
    Rect rect;
    Mat bgdModel, fgdModel;
    const int iterCount = 1;

    Mat QImage_to_Mat( const QImage &image);
    QImage cvMat_to_QImage(const Mat &mat );
};

#endif // GRUBCUTER_H
