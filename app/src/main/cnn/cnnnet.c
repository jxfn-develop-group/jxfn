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
    net1->level[2] = neuronssInit(16);
    net1->level[3] = neuronssInit(16);
    net1->level[4] = neuronssInit(120);
    net1->level[5] = neuronssInit(84);
    net1->level[6] = neuronssInit(10);
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
    for(int i = 0; i < 6; i++){
        net1->level[0].neu[i] = neuronsInit(5, 5, getRand());
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < 5; k++){
                net1->level[0].neu[i].weights.arr[j * 5 + k] = getRand();
            }
        }
        net1->level[0].neu[i].p_activateFunction = funOfLevel0;
    }
    for(int i = 0; i < 6; i++){
        net1->level[1].neu[i].p_activateFunction = funOfLevel1;
        net1->level[1].neu[i].p_baseFunction = maxOfMatrix;
        net1->level[1].neu[i].bias = getRand();
    }
    for(int i = 0; i < 16; i++){
        net1->level[2].neu[i] = neuronsInit(5, 5, getRand());
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < 5; k++){
                net1->level[2].neu[i].weights.arr[j * 5 + k] = getRand();
            }
        }
        net1->level[2].neu[i].p_activateFunction = funOfLevel2;
    }
    for(int i = 0; i < 16; i++){
        net1->level[3].neu[i].p_activateFunction = funOfLevel3;
        net1->level[3].neu[i].p_baseFunction = maxOfMatrix;
        net1->level[3].neu[i].bias = getRand();
    }
    for(int i = 0; i < 120; i++){
        net1->level[4].neu[i] = neuronsInit(5, 5, getRand());
        net1->level[4].neu[i].p_activateFunction = funOfLevel4;
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < 5; k++){
                net1->level[4].neu[i].weights.arr[j * 5 + k] = getRand();
            }
        }
    }
    for(int i = 0; i < 84; i++){
        net1->level[5].neu[i] = neuronsInit(1, 120, getRand());
        net1->level[5].neu[i].weights.arr[0] = getRand();
    }
    for(int i = 0; i < 10; i++){
        net1->level[6].neu[i] = neuronsInit(1, 84, getRand());
        net1->level[6].neu[i].weights.arr[0] = getRand();
    }
}


void runOfLayerOne(Cnnnet *net1){
    for (int i = 0; i < 6; i++){
        for(int j = 0; j < 28; j++){
            for(int k = 0; k < 28; k++){
                net1->mats[1].p_matrix[i].arr[j * 28 + k] = 0.0;
                for(int ii = 0; ii < 5; ii++){
                    for(int jj = 0; jj < 5; jj++){
                        net1->mats[1].p_matrix[i].arr[j * 28 + k] +=
                        net1->level[0].neu[i].weights.arr[ii * 5 + jj] *
                        net1->mats[0].p_matrix[i].arr[(j + ii) * 32 + k + jj];
                    }
                }
                net1->mats[1].p_matrix[i].arr[j * 28 + k] +=
                    net1->level[0].neu[i].bias;
                net1->mats[1].p_matrix[i].arr[j * 28 + k] =
                    net1->level[0].neu[i].p_activateFunction
                    (net1->mats[1].p_matrix[i].arr[j * 28 + k], 0.0);
            }
        }
    }
}


void runOfLayerTwo(Cnnnet *net1){
    Matrix tmp = matrixInit(2, 2);
    Matrix tmp1 = matrixInit(1, 1);
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 14; j++){
            for(int k = 0; k < 14; k++){
                for(int ii = 0; ii < 2; ii++){
                    for(int jj = 0; jj < 2; jj++){
                        tmp.arr[ii * 2 + jj] =
                        net1->mats[1].p_matrix[i].arr[(j*2 + ii) * 28 + k+jj];
                    }
                }
                net1->mats[2].p_matrix[i].arr[j * 14 + k] =
                net1->level[1].neu[i].p_baseFunction(tmp, tmp1, 0.0);

            }
        }
    }
}


