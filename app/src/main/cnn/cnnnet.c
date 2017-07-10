#include <stdio.h>
#include <math.h>
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
        neuronsInit(net1->level[0].neu[i],  5, 5, getRand()*0.2);
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
        neuronsInit(net1->level[2].neu[i], 5, 5, getRand()*0.2);
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < 5; k++){
                if(i<6){
                    net1->level[2].neu[i]->weights.arr[j * 5 + k] =
                    getRand();
                }
                else if(i==15){
                    net1->level[2].neu[i]->weights.arr[j * 5 + k] =
                    getRand();
                }
                else{
                    net1->level[2].neu[i]->weights.arr[j * 5 + k] =
                    getRand();
                }
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
        neuronsInit(net1->level[4].neu[i], 5, 5, getRand()*0.2);
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < 5; k++){
                net1->level[4].neu[i]->weights.arr[j * 5 + k] = getRand();
            }
        }
        net1->level[4].neu[i]->p_activateFunction = funOfLevel4;
    }
    for(int i = 0; i < 84; i++){
        neuronsInit(net1->level[5].neu[i], 1, 120, getRand()*0.2);
        for(int j = 0; j < 120; j++){
            net1->level[5].neu[i]->weights.arr[j] = getRand();
        }
        net1->level[5].neu[i]->p_activateFunction = funOfLevel0;
        //每层的激活函数相同
    }
    for(int i = 0; i < 10; i++){
        neuronsInit(net1->level[6].neu[i], 1, 84, getRand()*0.2);
        for(int j = 0; j < 84; j++){
            net1->level[6].neu[i]->weights.arr[j] = getRand();
        }
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
        matrixMulNum(net1->mats[1].p_matrix[i], 0.08);
    }
}


void runOfLayerTwo(Cnnnet *net1){
    for(int i = 0; i < 6; i++){
        matrixSample(net1->mats[2].p_matrix[i],
            net1->mats[1].p_matrix[i], 2, 2, maxnumOfMatrix);
    }
}


void runOfLayerThree(Cnnnet *net1){
    Matrixs tmat;
    matrixsInit(&tmat, 16, 14, 14);
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 3; j++){
            matrixAdd(tmat.p_matrix[i], net1->mats[2].p_matrix[(i+j)%6]);
        }
    }
    for(int i = 6; i < 12; i++){
        for(int j = 0; j < 4; j++){
            matrixAdd(tmat.p_matrix[i], net1->mats[2].p_matrix[(i+j)%6]);
        }
    }
    for(int i = 12; i < 15; i++){
        for(int j = 0; j < 5; j++){
            if(j == 2){continue;}
            matrixAdd(tmat.p_matrix[i], net1->mats[2].p_matrix[(i+j)%6]);
        }
    }
    for(int i = 0; i < 6; i++){
        matrixAdd(tmat.p_matrix[15], net1->mats[2].p_matrix[i]);
    }
    /*
    net1->mats[3].p_matrix[i] 必须初始化为零
    */
    for (int i = 0; i < 16; i++){
        matrixConv(net1->mats[3].p_matrix[i], tmat.p_matrix[i],
            &net1->level[2].neu[i]->weights);
        matrixAddNum(net1->mats[3].p_matrix[i], net1->level[2].neu[i]->bias);
        matrixFunction(net1->mats[3].p_matrix[i],
            net1->level[2].neu[i]->p_activateFunction, 0.0);
    }
    for(int i = 0; i < 6; i++){
        matrixMulNum(net1->mats[3].p_matrix[i], 0.08/3.0);
    }
    for(int i = 6; i < 15; i++){
        matrixMulNum(net1->mats[3].p_matrix[i], 0.02);
    }
    matrixMulNum(net1->mats[3].p_matrix[15], 0.04/3.0);
    matrixsFree(&tmat);
}


void runOfLayerFour(Cnnnet *net1){
    for(int i = 0; i < 16; i++){
        matrixSample(net1->mats[4].p_matrix[i], net1->mats[3].p_matrix[i],
            2, 2, maxnumOfMatrix);
    }
}


