#ifndef _MATRIX_H
    #define _MATRIX_H 2
    struct Matrix{
        int n,m;
        double* arr;
    };
    typedef struct Matrix Matrix;
    struct Matrix matrixInit(int n, int m);
    void matrixSetNum(struct Matrix *a, int n, int m, double val);
    void matrixPrin(struct Matrix a);
    struct Matrix matrixMul(struct Matrix a, struct Matrix b);
    Matrix matrixDot(Matrix a, Matrix b);
    Matrix matrixAdd(Matrix a, Matrix b);
    Matrix matrixMulNum(Matrix a, double b);
    Matrix matrixTrans(Matrix a);
#endif
