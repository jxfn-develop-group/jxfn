#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "matrix.h"

void matrixInit(Matrix* mat, int n, int m){
    if(n < 0||m < 0){
        printf("The matrix size must be positive numbers!\n");
        exit(0);
    }
    mat->arr = (double*)(calloc(n * m, sizeof(double)));
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
}


void matrixPrin(struct Matrix a){
    for (int i = 0; i < a.n; i++) {
        for (int j = 0; j < a.m; j++) {
            printf("%f ",a.arr[i * a.m + j]);
        }
        printf("\n");
    }
}


void matrixEqu(Matrix* a, Matrix* b){
    if(a->arr != NULL){
        free(a->arr);
    }
    a->n = b->n;
    a->m = b->m;
    a->arr = (double*)(calloc(b->n * b->m, sizeof(double)));
    for(int i = 0; i < b->n; i++){
        for(int j = 0; j < b->m; j++){
            a->arr[i * b->m + j] = b->arr[i * b->m + j];
        }
    }
}


void matrixMul(Matrix* a, Matrix* b){
    if(a->m != b->n){
        printf("The matrixs can't be multipled!\n");
        exit(0);
    }
    Matrix c;
    matrixInit(&c, a->n, b->m);
    for (int i = 0; i < a->n; i++) {
        for(int j = 0; j < b->m; j++){
            c.arr[i * b->m + j] = 0;
            for(int k = 0; k < a->m; k++){
                c.arr[i * b->m +j] += a->arr[i * a->m + k] * b->arr[k *b->m+j];
            }
        }
    }
    matrixEqu(a , &c);
    free(c.arr);
}


void matrixDot(Matrix* a, Matrix* b){
    if(a->m != b->m || a->n != b->n){
        printf("The matrixs can't be doted!\n");
        exit(0);
    }
    Matrix c;
    matrixInit(&c, a->n, b->m);
    for (int i = 0; i < a->n; i++){
        for(int j = 0; j < b->m ; j++){
            c.arr[i * a->m + j] = a->arr[i * b->m + j] * b->arr[i * b->m + j];
        }
    }
    matrixEqu(a, &c);
    free(c.arr);
}


void matrixAdd(Matrix* a, Matrix* b){
    if(a->m != b->m || a->n != b->n){
        printf("The matrixs can't be doted!\n");
        exit(0);
    }
    for (int i = 0; i < a->n; i++){
        for(int j = 0; j < a->m ; j++){
            a->arr[i * a->m + j] += b->arr[i * b->m + j];
        }
    }
}


