#ifndef READER_H
#define READER_H

#include<basic.h>
#include<map>
#include<QFile>
#include<assert.h>


class fileHead
{
public:
    quint16 type;
    quint32	size;
    quint16	reserved1;
    quint16	reserved2;
    quint32	offset;
};

class infoHead
{
public:
    quint32 size;
    qint32  width;
    qint32  height;
    quint16 planes;
    quint16 bitCount;
    quint32 compression;
    quint32 sizeImage; //实际位图数据占用的字节数
    qint32  XPelsPerMeter;
    qint32  YPelsPerMeter;
    quint32 clrUsed;
    quint32 clrImportant;
};

class bitmap
{
private:


public:
   bitmap(){}
   bitmap(QString filename){}
   ~bitmap(){
       delete[] pColorTable;
   }
   fileHead filehead; //文件头
   infoHead infohead;  //信息头
   RGB *pColorTable; //调色板

};


class reader
{
public:
    reader();
    ~reader(){
        delete[] rgb;
    }

    bool readFile(QString );
    RGB* getrgb(){return rgb;}
    void setrgb(RGB* rgb){this->rgb = rgb;}
    void setw(qint32 w){this->w=w;}
    qint32 getw(){return w;}
    void seth(qint32 h){this->h=h;}
    qint32 geth(){return h;}
    map<quint32,quint32> getpiexls(){return piexls;}

private:
    bool readBmp(QString );
    bool readJpg(QString ){return false;}
    bool readPng(QString ){return false;}
    bool readObj(QString ){return false;}

    RGB* rgb;
    qint32 w;
    qint32 h;
    map<quint32,quint32> piexls;
};





#endif // READER_H