void runOfLayerFive(Cnnnet *net1){
    Matrix tmat;
    matrixInit(&tmat, 5, 5);
    for(int i = 0; i < 16; i++){
        matrixAdd(&tmat, net1->mats[4].p_matrix[i]);
    }
    for(int i = 0; i < 120; i++){
        matrixConv(net1->mats[5].p_matrix[i], &tmat,
            &net1->level[4].neu[i]->weights);
        net1->mats[5].p_matrix[i]->arr[0] += net1->level[4].neu[i]->bias;
        net1->mats[5].p_matrix[i]->arr[0] =
            net1->level[4].neu[i]->p_activateFunction
            (net1->mats[5].p_matrix[i]->arr[0], 0.0);
        matrixMulNum(net1->mats[5].p_matrix[i], 0.005);
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
        net1->mats[6].p_matrix[i]->arr[0] += net1->level[5].neu[i]->bias;
        net1->mats[6].p_matrix[i]->arr[0] =
            net1->level[5].neu[i]->p_activateFunction
            (net1->mats[6].p_matrix[i]->arr[0], 0.0);
        matrixMulNum(net1->mats[5].p_matrix[i], 1.0/60.0);
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
        net1->mats[7].p_matrix[i]->arr[0] += net1->level[6].neu[i]->bias;
        net1->mats[7].p_matrix[i]->arr[0] =
            net1->level[6].neu[i]->p_activateFunction
            (net1->mats[7].p_matrix[i]->arr[0], 0.0);
        matrixMulNum(net1->mats[5].p_matrix[i], 1.0/42.0);
    }
}


void learnOfLayerOne(Cnnnet *net1, Matrixs* mat){
    Matrix tmp;
    matrixInit(&tmp, 32, 32);
    Matrix tbias;
    matrixInit(&tbias, 1, 6);
    for(int i = 0 ;i < 6; i++){
        tbias.arr[i] = net1->level[0].neu[i]->bias;
        matrixMulNum(mat->p_matrix[i], 0.08);
    }
    for(int i = 0; i < 6; i++){
        /*convRT(&tmp, mat->p_matrix[i], net1->level[0].neu[i],
        net1->mats[0].p_matrix[0], net1->mats[1].p_matrix[i], LReLuRTNoChange);*/
        biasAdjust(&tbias.arr[i], &net1->level[0].neu[i]->bias);
    }
    matrixFree(&tmp);
    matrixFree(&tbias);
}


void learnOfLayerTwo(Cnnnet *net1, Matrixs* mat){
    Matrixs res;
    matrixsInit(&res, 6, 28, 28);
    for(int i = 0; i < 6; i++){
        matrixRestore(net1->mats[1].p_matrix[i], mat->p_matrix[i],
            res.p_matrix[i], 2, 2);
    }
    matrixsEqu(mat, &res);
    matrixsFree(&res);
}


void learnOfLayerThree(Cnnnet *net1, Matrixs* mat){
    Matrixs res;
    matrixsInit(&res, 6, 14, 14);
    Matrixs tma;
    matrixsInit(&tma, 16, 14, 14);
    Matrixs tmat;
    matrixsInit(&tmat, 16, 14, 14);
    Matrix tbias;
    matrixInit(&tbias, 1 , 16);
    for(int i = 0; i < 16; i++){
        tbias.arr[i] = net1->level[2].neu[i]->bias;
    }
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 3; j++){
            matrixAdd(tmat.p_matrix[i], net1->mats[2].p_matrix[(i+j)%6]);
        }
        matrixMulNum(mat->p_matrix[i], 0.08/3.0);
    }
    for(int i = 6; i < 12; i++){
        for(int j = 0; j < 4; j++){
            matrixAdd(tmat.p_matrix[i], net1->mats[2].p_matrix[(i+j)%6]);
        }
        matrixMulNum(mat->p_matrix[i], 0.04);
    }
    for(int i = 12; i < 15; i++){
        for(int j = 0; j < 5; j++){
            if(j == 2){continue;}
            matrixAdd(tmat.p_matrix[i], net1->mats[2].p_matrix[(i+j)%6]);
        }
        matrixMulNum(mat->p_matrix[i], 0.04);
    }
    for(int i = 0; i < 6; i++){
        matrixAdd(tmat.p_matrix[15], net1->mats[2].p_matrix[i]);
    }
    matrixMulNum(mat->p_matrix[15], 0.04/3.0);
    for(int i = 0; i < 16; i++){
        convRT(tma.p_matrix[i], mat->p_matrix[i], net1->level[2].neu[i],
        tmat.p_matrix[i], net1->mats[3].p_matrix[i], LReLuRTNoChange);
    }

    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 3; j++){
            matrixAdd(res.p_matrix[(i+j)%6], tma.p_matrix[i]);
        }
    }
    for(int i = 6; i < 12; i++){
        for(int j = 0; j < 4; j++){
            matrixAdd(res.p_matrix[(i+j)%6], tma.p_matrix[i]);
        }
    }
    for(int i = 12; i < 15; i++){
        for(int j = 0; j < 5; j++){
            if(j == 2){continue;}
            matrixAdd(res.p_matrix[(i+j)%6], tma.p_matrix[i]);
        }
    }
    for(int i = 0; i < 6; i++){
        matrixAdd(res.p_matrix[i], tma.p_matrix[15]);
    }
    for(int i = 0; i < 16; i++){
        biasAdjust(&tbias.arr[i], &net1->level[2].neu[i]->bias);
    }
    gradAdjust(&res);
    matrixFree(&tbias);
    matrixsEqu(mat, &res);
    matrixsFree(&res);
    matrixsFree(&tma);
    matrixsFree(&tmat);
}


