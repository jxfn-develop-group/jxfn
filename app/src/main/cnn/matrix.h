#include "fileofconfig.h"


#ifndef _MATRIX_H
    #define _MATRIX_H 2
    struct Matrix{
        int n,m;
        double* arr;
    };
    typedef struct Matrix Matrix;
    void matrixFree(Matrix* mat);
    void matrixInit(Matrix* mat, int n, int m);
    void matrixSetNum(Matrix *a, int n, int m, double val);
    void matrixPrin(Matrix a);
    void matrixMul(Matrix* a, Matrix* b);
    void matrixDot(Matrix* a, Matrix* b);
    void matrixAdd(Matrix* a, Matrix* b);
    void matrixAddNum(Matrix* a, double b);
    void matrixEqu(Matrix* a, Matrix* b);
    void matrixMulNum(Matrix* a, double b);
    void matrixTrans(Matrix* a);
    void matrixConv(Matrix* a, Matrix* b, Matrix* c);
    void matrixFunction(Matrix* a,double (*p_fun)(double, double), double b);
    void matrixSample(Matrix* a, Matrix* b, int n, int m,
        double (*p_fun)(Matrix));//矩阵采样函数
    void matrixSwap(Matrix* a, Matrix* b);
    struct Matrixs{
        int siz;
        Matrix** p_matrix;
    };
    typedef struct Matrixs Matrixs;
    void matrixsInit(Matrixs* mats, int a, int n, int m);
    void matrixsFree(Matrixs* mats);
    void matrixsEqu(Matrixs* a, Matrixs* b);
    void matrixsClear(Matrixs* a);
#endif
