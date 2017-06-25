#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

void matrixInit(Matrix* mat, int n, int m){
    if(n <= 0||m <= 0){
        printf("The matrix size must be positive numbers!\n");
        exit(0);
    }
    mat->arr = malloc(n * m * sizeof(double));
    if(mat->arr == NULL){
        printf("The matrix can't be created!\n");
        exit(0);
    }
    mat->n = n;
    mat->m = m;
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


void matrixEqu(Matrix* a, Matrix b){
    a->n = b.n;
    a->m = b.m;
    free(a->arr);
    a->arr = malloc(b.n * b.m * sizeof(double));
    for(int i = 0; i < b.n; i++){
        for(int j = 0; j < b.m; j++){
            a->arr[i * b.m + j] = b.arr[i * b.m + j];
        }
    }
}
void matrixMul(Matrix* a, Matrix b){
    if(a->m != b.n){
        printf("The matrixs can't be multipled!\n");
        exit(0);
    }
    Matrix c;
    matrixInit(&c, a->n, b.m);
    for (int i = 0; i < a->n; i++) {
        for(int j = 0; j < b.m; j++){
            c.arr[i * b.m + j] = 0;
            for(int k = 0; k < a->m; k++){
                c.arr[i * b.m +j] += a->arr[i * a->m + k] * b. arr[k * b.m +j];
            }
        }
    }
    matrixEqu(a , c);
    free(c.arr);
}


void matrixDot(Matrix* a, Matrix b){
    if(a->m != b.m || a->n != b.n){
        printf("The matrixs can't be doted!\n");
        exit(0);
    }
    Matrix c;
    matrixInit(&c, a->n, b.m);
    for (int i = 0; i < a->n; i++){
        for(int j = 0; j < b.m ; j++){
            c.arr[i * a->m + j] = a->arr[i * b.m + j] * b.arr[i * b.m + j];
        }
    }
    matrixEqu(a, c);
    free(c.arr);
}


void matrixAdd(Matrix* a, Matrix b){
    if(a->m != b.m || a->n != b.n){
        printf("The matrixs can't be doted!\n");
        exit(0);
    }
    for (int i = 0; i < a->n; i++){
        for(int j = 0; j < a->m ; j++){
            a->arr[i * a->m + j] += b.arr[i * b.m + j];
        }
    }
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


void matrixMulNum(Matrix* a, double b){
    for(int i = 0; i < a->n; i++){
        for(int j = 0; j < a->m; j++){
            a->arr[i * a->m + j] *= b;
        }
    }
}


/*
矩阵转置
*/
void matrixTrans(Matrix* a){
    Matrix b;
    matrixInit(&b, a->m, a->n);
    for(int i = 0; i < b.n; i++){
        for(int j = 0; j < b.m; j++){
            b.arr[i * b.m + j] = a->arr[j * a->m + i];
        }
    }
    matrixEqu(a, b);
    free(b.arr);
}


void matrixsInit(Matrixs* mats, int a, int n, int m){
    if(a <= 0){
        printf("error when create matrixs!\n");
    }
    mats->siz = a;
    mats->p_matrix = malloc(a * sizeof(Matrix*));
    for (int i = 0; i < a; i++){
        mats->p_matrix[i] = malloc(2 * sizeof(int) +  sizeof(Matrix*));
        mats->p_matrix[i]->n = n;
        mats->p_matrix[i]->m = m;
        mats->p_matrix[i]->arr = malloc(n * m * sizeof(double));
    }
}
