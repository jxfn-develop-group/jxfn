#include "matrix.h"
#include "fileofconfig.h"
#include "neurons.h"


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
    double sigmoid(double a, double b);
    double sigmoidDer(double a, double b);
    void sigmoidRT(double* pre, double * nex, double* w, double input,
        double output, double* bias);
    //反向传播时进行修改
    double LReLu(double a);
    double LReLuDer(double a);
    void LReLuRT(double* pre, double* nex, double* w, double input,
        double output, double* bias);
    void LReLuRTNoChange(double* pre, double* nex, double* w, double input,
        double output, double* bias, double* wc);
    void convRT(Matrix* pre, Matrix* nex, Neurons* neu, Matrix* input,
        Matrix* output, void(*p_fun)(double*, double*, double *, double,
            double, double*, double*));
    //卷积反向传递函数
    double minDouble(double a, double b);
    void gradAdjust(Matrixs* mat);
    void biasAdjust(double* tmpbias, double* bias);
    void weightsAdjust(Matrix* pre, Matrix* now);
#endif
