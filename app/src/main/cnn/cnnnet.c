#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "cnnnet.h"
#include "funofneurons.h"


void cnnnetInit(Cnnnet* net1){
    net1->mats[0] = matrixsInit(1, 32, 32);
    net1->mats[1] = matrixsInit(6, 28, 28);
    net1->mats[2] = matrixsInit(6, 14, 14);
    net1->mats[3] = matrixsInit(16, 10, 10);
    net1->mats[4] = matrixsInit(16, 5, 5);
    net1->mats[5] = matrixsInit(120, 1, 1);
    net1->mats[6] = matrixsInit(84, 1, 1);
    net1->mats[7] = matrixsInit(10, 1, 1);

    net1->level[0] = neuronssInit(6);
    net1->level[1] = neuronssInit(6);
    net1->level[2] = neuronssInit(111);
    net1->level[3] = neuronssInit(16);
    net1->level[4] = neuronssInit(111);


}


void initFromFile(Cnnnet* net1){
    FILE* fp = fopen("parameter","r");
    if (fp == NULL){
        printf("The file of init doesn't exit!\n");
        exit(0);
    }
    fclose(fp);
}


void initRand(Cnnnet* net1){
    srand(time(0));

}


void runOfLayerOne(Cnnnet *net1){

}


void runOfLayerTwo(Cnnnet *net1){

}


void runOfLayerThree(Cnnnet *net1){

}


void runOfLayerFour(Cnnnet *net1){

}


void runOfLayerFive(Cnnnet *net1){

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


int runCnn(Cnnnet* net1, Matrix image){
    int ans = 0;
    net1->mats[0].p_matrix[0] = matrixMulNum(image , 1.0);
    runOfLayerOne(net1);
    runOfLayerTwo(net1);
    runOfLayerThree(net1);
    runOfLayerFour(net1);
    runOfLayerFive(net1);
    return ans;
}


void writeParameter(Cnnnet net1){
    FILE* fp = fopen("parameter","w");
    fclose(fp);
}


void learn(Cnnnet* net1, Matrix image, double answer){
    runCnn(net1, image);
    learnOfLayerFive(net1);
    learnOfLayerFour(net1);
    learnOfLayerThree(net1);
    learnOfLayerTwo(net1);
    learnOfLayerOne(net1);
}
