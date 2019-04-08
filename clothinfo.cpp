#include "clothinfo.h"

clothinfo::clothinfo()
{
    image.load(QString::fromStdString(grubcutboundaryPath));
    boundchange();
    analysis();
    borderline();
    //panelcut();
    shoulderwidthCal();
    collarwidthCal();

}

clothinfo::clothinfo(QImage image)
{
    this->image=image;
    boundchange();
    analysis();
    borderline();
    //panelcut();
    shoulderwidthCal();
    collarwidthCal();
}

void clothinfo::boundchange(){
    QImage newboundary(image);
    for(int i=0;i<image.width();i++)
        for(int j=0;j<image.height();j++){
            QRgb rgb = image.pixel(i,j);
            if((qRed(rgb)+qGreen(rgb)+qBlue(rgb))<700){
                QRgb blank = qRgb(0,0,0);
                newboundary.setPixel(i,j,blank);
            }
            else{
                QRgb white = qRgb(255,255,255);
                newboundary.setPixel(i,j,white);
            }
        }
    newboundary.save(QString::fromStdString(newboundarypath),"JPG",100);
    image.load(QString::fromStdString(newboundarypath));
}
void clothinfo::analysis(){
    int w = image.width(); //横轴
    int h = image.height();//纵轴

    for(int j=0;j<h;j++){
        bool found=false;
        for(int i=0;i<w/2;i++){
            QRgb rgb = image.pixel(i,j);
            if((qRed(rgb)+qGreen(rgb)+qBlue(rgb))<700)
                continue;
            if((qRed(rgb)+qGreen(rgb)+qBlue(rgb))!=0){
                leftuppoint.setX(i);
                leftuppoint.setY(j);
                found=true;
            }
        }
        if(found==true) break;
    }
    for(int j=0;j<h;j++){
        bool found=false;
        for(int i=w/2;i<w;i++){
            QRgb rgb = image.pixel(i,j);
            if((qRed(rgb)+qGreen(rgb)+qBlue(rgb))<700)
                continue;
            if((qRed(rgb)+qGreen(rgb)+qBlue(rgb))!=0){
                rightuppoint.setX(i);
                rightuppoint.setY(j);
                found=true;
            }
        }
        if(found==true) break;
    }

    //cout<<leftuppoint.x()<<" "<<leftuppoint.y()<<" "<<rightuppoint.x()<< " "<<rightuppoint.y()<<endl;
    int state=0;
    int old=0;
    int k=0;
    for(int j=leftuppoint.y()+1;j<h;j++){
        old=k;
        k=0;
        for(int i=0;i<w/2;i++){
            QRgb rgb = image.pixel(i,j);
            if((qRed(rgb)+qGreen(rgb)+qBlue(rgb))<700)
                continue;
            if((qRed(rgb)+qGreen(rgb)+qBlue(rgb))!=0){
               k++;
               i=i+w/100;
            }
        }
        if(k>1&&old>1&&state==0)
            state=1;
        if(k==1&&old==1&&state==1)
            state=2;
        if(k>1&&old==1&&state==2){
            leftcutpoint.setY(j);
            for(int i=w/2;i>=0;i--){
                QRgb rgb = image.pixel(i,j);
                if((qRed(rgb)+qGreen(rgb)+qBlue(rgb))<700)
                    continue;
                if((qRed(rgb)+qGreen(rgb)+qBlue(rgb))!=0){
                    leftcutpoint.setX(i);
                    break;
                }
            }
            break;
        }
    }
    state=0;
    old=0;
    k=0;
    for(int j=rightuppoint.y()+1;j<h;j++){
        old=k;
        k=0;
        for(int i=w/2;i<w;i++){
            QRgb rgb = image.pixel(i,j);
            if((qRed(rgb)+qGreen(rgb)+qBlue(rgb))<700)
                continue;
            if((qRed(rgb)+qGreen(rgb)+qBlue(rgb))!=0){
               k++;
               i=i+w/100;
            }
        }
        if(k>1&&old>1&&state==0)
            state=1;
        if(k==1&&old==1&&state==1)
            state=2;
        if(k>1&&old==1&&state==2){
            rightcutpoint.setY(j);
            for(int i=w/2;i<w;i++){
                QRgb rgb = image.pixel(i,j);
                if((qRed(rgb)+qGreen(rgb)+qBlue(rgb))<700)
                    continue;
                if((qRed(rgb)+qGreen(rgb)+qBlue(rgb))!=0){
                    rightcutpoint.setX(i);
                    break;
                }
            }
            break;
        }
    }
    /*
    cout<<leftcutpoint.x()<<" "<<leftcutpoint.y()<<endl;
    QRgb rgb = image.pixel(leftcutpoint.x(),leftcutpoint.y());
    cout<<qRed(rgb)+qGreen(rgb)+qBlue(rgb)<< " ";
    cout<<rightcutpoint.x()<<" "<<rightcutpoint.y()<<endl;
    QRgb rgb = image.pixel(rightcutpoint.x(),rightcutpoint.y());
    cout<<qRed(rgb)+qGreen(rgb)+qBlue(rgb)<< " ";
    for(int i=0;i<w;i++){
        for(int j=0;j<h;j++){
            QRgb rgb = image.pixel(i,j);
            cout<<qRed(rgb)+qGreen(rgb)+qBlue(rgb)<< " ";
        }
        cout<<endl;
    }
    */
}

