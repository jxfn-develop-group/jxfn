#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


#include "matrix.h"
#include "neurons.h"
#include "funofneurons.h"
#include "cnnnet.h"
#include "fileofparameter.h"
#include "fileofconfig.h"
#include "functioninit.h"


int main(){
    srand(time(0));
    Matrix mat;
    char fn[1111] = "parameter";
    matrixInit(&mat, 32, 32);
    Cnnnet cnn;
    cnnnetInit(&cnn);
    //initRand(&cnn);
    initFromFile(&cnn, fn);
    //functionIni(&cnn);
    FILE* fp;

    int xiangxi = 0;
    int k=0;
    fp= fopen("out2","r");
    int mark[26] = {0};
    int mans = 0;
    for(int ii=0;ii<TESTDATANUM;ii++){
        for(int i = 2;i<30;i++){
            for(int j= 2; j < 30 ; j++){
                fscanf(fp,"%lf",&mat.arr[i * 32 + j]);
            }
        }
        int e= runCnn(&cnn, mat);
        //printf("%d %d\n",e,ii);
        if(e==ii%OUTPUTNUMBER){
            k++;
            if(!mark[e]){
                mark[e]=1;
                mans++;

            }
            //printf("e:%d\n",ii);
        }
        //printf("%d %d\n",ii,e);
        if(xiangxi){
            for(int i = 0; i < OUTPUTNUMBER; i++){
                printf("%f\n", cnn.mats[7].p_matrix[i]->arr[0]);
            }
            printf("----------------------\n");
        }
    }
    printf("%d %f%%\n", k, (double)k/((double)TESTDATANUM) * 100.0);
    printf("%d\n",TESTDATANUM);
    printf("%d\n",mans);
    cnnnetFree(&cnn);
    matrixFree(&mat);
    return 0;
}
