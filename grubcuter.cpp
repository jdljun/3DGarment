﻿#include "grubcuter.h"

grubcuter::grubcuter()
{

}

grubcuter::grubcuter(QImage image, multimap<int, int> backgroundpiexls, multimap<int, int> foregroundpiexls,
          int x, int y, int w, int h){
    this->image = &QImage_to_Mat(image);
}

void grubcuter::grubCut(){
    grabCut(*image,mask,rect,bgdModel,fgdModel,iterCount,GC_INIT_WITH_RECT);
}

QImage grubcuter::getQImage(){
    return cvMat_to_QImage(*image);
}

/*
原始C++的cv::grabCut函数参考
void cv::grabCut( InputArray _img, InputOutputArray _mask, Rect rect,
                  InputOutputArray _bgdModel, InputOutputArray _fgdModel,
                  int iterCount, int mode )

OutputArrayOfArrays、InputOutputArray、InputOutputArrayOfArrays都是OutputArray的别名
OutputArray是InputArray的派生类
使用_OutputArray::getMat()之前一定要调用_OutputArray::create()为矩阵分配空间。
可以用_OutputArray::needed()来检测输出的矩阵是否需要被计算。

参数说明：
img——待分割的源图像，必须是8位3通道（CV_8UC3）图像，在处理的过程中不会被修改；

mask——掩码图像，如果使用掩码进行初始化，那么mask保存初始化掩码信息；
      在执行分割的时候，也可以将用户交互所设定的前景与背景保存到mask中，然后再传入grabCut函数；
      在处理结束之后，mask中会保存结果。mask只能取以下四种值：
            GCD_BGD（=0），背景；
            GCD_FGD（=1），前景；
            GCD_PR_BGD（=2），可能的背景；
            GCD_PR_FGD（=3），可能的前景。
            如果没有手工标记GCD_BGD或者GCD_FGD，那么结果只会有GCD_PR_BGD或GCD_PR_FGD；

rect——用于限定需要进行分割的图像范围，只有该矩形窗口内的图像部分才被处理，可为None；

bgdModel——背景模型，如果为null，函数内部会自动创建一个bgdModel；bgdModel必须是单通道浮点型（CV_32FC1）图像，
          且行数只能为1，列数只能为13x5；

fgdModel——前景模型，如果为null，函数内部会自动创建一个fgdModel；fgdModel必须是单通道浮点型（CV_32FC1）图像，
          且行数只能为1，列数只能为13x5；

iterCount——迭代次数，必须大于0；

mode——用于指示grabCut函数进行什么操作，可选的值有：
      GC_INIT_WITH_RECT（=0），用矩形窗初始化GrabCut；
      GC_INIT_WITH_MASK（=1），用掩码图像初始化GrabCut；
      GC_EVAL（=2），执行分割。

*/

Mat grubcuter::QImage_to_Mat( const QImage &image){
    bool inCloneImageData = true;
    switch ( image.format() )
    {
       // 8-bit, 4 channel
       case QImage::Format_RGB32:
       {
          Mat mat( image.height(), image.width(), CV_8UC4, const_cast<uchar*>(image.bits()), image.bytesPerLine() );
          return (inCloneImageData ? mat.clone() : mat);
       }

       // 8-bit, 3 channel
       case QImage::Format_RGB888:
       {
          if ( !inCloneImageData ) {
             qWarning() << "ASM::QImageToCvMat() - Conversion requires cloning since we use a temporary QImage";
          }
          QImage swapped = image.rgbSwapped();
          return Mat( swapped.height(), swapped.width(), CV_8UC3, const_cast<uchar*>(swapped.bits()), swapped.bytesPerLine() ).clone();
       }

       // 8-bit, 1 channel
       case QImage::Format_Indexed8:
       {
          Mat  mat( image.height(), image.width(), CV_8UC1, const_cast<uchar*>(image.bits()), image.bytesPerLine() );
          return (inCloneImageData ? mat.clone() : mat);
       }

       default:{
          qDebug("Image format is not supported: depth=%d and %d format\n", image.depth(), image.format());
          break;
       }

    }

    return Mat();
}

QImage grubcuter::cvMat_to_QImage(const Mat &mat ){
    switch ( mat.type() )
    {
       // 8-bit, 4 channel
       case CV_8UC4:
       {
          QImage image( mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB32 );
          return image;
       }

       // 8-bit, 3 channel
       case CV_8UC3:
       {
          QImage image( mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888 );
          return image.rgbSwapped();
       }

       // 8-bit, 1 channel
       case CV_8UC1:
       {
          static QVector<QRgb>  sColorTable;
          // only create our color table once
          if ( sColorTable.isEmpty() )
          {
             for ( int i = 0; i < 256; ++i )
                sColorTable.push_back( qRgb( i, i, i ) );
          }
          QImage image( mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8 );
          image.setColorTable( sColorTable );
          return image;
       }

       default:
          qDebug("Image format is not supported: depth=%d and %d channels\n", mat.depth(), mat.channels());
          break;
    }
    return QImage();
}
