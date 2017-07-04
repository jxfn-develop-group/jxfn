#include <time.h>
#include <stdlib.h>
#include <stdio.h>


#include "matrix.h"
#include "neurons.h"
#include "funofneurons.h"
#include "cnnnet.h"
#include "fileofparameter.h"
#include "fileofconfig.h"


int main(){
    srand(time(0));
    char s[111] = "out1";
    Matrix mat;
    matrixInit(&mat, 32, 32);
    readIm(s, &mat);
    Cnnnet cnn;
    cnnnetInit(&cnn);
    initRand(&cnn);
    //initFromFile(&cnn);
    //printf("%d\n",runCnn(&cnn, mat));
    //double start = clock();
    int tmp;
    //scanf("%d",&tmp);
    tmp = 5;
    int ans = 1;
    for(int i = 0; i< tmp;i++){
        // printf("%d %d\n",i,runCnn(&cnn,mat));
        ans = runCnn(&cnn, mat);
    }
    for(int i = 0; i < 10; i++){
        printf("%f\n", cnn.mats[7].p_matrix[i]->arr[0]);
    }
    //printf("%d\n",ans);
    //printf("%d\n", (int)sizeof(double));
    //printf("%f\n", (clock() - start)/(double)CLOCKS_PER_SEC);
    for(int i = 0; i < 2; i++){
        learnCnn(&cnn, mat, 1);
    }
    printf("%d\n",runCnn(&cnn, mat));
    for(int i = 0; i < 10; i++){
        printf("%f\n", cnn.mats[7].p_matrix[i]->arr[0]);
    }
    cnnnetFree(&cnn);
    matrixFree(&mat);
    return 0;
}
