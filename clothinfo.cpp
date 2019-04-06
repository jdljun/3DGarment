#include "clothinfo.h"

clothinfo::clothinfo()
{
    image.load(QString::fromStdString(grubcutboundaryPath));
    analysis();
}

clothinfo::clothinfo(QImage image)
{
    this->image=image;
    analysis();
}

void clothinfo::analysis(){
    int w = image.width(); //横轴
    int h = image.height();//纵轴
   // for(int i=0;i<w;i++){
       // for(int j=0;j<h;j++)
           // cout<<qRed(image.pixel(i,j))<<" ";
       // cout<<endl;
  //  }

    //服装左边部分计算
    for(int j=0;j<h;j++){
        bool isfirst=true;
        for(int i=w/2;i>=0;i--){
            QRgb rgb = image.pixel(i,j);
            if((qRed(rgb)+qGreen(rgb)+qBlue(rgb))==0)//无关点
                continue;
        }
    }
}