void matrixAddNum(Matrix* a, double b){
    for(int i = 0; i < a->n; i++){
        for(int j = 0; j < a->m; j++){
            a->arr[i * a->m + j] += b;
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
    matrixEqu(a, &b);
    free(b.arr);
}


/*矩阵卷积*/
void matrixConv(Matrix* a, Matrix* b,Matrix* c){
    if(a->n != b->n - c->n + 1 || a->m != b->m - c->m + 1){
        printf("Can't conv!\n");
        return;
    }
    for(int i = 0; i < a->n; i++){
        for(int j = 0; j < a->m; j++){
            a->arr[i * a->m + j] = 0.0;
            for(int ii = 0; ii < c->n; ii++){
                for(int jj = 0; jj < c->m; jj++){
                    a->arr[i * a->m + j] += b->arr[(i + ii) * b->m + j + jj] *
                        c->arr[ii * c->m + jj];
                }
            }
        }
    }
}


void matrixsInit(Matrixs* mats, int a, int n, int m){
    if(a <= 0){
        printf("error when create matrixs!\n");
    }
    mats->siz = a;
    mats->p_matrix = (Matrix**)(calloc(a, sizeof(Matrix*)));
    if(mats->p_matrix == NULL){
        printf("matrixs init error!\n");
        exit(0);
    }
    for (int i = 0; i < a; i++){
        mats->p_matrix[i] = (Matrix*)(calloc(1,
            2 * sizeof(int) + sizeof(Matrix*)));
        if(mats->p_matrix[i] == NULL){
            printf("matrixs p_matrix init error!\n");
            exit(0);
        }
        mats->p_matrix[i]->n = n;
        mats->p_matrix[i]->m = m;
        mats->p_matrix[i]->arr = (double*)(calloc(n * m, sizeof(double)));
        if(mats->p_matrix[i]->arr == NULL){
            printf("matrixs init arr error!\n");
            exit(0);
        }
    }
}


void matrixFree(Matrix* mat){
    if(mat->arr != NULL){
        free(mat->arr);
    }
    mat->n = mat->m = 0;
}


void matrixsFree(Matrixs* mats){
    if(mats->p_matrix != NULL){
        for(int i = 0; i < mats->siz; i++){
            matrixFree(mats->p_matrix[i]);
            if(mats->p_matrix[i] != NULL){
                free(mats->p_matrix[i]);
            }
        }
        free(mats->p_matrix);
    }
    mats->siz = 0;
}


void matrixFunction(Matrix* a,double (*p_fun)(double, double), double b){
    for(int i = 0; i < a->n; i++){
        for(int j = 0; j < a->m; j++){
            a->arr[i * a->m + j] = p_fun(a->arr[i * a->m +j], b);
        }
    }
}


void matrixSample(Matrix* a, Matrix *b, int n, int m, double (*p_fun)(Matrix)){
    if(a->n * n != b->n ||a->m * m != b->m){
        printf("Can't matrixSample!\n");
        return;
    }
    Matrix mat;
    matrixInit(&mat, n, m);
    for(int i = 0; i < a->n; i++){
        for(int j = 0; j < a->m; j++){
            for(int ii = 0; ii < n; ii++){
                for(int jj = 0; jj < m; jj++){
                    mat.arr[ii * m + jj] =
                        b->arr[(i * n + ii) * b->m + j * m +jj];
                }
            }
            a->arr[i * a->m +j] = p_fun(mat);
        }
    }
    matrixFree(&mat);
}


void matrixSwap(Matrix* a, Matrix* b){
    Matrix c;
    matrixEqu(&c, a);
    matrixEqu(a, b);
    matrixEqu(b, &c);
    matrixFree(&c);
}


void matrixsEqu(Matrixs* a, Matrixs* b){
    matrixsFree(a);
    if(b->siz == 0){
        return ;
    }
    matrixsInit(a, b->siz, b->p_matrix[0]->n, b->p_matrix[0]->m);
    for(int i = 0; i < b->siz; i++){
        matrixEqu(a->p_matrix[i], b->p_matrix[i]);
    }
}


void matrixsClear(Matrixs* a){
    for(int i = 0; i < a->siz; i++){
        for(int j = 0; j < a->p_matrix[i]->n; j++){
            int tmp = a->p_matrix[i]->m;
            for(int k = 0; k < tmp; k++){
                a->p_matrix[i]->arr[j * tmp + k] = 0.0;
            }
        }
    }
}


int matrixSameSize(Matrix* a, Matrix* b){
    return a->n == b->n && a->m == b->m;
}


void matrixRestore(Matrix* a, Matrix* b, Matrix* c, int n, int m){
    if(b->n * n != a->n || b->m * m != a->m || a->n != c->n || a->m != c->m){
        printf("there is an erros in matrixRestore!\n");
        return ;
    }
    for(int i = 0; i < b->n; i++){
        for(int j = 0; j < b->m; j++){
            if(fabs(b->arr[i * b->m + j]) < EPS ){
                continue;
            }
            int posx = 0, posy = 0;
            for(int ii = 0; ii < n; ii++){
                for(int jj = 0; jj < m; jj++){
                    if(a->arr[(i * n + posx) * a->m + j * m + posy] <
                            a->arr[(i * n + ii) * a->m + j * m + jj]){
                        posx = ii;
                        posy = jj;
                    }
                    c->arr[(i * n + ii) * a->m + j * m + jj] = 0.0;
                }
            }
            c->arr[(i * n + posx) * a->m + j * m + posy] =
                b->arr[i * b->m +j];
        }
    }
}