void learnOfLayerFour(Cnnnet *net1, Matrixs* mat){
    Matrixs res;
    matrixsInit(&res, 16, 10, 10);
    for(int i = 0; i < 16; i++){
        matrixRestore(net1->mats[3].p_matrix[i], mat->p_matrix[i],
            res.p_matrix[i], 2, 2);
    }
    matrixsEqu(mat, &res);
    matrixsFree(&res);
}


void learnOfLayerFive(Cnnnet *net1, Matrixs* mat){
    Matrixs res;
    matrixsInit(&res, 16, 5, 5);
    Matrix tmat;
    matrixInit(&tmat, 5, 5);
    Matrix tres;
    matrixInit(&tres, 5 , 5);
    for(int i = 0; i < 16; i++){
        matrixAdd(&tmat, net1->mats[4].p_matrix[i]);
    }
    for(int i = 0; i < 120; i++){
        double outputError = mat->p_matrix[i]->arr[0];
        outputError *= 0.005;
        // printf("layout5:%f %d\n",outputError,i);
        double tmpbias = net1->level[4].neu[i]->bias;
        for(int j = 0; j < 25; j++){
            LReLuRT(&tres.arr[j], &outputError ,
                &net1->level[4].neu[i]->weights.arr[j], tmat.arr[j],
                tmat.arr[j] * net1->level[4].neu[i]->weights.arr[j] +
                net1->level[4].neu[i]->bias*0.04,
                &net1->level[4].neu[i]->bias);
        }
        biasAdjust(&tmpbias, &net1->level[4].neu[i]->bias);
    }
    gradAdjust(&res);
    for(int i = 0; i < 16; i++){
        matrixEqu(res.p_matrix[i], &tres);
    }
    matrixsEqu(mat, &res);
    matrixsFree(&res);
    matrixFree(&tmat);
    matrixFree(&tres);
}


void learnOfLayerSix(Cnnnet *net1, Matrixs* mat){
    Matrixs res;
    matrixsInit(&res, 120, 1, 1);
    for(int i = 0; i < 84; i++){
        double outputError = mat->p_matrix[i]->arr[0];
        outputError /= 60.0;
        // printf("layout6: %d %f\n",i,outputError);
        double tmpbias = net1->level[5].neu[i]->bias;
        for(int j = 0; j < 120; j++){
            LReLuRT(&res.p_matrix[j]->arr[0], &outputError ,
                &net1->level[5].neu[i]->weights.arr[j],
                net1->mats[5].p_matrix[j]->arr[0],
                net1->mats[5].p_matrix[i]->arr[0]*net1->level[5].neu[i]->
                weights.arr[j]+net1->level[5].neu[i]->bias,
                &net1->level[5].neu[i]->bias);
        }
        biasAdjust(&tmpbias, &net1->level[5].neu[i]->bias);
    }
    gradAdjust(&res);
    matrixsEqu(mat, &res);
    matrixsFree(&res);
}


