#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "cnnnet.h"
#include "funofneurons.h"
#include "fileofparameter.h"


void cnnnetInit(Cnnnet* net1){
    matrixsInit(&net1->mats[0], 1, 32, 32);
    matrixsInit(&net1->mats[1], 6, 28, 28);
    matrixsInit(&net1->mats[2], 6, 14, 14);
    matrixsInit(&net1->mats[3], 16, 10, 10);
    matrixsInit(&net1->mats[4], 16, 5, 5);
    matrixsInit(&net1->mats[5], 120, 1, 1);
    matrixsInit(&net1->mats[6], 84, 1, 1);
    matrixsInit(&net1->mats[7], 10, 1, 1);

    neuronssInit(&net1->level[0], 6);
    neuronssInit(&net1->level[1], 6);
    neuronssInit(&net1->level[2], 16);
    neuronssInit(&net1->level[3], 16);
    neuronssInit(&net1->level[4], 120);
    neuronssInit(&net1->level[5], 84);
    neuronssInit(&net1->level[6], 10);
}


void cnnnetFree(Cnnnet* net1){
    matrixsFree(&net1->mats[0]);
    matrixsFree(&net1->mats[1]);
    matrixsFree(&net1->mats[2]);
    matrixsFree(&net1->mats[3]);
    matrixsFree(&net1->mats[4]);
    matrixsFree(&net1->mats[5]);
    matrixsFree(&net1->mats[6]);
    matrixsFree(&net1->mats[7]);

    neuronssFree(&net1->level[0]);
    neuronssFree(&net1->level[1]);
    neuronssFree(&net1->level[2]);
    neuronssFree(&net1->level[3]);
    neuronssFree(&net1->level[4]);
    neuronssFree(&net1->level[5]);
    neuronssFree(&net1->level[6]);
}


void initFromFile(Cnnnet* net1){
    initRand(net1);
    readPara(net1);
}


void initRand(Cnnnet* net1){
    for(int i = 0; i < 6; i++){
        neuronsInit(net1->level[0].neu[i],  5, 5, getRand());
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < 5; k++){
                net1->level[0].neu[i]->weights.arr[j * 5 + k] = getRand();
            }
        }
        net1->level[0].neu[i]->p_activateFunction = funOfLevel0;
    }
    for(int i = 0; i < 6; i++){
        net1->level[1].neu[i]->p_activateFunction = funOfLevel1;
        net1->level[1].neu[i]->p_baseFunction = maxOfMatrix;
        net1->level[1].neu[i]->bias = getRand();
    }
    for(int i = 0; i < 16; i++){
        neuronsInit(net1->level[2].neu[i], 5, 5, getRand());
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < 5; k++){
                net1->level[2].neu[i]->weights.arr[j * 5 + k] = getRand();
            }
        }
        net1->level[2].neu[i]->p_activateFunction = funOfLevel2;
    }
    for(int i = 0; i < 16; i++){
        net1->level[3].neu[i]->p_activateFunction = funOfLevel3;
        net1->level[3].neu[i]->p_baseFunction = maxOfMatrix;
        net1->level[3].neu[i]->bias = getRand();
    }
    for(int i = 0; i < 120; i++){
        neuronsInit(net1->level[4].neu[i], 5, 5, getRand());
        net1->level[4].neu[i]->p_activateFunction = funOfLevel4;
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < 5; k++){
                net1->level[4].neu[i]->weights.arr[j * 5 + k] = getRand();
            }
        }
    }
    for(int i = 0; i < 84; i++){
        neuronsInit(net1->level[5].neu[i], 1, 120, getRand());
        net1->level[5].neu[i]->weights.arr[0] = getRand();
        net1->level[5].neu[i]->p_activateFunction = funOfLevel0;
        //每层的激活函数相同
    }
    for(int i = 0; i < 10; i++){
        neuronsInit(net1->level[6].neu[i], 1, 84, getRand());
        net1->level[6].neu[i]->weights.arr[0] = getRand();
        net1->level[6].neu[i]->p_activateFunction = funOfLevel0;
    }
}


void runOfLayerOne(Cnnnet *net1){
    for (int i = 0; i < 6; i++){
        matrixConv(net1->mats[1].p_matrix[i], net1->mats[0].p_matrix[0],
            &(net1->level[0].neu[i]->weights));
        matrixAddNum(net1->mats[1].p_matrix[i], net1->level[0].neu[i]->bias);
        matrixFunction(net1->mats[1].p_matrix[i],
            net1->level[0].neu[i]->p_activateFunction, 0.0);
    }
}


void runOfLayerTwo(Cnnnet *net1){
    for(int i = 0; i < 6; i++){
        matrixSample(net1->mats[2].p_matrix[i],
            *net1->mats[1].p_matrix[i], 2, 2, maxnumOfMatrix);
    }
}


