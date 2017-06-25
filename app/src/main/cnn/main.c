#include <time.h>
#include <stdlib.h>
#include <stdio.h>


#include "matrix.h"
#include "neurons.h"
#include "funofneurons.h"
#include "cnnnet.h"
#include "fileofparameter.h"


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
    printf("%d\n",runCnn(&cnn, mat));
    //writeParameter(cnn);

    return 0;
}
