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
    Matrix mat;
    matrixInit(&mat, 32, 32);
    Cnnnet cnn;
    cnnnetInit(&cnn);
    initRand(&cnn);
    //initFromFile(&cnn);
    //printf("%d\n",runCnn(&cnn, mat));
    int tmp = 0;
    scanf("%d",&tmp);
    //printf("%d\n",ans);
    FILE* fpoint = fopen("out1", "r");
    double start = clock();

    int ans = 0;
    double img[28*28] = {};
    for(int i = 0; i < tmp; i++){
        for (int j = 0; j < 28*28; ++j)
        {
            fscanf(fpoint, "%lf", &img[j]);
        }
        readIm(img, &mat);
        for (int k = 0; k < 100; ++k)
        {
            learnCnn(&cnn, mat, ans);
        }
    }

    for (int j = 0; j < 28*28; ++j)
    {
        fscanf(fpoint, "%lf", &img[j]);
    }
    readIm(img, &mat);
    printf("%d\n", runCnn(&cnn, mat));

    printf("%f\n", (clock() - start)/(double)CLOCKS_PER_SEC);
    cnnnetFree(&cnn);
    matrixFree(&mat);
    return 0;
}
