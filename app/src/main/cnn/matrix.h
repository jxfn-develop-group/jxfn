#ifndef _MATRIX_H
    #define _MATRIX_H 2
    struct Matrix{
        int n,m;
        int* arr;
    };
    typedef struct Matrix Matrix;
    struct Matrix matrixInit(int n, int m);
    void matrixSetNum(struct Matrix *a, int n, int m, int val);
    void matrixPrin(struct Matrix a);
    struct Matrix matrixMul(struct Matrix a, struct Matrix b);
    Matrix matrtixDot(Matrix a, Matrix b);
#endif