void runOfLayerThree(Cnnnet *net1){
    Matrixs tmat = matrixsInit(16, 14, 14);
    for (int i = 0; i < 16; i++){
        for(int j = 0; j < 10; j++){
            for (int k = 0; k < 10; k++){
                net1->mats[3].p_matrix[i].arr[j * 10 + k] = 0.0;
            }
        }
        for(int j = 0; j < 14; j++){
            for(int k = 0; k < 14; k++){
                net1->mats[3].p_matrix[i].arr[j * 14 + k] = 0.0;
            }
        }
    }
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 3; j++){
            matrixAddItself(&tmat.p_matrix[i],net1->mats[2].p_matrix[(i+j)%6]);
        }
    }
    for(int i = 6; i < 12; i++){
        for(int j = 0; j < 4; j++){
            matrixAddItself(&tmat.p_matrix[i],net1->mats[2].p_matrix[(i+j)%6]);
        }
    }
    for(int i = 12; i < 15; i++){
        for(int j = 0; j < 5; j++){
            if(j == 2){continue;}
            matrixAddItself(&tmat.p_matrix[i],net1->mats[2].p_matrix[(i+j)%6]);
        }
    }
    for(int i = 0; i < 6; i++){
        matrixAddItself(&tmat.p_matrix[15], net1->mats[2].p_matrix[i]);
    }
    for (int i = 0; i < 16; i++){
        for(int j = 0; j < 10; j++){
            for(int k = 0; k < 10; k++){
                net1->mats[3].p_matrix[i].arr[j * 10 + k] = 0.0;
                for(int ii = 0; ii < 5; ii++){
                    for(int jj = 0; jj < 5; jj++){
                        net1->mats[3].p_matrix[i].arr[j * 10 + k] +=
                        net1->level[2].neu[i].weights.arr[ii * 5 + jj] *
                        tmat.p_matrix[i].arr[(j + ii) * 14 + k + jj];
                    }
                }
                net1->mats[3].p_matrix[i].arr[j * 10 + k] =
                    net1->level[2].neu[i].p_activateFunction
                    (net1->mats[3].p_matrix[i].arr[j * 10 +k], 0.0);
            }
        }
    }
}


void runOfLayerFour(Cnnnet *net1){
    Matrix tmp = matrixInit(2, 2);
    Matrix tmp1 = matrixInit(1, 1);
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < 5; k++){
                for(int ii = 0; ii < 2; ii++){
                    for(int jj = 0; jj < 2; jj++){
                        tmp.arr[ii * 2 + jj] =
                        net1->mats[3].p_matrix[i].arr[(j*2 + ii) * 10 + k+jj];
                    }
                }
                net1->mats[4].p_matrix[i].arr[j * 5 + k] =
                net1->level[3].neu[i].p_baseFunction(tmp, tmp1, 0.0);
            }
        }
    }
}


void runOfLayerFive(Cnnnet *net1){
    Matrix tmat = matrixInit(5, 5);
    for(int i = 0; i < 120; i++){
        net1->mats[5].p_matrix[i].arr[0] = 0.0;
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < 5; k++){
                net1->mats[5].p_matrix[i].arr[0] +=
                    net1->level[4].neu[i].weights.arr[j * 5 +k] *
                    tmat.arr[j * 5 +k];
            }
        }
        net1->mats[5].p_matrix[i].arr[0] =
            net1->level[4].neu[i].p_activateFunction
            (net1->mats[5].p_matrix[i].arr[0], 0.0);
    }
}


void runOfLayerSix(Cnnnet *net1){
    for(int i = 0; i < 84; i++){
        net1->mats[6].p_matrix[i].arr[0] = 0.0;
        for(int j = 0; j < 120; j++){
            net1->mats[6].p_matrix[i].arr[0] +=
            net1->mats[5].p_matrix[j].arr[0] *
            net1->level[5].neu[i].weights.arr[j];
        }
        net1->mats[6].p_matrix[i].arr[0] =
            net1->level[5].neu[i].p_activateFunction
            (net1->mats[6].p_matrix[i].arr[0], 0.0);
    }
}


void runOfLayerSeven(Cnnnet *net1){
    for(int i = 0; i < 10; i++){
        net1->mats[7].p_matrix[i].arr[0] = 0.0;
        for(int j = 0; j < 120; j++){
            net1->mats[7].p_matrix[i].arr[0] +=
            net1->mats[6].p_matrix[j].arr[0] *
            net1->level[6].neu[i].weights.arr[j];
        }
        net1->mats[7].p_matrix[i].arr[0] =
            net1->level[6].neu[i].p_activateFunction
            (net1->mats[7].p_matrix[i].arr[0], 0.0);
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
    net1->mats[0].p_matrix[0] = matrixMulNum(image , 1.0);
    runOfLayerOne(net1);
    runOfLayerTwo(net1);
    runOfLayerThree(net1);
    runOfLayerFour(net1);
    runOfLayerFive(net1);
    runOfLayerSix(net1);
    runOfLayerSeven(net1);
    for(int i = 1; i < 10; i++){
        if(net1->mats[7].p_matrix[0].arr[i] >
            net1->mats[7].p_matrix[0].arr[ans]){

            ans = i;
        }
    }
    return ans;
}


void writeParameter(Cnnnet net1){
    FILE* fp = fopen("parameter","w");
    fclose(fp);
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
