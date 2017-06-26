#include "matrix.h"
#include "fileofconfig.h"


#ifndef _FUNOFNEURONS_H
    #define _FUNOFNEURONS_H 2
    double maxOfMatrix(Matrix a, Matrix b, double c);
    double maxnumOfMatrix(Matrix a);
    double maxd(double a, double b);//两个double中较大值
    double getRand();//得到一个浮点随机数，范围-1~1,精度1/300;
    double getRandRange(int a);
    double funOfLevel0(double a, double b);
    double funOfLevel1(double a, double b);
    double funOfLevel2(double a, double b);
    double funOfLevel3(double a, double b);
    double funOfLevel4(double a, double b);
    //double sigmoid(double a, double b);
    double LReLu(double a);
    double LReLuDer(double a);
#endif
