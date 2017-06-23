#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

struct Matrix matrixInit(int n, int m){
    struct Matrix a;
    a.arr = malloc(n*m);
    if(a.arr == NULL){
        printf("The matrix can't be created!");
        exit(0);
    }
    a.n = n;
    a.m = m;
    return a;
}


void matrixSetNum(struct Matrix *a, int n, int m, int val){
    a->arr[n * a->m + m] = val;
}


void matrixPrin(struct Matrix a){
    for (int i = 0; i < a.n; i++) {
        for (int j = 0; j < a.m; j++) {
            printf("%d ",a.arr[i * a.m + j]);
        }
        printf("\n");
    }
}


struct Matrix matrixMul(struct Matrix a, struct Matrix b){
    if(a.m != b.n){
        printf("The matrixs can't be multipled!");
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


Matrix matrtixDot(Matrix a, Matrix b){
    if(a.m != b.m || a.n != b.n){
        printf("The matrixs can't be doted!");
        exit(0);
    }
    Matrix c;
    for (int i = 0; i < a.n; i++){
        for(int j = 0; j < b.n ; j++){
            c.arr[i * a.m + j] = a.arr[i * a.m + j] * b.arr[i * a.m + j];
        }
    }
    return c;
}
