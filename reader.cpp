#include "reader.h"

reader::reader()
{

}

bmp reader::readFile(string fileName){
    if(strstr(fileName,".bmp")!=NULL)
        return readBmp(fileName);
    else if(strstr(fileName,".jpg")!=NULL)
        return readJpg(fileName);
    else if(strstr(fileName,".png")!=NULL)
        return readPng(fileName);
    return NUll;
}

bmp reader::readBmp(string fileName){

}

bmp reader::readObj(string fileName){

}
