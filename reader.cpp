#include "reader.h"

#include <qdatastream.h>
reader::reader()
{

}

bool reader::readFile(QString fileName){
    if(fileName.indexOf(".bmp")!=-1)
        return readBmp(fileName);
    else if(fileName.indexOf(".jpg")!=-1)
        return readJpg(fileName);
    else if(fileName.indexOf(".png")!=-1)
        return readPng(fileName);
    return false;
}
//大小端转化
quint32 DWORDtoQuint32(quint32  n)
{
    quint32 r = 0x00000000, temp = 0x00000000;
    temp = n >> 24; //取出第一个字节
    r = r + temp;
    temp = (n & (0x00ff0000)) >> 8; //取出第二个字节
    r = r + temp;
    temp = (n & (0x0000ff00)) << 8; //取出第三个字节
    r = r + temp;
    temp = (n & (0x000000ff)) << 24; //取出第四个字节
    r = r + temp;
    return r;
}
//大小端转化
quint16 WORDtoQuint16(quint16 n)
{
    quint16 r = 0x00000000, temp = 0x00000000;
    temp = n >> 8; //取出第一个字节
    r = r + temp;
    temp = (n & (0x00ff0000)) >> 8; //取出第二个字节
    r = r + temp;
    return r;
}
//大小端转化
qint32 LONGtoQint32(qint32 n)
{
    qint32 r = 0x00000000, temp = 0x00000000;
    temp = n >> 24; //取出第一个字节
    temp = temp & 0x000000ff; //为了实现逻辑右移
    r = r + temp;
    temp = (n & (0x00ff0000)) >> 8; //取出第二个字节
    temp = temp & 0x00ffffff; //实现右移的逻辑化
    r = r + temp;
    temp = (n & (0x0000ff00)) << 8; //取出第三个字节
    r = r + temp;
    temp = (n & (0x000000ff)) << 24; //取出第四个字节
    r = r + temp;
    return r;
}

//24位图bmp图像
bool reader::readBmp(QString fileName){

    QFile fp(fileName);
    if(!fp.open(QIODevice::ReadOnly)){
        cout<<"file open failed";
        return NULL;
    }

    QDataStream in(&fp);
    in.setVersion(QDataStream::Qt_5_7);

    bitmap bmp;
    //读取文件头
    in >> bmp.filehead.type; //读取文件类型
    in >> bmp.filehead.size; //读取文件大小
    in >> bmp.filehead.reserved1; //读取两个保留字
    in >> bmp.filehead.reserved2;
    in >> bmp.filehead.offset; //读取偏移量

    //读取位图信息头
    in >> bmp.infohead.size;
    in >> bmp.infohead.width;
    in >> bmp.infohead.height;
    in >> bmp.infohead.planes;
    in >> bmp.infohead.bitCount;
    in >> bmp.infohead.compression;
    in >> bmp.infohead.sizeImage;
    in >> bmp.infohead.XPelsPerMeter;
    in >> bmp.infohead.YPelsPerMeter;
    in >> bmp.infohead.clrUsed;
    in >> bmp.infohead.clrImportant;

    //读取调色板
    qint32 format = WORDtoQuint16(bmp.infohead.bitCount);
    if(format==1){  //黑白图
        bmp.pColorTable = new RGB[2];
        //读入颜色表
        for (int i = 0; i < 2; i++)
        {
            in >> bmp.pColorTable[i].b;
            in >> bmp.pColorTable[i].g;
            in >> bmp.pColorTable[i].r;
            in >> bmp.pColorTable[i].rgbReserved;
        }
    }
    if(format==4){ //4位灰度图  16颜色梯度
        bmp.pColorTable = new RGB[16];
        //读入颜色表
        for (int i = 0; i < 16; i++)
        {
            in >> bmp.pColorTable[i].b;
            in >> bmp.pColorTable[i].g;
            in >> bmp.pColorTable[i].r;
            in >> bmp.pColorTable[i].rgbReserved;
        }
    }
    if(format==8){  //8位灰度图  256颜色梯度
        bmp.pColorTable = new RGB[256];
        //读入颜色表
        for (int i = 0; i < 256; i++)
        {
            in >> bmp.pColorTable[i].b;
            in >> bmp.pColorTable[i].g;
            in >> bmp.pColorTable[i].r;
            in >> bmp.pColorTable[i].rgbReserved;
        }
    }
    // if(format==24) //24位图 真彩色图 无调色板

    //设定颜色位图宽度与高度 从左到右 从上到下
    this->setw(LONGtoQint32(bmp.infohead.width));
    this->seth(LONGtoQint32(bmp.infohead.height));
    assert(w>0 && h>0);

    //存储位图信息
    if(format==1){

    }
    if(format==4){

    }
    if(format==8){

    }
    if(format==24){
        quint32 size = bmp.infohead.sizeImage / 3;
        rgb = new RGB[size];
        for(quint32 i = 0;i<size;i++){
            in>>rgb[i].b;
            in>>rgb[i].g;
            in>>rgb[i].r;
        }
    }

    fp.close();
    return true;
}

/*前十个点的RGB值
45 86 109
44 85 108
49 90 113
47 88 111
44 85 108
49 90 113
44 85 108
29 70 93
44 85 108
41 82 105
43 84 107
*/



