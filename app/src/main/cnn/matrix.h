#ifndef _MATRIX_H
    #define _MATRIX_H 2
    struct Matrix{
        int n,m;
        double* arr;
    };
    typedef struct Matrix Matrix;
    void matrixInit(Matrix* mat, int n, int m);
    void matrixSetNum(Matrix *a, int n, int m, double val);
    void matrixPrin(Matrix a);
    void matrixMul(Matrix* a, Matrix b);
    void matrixDot(Matrix* a, Matrix b);
    void matrixAdd(Matrix* a, Matrix b);
    void matrixEqu(Matrix* a, Matrix b);
    void matrixMulNum(Matrix* a, double b);
    void matrixTrans(Matrix* a);
    struct Matrixs{
        int siz;
        Matrix** p_matrix;
    };
    typedef struct Matrixs Matrixs;
    void matrixsInit(Matrixs* mats, int a, int n, int m);
    void matrixsFree(Matrixs* mats);
#endif