void runOfLayerThree(Cnnnet *net1){
    Matrixs tmat;
    matrixsInit(&tmat, 16, 14, 14);
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 3; j++){
            matrixAdd(tmat.p_matrix[i],
                *(net1->mats[2].p_matrix[(i+j)%6]));
        }
    }
    for(int i = 6; i < 12; i++){
        for(int j = 0; j < 4; j++){
            matrixAdd(tmat.p_matrix[i],
                *(net1->mats[2].p_matrix[(i+j)%6]));
        }
    }
    for(int i = 12; i < 15; i++){
        for(int j = 0; j < 5; j++){
            if(j == 2){continue;}
            matrixAdd(tmat.p_matrix[i],
                *(net1->mats[2].p_matrix[(i+j)%6]));
        }
    }
    for(int i = 0; i < 6; i++){
        matrixAdd(tmat.p_matrix[15],
            *(net1->mats[2].p_matrix[i]));
    }
    /*
    net1->mats[3].p_matrix[i] 必须初始化为零
    */
    for (int i = 0; i < 16; i++){
        matrixConv(net1->mats[3].p_matrix[i], tmat.p_matrix[i],
            &net1->level[2].neu[i]->weights);
        matrixFunction(net1->mats[3].p_matrix[i],
            net1->level[2].neu[i]->p_activateFunction, 0.0);
    }
    matrixsFree(&tmat);
}


void runOfLayerFour(Cnnnet *net1){
    for(int i = 0; i < 16; i++){
        matrixSample(net1->mats[4].p_matrix[i], *net1->mats[3].p_matrix[i],
            2, 2, maxnumOfMatrix);
    }
}


void runOfLayerFive(Cnnnet *net1){
    Matrix tmat;
    matrixInit(&tmat, 5, 5);
    for(int i = 0; i < 16; i++){
        matrixAdd(&tmat, *net1->mats[4].p_matrix[i]);
    }
    for(int i = 0; i < 120; i++){
        matrixConv(net1->mats[5].p_matrix[i], &tmat,
            &net1->level[4].neu[i]->weights);
        net1->mats[5].p_matrix[i]->arr[0] =
            net1->level[4].neu[i]->p_activateFunction
            (net1->mats[5].p_matrix[i]->arr[0], 0.0);
    }
    matrixFree(&tmat);
}


void runOfLayerSix(Cnnnet *net1){
    for(int i = 0; i < 84; i++){
        net1->mats[6].p_matrix[i]->arr[0] = 0.0;
        for(int j = 0; j < 120; j++){
            net1->mats[6].p_matrix[i]->arr[0] +=
            net1->mats[5].p_matrix[j]->arr[0] *
            net1->level[5].neu[i]->weights.arr[j];
        }
        net1->mats[6].p_matrix[i]->arr[0] =
            net1->level[5].neu[i]->p_activateFunction
            (net1->mats[6].p_matrix[i]->arr[0], 0.0);
    }
}


void runOfLayerSeven(Cnnnet *net1){
    for(int i = 0; i < 10; i++){
        net1->mats[7].p_matrix[i]->arr[0] = 0.0;
        for(int j = 0; j < 84; j++){
            net1->mats[7].p_matrix[i]->arr[0] +=
            net1->mats[6].p_matrix[j]->arr[0] *
            net1->level[6].neu[i]->weights.arr[j];
        }
        net1->mats[7].p_matrix[i]->arr[0] =
            net1->level[6].neu[i]->p_activateFunction
            (net1->mats[7].p_matrix[i]->arr[0], 0.0);
    }
}


void learnOfLayerOne(Cnnnet *net1){

}


void learnOfLayerTwo(Cnnnet *net1){

}


void learnOfLayerThree(Cnnnet *net1){

}


void learnOfLayerFour(Cnnnet *net1){

}


void learnOfLayerFive(Cnnnet *net1){

}


void learnOfLayerSix(Cnnnet *net1){

}


void learnOfLayerSeven(Cnnnet *net1){

}


int runCnn(Cnnnet* net1, Matrix image){
    int ans = 0;
    matrixEqu(net1->mats[0].p_matrix[0], image);
    // int asserti = 0;
    // printf("=%d=\n", asserti++);
    runOfLayerOne(net1);
    // printf("=%d=\n", asserti++);
    runOfLayerTwo(net1);
    // printf("=%d=\n", asserti++);
    runOfLayerThree(net1);
    // printf("=%d=\n", asserti++);
    runOfLayerFour(net1);
    // printf("=%d=\n", asserti++);
    runOfLayerFive(net1);
    // printf("=%d=\n", asserti++);
    runOfLayerSix(net1);
    //printf("=%d=\n", asserti++);
    runOfLayerSeven(net1);
    //printf("=%d=\n", asserti++);
    for(int i = 1; i < 10; i++){
        if(net1->mats[7].p_matrix[i]->arr[0] >
            net1->mats[7].p_matrix[ans]->arr[0]){
            ans = i;
        }
    }
    return ans;
}


void writeParameter(Cnnnet net1){
    writePara(net1);
}


void learn(Cnnnet* net1, Matrix image, double answer){
    runCnn(net1, image);
    learnOfLayerSeven(net1);
    learnOfLayerSix(net1);
    learnOfLayerFive(net1);
    learnOfLayerFour(net1);
    learnOfLayerThree(net1);
    learnOfLayerTwo(net1);
    learnOfLayerOne(net1);
}