void clothinfo::borderline(){
     //初始化
    leftborder = new int[image.height()];
    rightborder = new int[image.height()];
    for(int i=0;i<image.height();i++){
        leftborder[i]=0;
        rightborder[i]=0;
    }
    //leftborderline generate
    for(int j=leftuppoint.y();j<image.height();j++){
        if(j<=leftcutpoint.y())
            leftborder[j]=leftcutpoint.x();
        else{
            for(int i=image.width()/2;i>=0;i--){
                QRgb rgb = image.pixel(i,j);
                if((qRed(rgb)+qGreen(rgb)+qBlue(rgb))<700)
                    continue;
                if((qRed(rgb)+qGreen(rgb)+qBlue(rgb))!=0){
                    if(i>leftborder[j-1])
                        leftborder[j]=leftborder[j-1];
                    else
                        leftborder[j]=i-1;
                    break;
                }
            }
            if(leftborder==0)
                leftborder[j]=leftborder[j-1];
        }
    }
    /*for(int j=leftuppoint.y();j<image.height();j++){
        cout<<leftborder[j]<<" ";
    }*/
    //rightborderline generate
    for(int j=rightuppoint.y();j<image.height();j++){
        if(j<=rightcutpoint.y())
            rightborder[j]=rightcutpoint.x();
        else{
            for(int i=image.width()/2;i<image.width();i++){
                QRgb rgb = image.pixel(i,j);
                if((qRed(rgb)+qGreen(rgb)+qBlue(rgb))<700)
                    continue;
                if((qRed(rgb)+qGreen(rgb)+qBlue(rgb))!=0){
                    if(i<rightborder[j-1])
                        rightborder[j]=rightborder[j-1];
                    else
                        rightborder[j]=i+1;
                    break;
                }
            }
            if(rightborder[j]==0)
                rightborder[j]=rightborder[j-1];
        }
    }
    /*
    for(int j=rightuppoint.y();j<image.height();j++){
        cout<<rightborder[j]<<" ";
    }*/

}
void clothinfo::panelcut(){
    QImage newimage;
    newimage.load(QString::fromStdString(grubcutResultPath));
    QImage leftpart(newimage);
    QImage middlepart(newimage);
    QImage rightpart(newimage);
    for(int i=0;i<newimage.width();i++){
        for(int j=0;j<newimage.height();j++){
            QRgb rgb = newimage.pixel(i,j);
            if((qRed(rgb)+qGreen(rgb)+qBlue(rgb))==0)//无关点
                continue;
            QRgb reg = qRgb(0,0,0);
            if(i<leftborder[j]){  //the point is in leftpart
                middlepart.setPixel(i,j,reg);
                rightpart.setPixel(i,j,reg);
            }else if(i>rightborder[j]){//the point is in rightpart
                leftpart.setPixel(i,j,reg);
                middlepart.setPixel(i,j,reg);
            }
            else{   //the point is in middlepart
                leftpart.setPixel(i,j,reg);
                rightpart.setPixel(i,j,reg);
            }

        }
    }
    //保存分割后的部分
    leftpart.save(QString::fromStdString(leftpartpath),"JPG",100);
    middlepart.save(QString::fromStdString(middlepartpath),"JPG",100);
    rightpart.save(QString::fromStdString(rightpartpath),"JPG",100);
}

void clothinfo::shoulderwidthCal(){
    shoulderwidth=rightcutpoint.x()-leftcutpoint.x();
    cout<<"shoulderwidth="<<shoulderwidth<<endl;
}

void clothinfo::collarwidthCal(){
    QPointF center;
    center.setX((leftuppoint.x()+rightuppoint.x())/2);
    center.setY((leftuppoint.y()+rightuppoint.y())/2);

    collarwidth=0;
    int num=rightuppoint.x()-leftuppoint.x();
    for(int i=leftuppoint.x();i<rightuppoint.x();i++){
        for(int j=min(leftuppoint.y(),rightuppoint.y());j<image.height();j++){
            QRgb rgb = image.pixel(i,j);
            if((qRed(rgb)+qGreen(rgb)+qBlue(rgb))<700)//无关点
                continue;
            collarwidth+=sqrt((center.x()-i)*(center.x()-i)+(center.y()-j)*(center.y()-j))/num;
            break;
        }
    }
    proportion=collarwidth/shoulderwidth;
    cout<<"collarwidth="<<collarwidth<<endl;
    cout<<"proportion="<<proportion<<endl;
}