void learnOfLayerSeven(Cnnnet *net1, Matrixs* mat){
    Matrixs res;
    matrixsInit(&res, 84, 1, 1);
    for(int i = 0; i < 10; i++){
        double outputError = net1->mats[7].p_matrix[i]->arr[0]
            - mat->p_matrix[i]->arr[0];
        if(fabs(outputError) < 0.1){
            continue;
        }
        // printf("lay7oute %d %f\n",i,outputError);
        outputError /= 42.0;
        double tmpbias = net1->level[6].neu[i]->bias;
        for(int j = 0; j < 84; j++){
            LReLuRT(&res.p_matrix[j]->arr[0], &outputError ,
                &net1->level[6].neu[i]->weights.arr[j],
                net1->mats[6].p_matrix[j]->arr[0],
                net1->mats[6].p_matrix[i]->arr[0]*net1->level[6].neu[i]->
                weights.arr[j]+net1->level[6].neu[i]->bias,
                &net1->level[6].neu[i]->bias);
        }
        biasAdjust(&tmpbias, &net1->level[6].neu[i]->bias);
    }
    /*for(int i=0; i< 84;i++){
        printf("lay7:%f %d\n",res.p_matrix[i]->arr[0],i);
    }*/
    gradAdjust(&res);
    matrixsEqu(mat, &res);
    matrixsFree(&res);
}


int runCnn(Cnnnet* net1, Matrix image){
    int ans = 0;
    matrixEqu(net1->mats[0].p_matrix[0], &image);
    matrixMulNum(net1->mats[0].p_matrix[0], 200.0/255.0);
    for(int i = 1; i < 8; i++){
        matrixsClear(&net1->mats[i]);
    }
    runOfLayerOne(net1);
    runOfLayerTwo(net1);
    runOfLayerThree(net1);
    runOfLayerFour(net1);
    runOfLayerFive(net1);
    runOfLayerSix(net1);
    runOfLayerSeven(net1);
    for(int i = 1; i < 10; i++){
        if(net1->mats[7].p_matrix[i]->arr[0] >
            net1->mats[7].p_matrix[ans]->arr[0]){
            ans = i;
        }
    }/*
    for(int k=0;k<net1->mats[7].siz;k++)
    for(int i=0;i<net1->mats[7].p_matrix[k]->n;i++){
        int m = net1->mats[7].p_matrix[k]->m;
        for(int j= 0; j<m;j++){
            printf("%f ",net1->mats[7].p_matrix[k]->arr[i*m+j]);
        }
        printf("\n");
    }*/
    //printf("ans:%f\n",net1->mats[7].p_matrix[ans]->arr[0]);
    return ans;
}


void writeParameter(Cnnnet net1){
    writePara(net1);
}


void learnCnn(Cnnnet* net1, Matrix image, int answer){
    runCnn(net1, image);
    Matrixs mat1;
    matrixsInit(&mat1, 10, 1, 1);
    for(int i = 0; i < 10; i++){
        if(i == answer){
            mat1.p_matrix[i]->arr[0] = IDEALOUTPUTPOS;
        }
        else{
            mat1.p_matrix[i]->arr[0] = IDEALOUTPUTNEG;
        }
    }
    learnOfLayerSeven(net1, &mat1);
    learnOfLayerSix(net1, &mat1);
    learnOfLayerFive(net1, &mat1);
    learnOfLayerFour(net1, &mat1);
    learnOfLayerThree(net1, &mat1);
    learnOfLayerTwo(net1, &mat1);
    learnOfLayerOne(net1, &mat1);
    matrixsFree(&mat1);
}


double errorCnn(Cnnnet* net1, Matrix image, int ans){
    double res = 0.0;
    runCnn(net1, image);
    for(int i = 0; i < 10; i++){
        if(i==ans){
            res += 0.5*pow(IDEALOUTPUTPOS - net1->mats[7].p_matrix[i]->arr[0],2.0);
        }
        else{
            res += 0.5*pow(IDEALOUTPUTNEG - net1->mats[7].p_matrix[i]->arr[0],2.0);
        }
    }
    return res;
}
