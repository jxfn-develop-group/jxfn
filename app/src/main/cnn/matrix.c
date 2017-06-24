#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

struct Matrix matrixInit(int n, int m){
    struct Matrix a;
    if(n <= 0||m <= 0){
        printf("The matrix size must be positive numbers!\n");
        exit(0);
    }
    a.arr = malloc(n * m * sizeof(double));
    if(a.arr == NULL){
        printf("The matrix can't be created!\n");
        exit(0);
    }
    a.n = n;
    a.m = m;
    return a;
}


void matrixSetNum(struct Matrix *a, int n, int m, double val){
    if(n < 0 ||n >= a->n || m < 0 || m >= a->m){
        printf("array out of range!\n");
        return ;
    }
    a->arr[n * a->m + m] = val;
    //printf("%d %d %d %lf\n",n,m,n*a->m+m,val);
}


void matrixPrin(struct Matrix a){
    for (int i = 0; i < a.n; i++) {
        for (int j = 0; j < a.m; j++) {
            printf("%lf ",a.arr[i * a.m + j]);
        }
        printf("\n");
    }
}


struct Matrix matrixMul(struct Matrix a, struct Matrix b){
    if(a.m != b.n){
        printf("The matrixs can't be multipled!\n");
        exit(0);
    }
    struct Matrix c = matrixInit(a.n, b.m);
    for (int i = 0; i < a.n; i++) {
        for(int j = 0; j < b.m; j++){
            c.arr[i * b.m + j] = 0;
            for(int k = 0; k < a.m; k++){
                c.arr[i * b.m +j] += a.arr[i * a.m + k] * b. arr[k * b.m + j];
            }
        }
    }
    return c;
}


Matrix matrixDot(Matrix a, Matrix b){
    if(a.m != b.m || a.n != b.n){
        printf("The matrixs can't be doted!\n");
        exit(0);
    }
    Matrix c = matrixInit(a.n, b.m);
    for (int i = 0; i < a.n; i++){
        for(int j = 0; j < b.m ; j++){
            c.arr[i * a.m + j] = a.arr[i * a.m + j] * b.arr[i * a.m + j];
        }
    }
    return c;
}


Matrix matrixAdd(Matrix a, Matrix b){
    if(a.m != b.m || a.n != b.n){
        printf("The matrixs can't be doted!\n");
        exit(0);
    }
    Matrix c = matrixInit(a.n, b.m);
    for (int i = 0; i < a.n; i++){
        for(int j = 0; j < a.m ; j++){
            c.arr[i * a.m + j] = a.arr[i * a.m + j] + b.arr[i * a.m + j];
        }
    }
    return c;
}


void matrixAddItself(Matrix* a, Matrix b){
    if(a->m != b.m || a->n != b.n){
        printf("The matrixs can't be doted!\n");
        exit(0);
    }
    for (int i = 0; i < a->n; i++){
        for(int j = 0; j < a->m ; j++){
            a->arr[i * a->m + j] += b.arr[i * a->m + j];
        }
    }
}


Matrix matrixMulNum(Matrix a, double b){
    Matrix c = matrixInit(a.n, a.m);
    for(int i = 0; i < a.n; i++){
        for(int j = 0; j < a.m; j++){
            c.arr[i * c.m + j] = a.arr[i * a.m + j] * b;
        }
    }
    return c;
}


/*
矩阵转置
*/
Matrix matrixTrans(Matrix a){
    Matrix b = matrixInit(a.m, a.n);
    for(int i = 0; i < b.n; i++){
        for(int j = 0; j < b.m; j++){
            b.arr[i * b.m + j] = a.arr[j * a.m + i];
        }
    }
    return b;
}


Matrixs matrixsInit(int a, int n, int m){
    Matrixs b;
    if(a <= 0){
        printf("error when create matrixs!\n");
    }
    b.siz = a;
    b.p_matrix = malloc(a * sizeof(Matrix));
    return b;
}
