#include <stdio.h>
#include <stdlib.h>


#include "fileofparameter.h"
#include "funofneurons.h"


void readLayerOne(Cnnnet* net1, FILE* fp){
    for(int i = 0; i < 6; i++){
        fscanf(fp,"%lf",&net1->level[0].neu[i]->bias);
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < 5; k++){
                fscanf(fp,"%lf",&net1->level[0].neu[i]->weights.arr[j * 5 + k]);
            }
        }
        net1->level[0].neu[i]->p_activateFunction = funOfLevel0;
    }
}


void writeLayerOne(Cnnnet net1, FILE* fp){
    for(int i = 0; i < 6; i++){
        fprintf(fp,"%f\n",net1.level[0].neu[i]->bias);
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < 5; k++){
                fprintf(fp,"%f ",net1.level[0].neu[i]->weights.arr[j * 5 + k]);
            }
            fprintf(fp,"\n");
        }
    }
}


void readLayerTwo(Cnnnet* net1, FILE* fp){

}


void writeLayerTwo(Cnnnet net1, FILE* fp){

}


void readLayerThree(Cnnnet* net1, FILE* fp){
    for(int i = 0; i < 16; i++){
        fscanf(fp,"%lf",&net1->level[2].neu[i]->bias);
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < 5; k++){
                fscanf(fp,"%lf",&net1->level[2].neu[i]->weights.arr[j * 5 + k]);
            }
        }
    }
}


void writeLayerThree(Cnnnet net1, FILE* fp){
    for(int i = 0; i < 16; i++){
        fprintf(fp,"%f\n",net1.level[2].neu[i]->bias);
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < 5; k++){
                fprintf(fp,"%f ",net1.level[2].neu[i]->weights.arr[j * 5 + k]);
            }
            fprintf(fp, "\n");
        }
    }
}


void readLayerFour(Cnnnet* net1, FILE* fp){

}


void writeLayerFour(Cnnnet net1, FILE* fp){

}


void readLayerFive(Cnnnet* net1, FILE* fp){
    for(int i = 0; i < 120; i++){
        fscanf(fp,"%lf",&net1->level[4].neu[i]->bias);
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < 5; k++){
                fscanf(fp,"%lf",&net1->level[4].neu[i]->weights.arr[j * 5 + k]);
            }
        }
    }
}


void writeLayerFive(Cnnnet net1, FILE* fp){
    for(int i = 0; i < 120; i++){
        fprintf(fp,"%f\n",net1.level[4].neu[i]->bias);
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < 5; k++){
                fprintf(fp,"%f ",net1.level[4].neu[i]->weights.arr[j * 5 + k]);
            }
        }
        fprintf(fp, "\n");
    }
}


void readLayerSix(Cnnnet* net1, FILE* fp){
    for(int i = 0; i < 84; i++){
        fscanf(fp,"%lf",&net1->level[5].neu[i]->bias);
        fscanf(fp,"%lf",&net1->level[5].neu[i]->weights.arr[0]);
    }
}


void writeLayerSix(Cnnnet net1, FILE* fp){
    for(int i = 0; i < 84; i++){
        fprintf(fp,"%f ",net1.level[5].neu[i]->bias);
        fprintf(fp,"%f\n",net1.level[5].neu[i]->weights.arr[0]);
    }
}


void readLayerSeven(Cnnnet* net1, FILE* fp){
    for(int i = 0; i < 10; i++){
        fscanf(fp,"%lf",&net1->level[6].neu[i]->bias);
        fscanf(fp,"%lf",&net1->level[6].neu[i]->weights.arr[0]);
    }
}


void writeLayerSeven(Cnnnet net1, FILE* fp){
    for(int i = 0; i < 10; i++){
        fprintf(fp,"%f ",net1.level[5].neu[i]->bias);
        fprintf(fp,"%f\n",net1.level[5].neu[i]->weights.arr[0]);
    }
}


void readPara(Cnnnet* net1){
    FILE* fp = fopen("parameter","r");
    if (fp == NULL){
        printf("The file of init doesn't exit!\n");
        exit(0);
    }
    readLayerOne(net1, fp);
    readLayerTwo(net1, fp);
    readLayerThree(net1, fp);
    readLayerFour(net1, fp);
    readLayerFive(net1, fp);
    readLayerSix(net1, fp);
    readLayerSeven(net1, fp);
    fclose(fp);
}


void writePara(Cnnnet net1){
    FILE* fp = fopen("parameter","w");
    writeLayerOne(net1, fp);
    writeLayerTwo(net1, fp);
    writeLayerThree(net1, fp);
    writeLayerFour(net1, fp);
    writeLayerFive(net1, fp);
    writeLayerSix(net1, fp);
    writeLayerSeven(net1, fp);
    fclose(fp);
}


void readIm(int s[], Matrix* mat){
    Matrix pic;
    matrixInit(&pic, 32, 32);
    for(int i = 0; i < 32; i++){
        pic.arr[i] = 0.0;
        pic.arr[i + 32] = 0.0;
        pic.arr[i + 32*30] = 0.0;
        pic.arr[i + 32*31] = 0.0;
        pic.arr[i * 32] = 0.0;
        pic.arr[i * 32 + 1] = 0.0;
        pic.arr[i * 32 + 30] = 0.0;
        pic.arr[i * 32 + 31] = 0.0;
    }
    for(int i = 2; i< 30; i++){
        for(int j = 2; j < 30; j++){
            pic.arr[i * 32 + j] = s[(i-2)*28 + (j-2)];
        }
    }
    matrixEqu(mat, &pic);
    free(pic.arr);
}
