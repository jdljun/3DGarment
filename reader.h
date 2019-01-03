#ifndef READER_H
#define READER_H

#include<bmp.h>
#include<basic.h>

class reader
{
public:
    reader();
    bmp readFile(string );
private:
    bmp readBmp(string );
    bmp readJpg(string ){return NULL;}
    bmp readPng(string ){return NULL;}
    bmp readObj(string );
};

#endif // READER_H
