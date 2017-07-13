#include <stdio.h>
#include <stdlib.h>


#include "fileofparameter.hpp"
#include "fileofconfig.hpp"
#include "funofneurons.hpp"


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
        fprintf(fp,"%.12f\n",net1.level[0].neu[i]->bias);
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < 5; k++){
                fprintf(fp,"%.12f ",net1.level[0].neu[i]->weights.arr[j * 5 + k]);
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
        fprintf(fp,"%.12f\n",net1.level[2].neu[i]->bias);
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < 5; k++){
                fprintf(fp,"%.12f ",net1.level[2].neu[i]->weights.arr[j * 5 + k]);
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
        fprintf(fp,"%.12f\n",net1.level[4].neu[i]->bias);
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < 5; k++){
                fprintf(fp,"%.12f ",net1.level[4].neu[i]->weights.arr[j * 5 + k]);
            }
        }
        fprintf(fp, "\n");
    }
}


void readLayerSix(Cnnnet* net1, FILE* fp){
    for(int i = 0; i < 84; i++){
        fscanf(fp,"%lf",&net1->level[5].neu[i]->bias);
        for(int j=0;j<120;j++){
            fscanf(fp,"%lf",&net1->level[5].neu[i]->weights.arr[j]);
        }
    }
}


void writeLayerSix(Cnnnet net1, FILE* fp){
    for(int i = 0; i < 84; i++){
        fprintf(fp,"%.12f\n",net1.level[5].neu[i]->bias);
        for(int j=0; j<120; j++){
            fprintf(fp,"%.12f ",net1.level[5].neu[i]->weights.arr[j]);
        }
        fprintf(fp, "\n");
    }
}


void readLayerSeven(Cnnnet* net1, FILE* fp){
    for(int i = 0; i < OUTPUTNUMBER; i++){
        fscanf(fp,"%lf",&net1->level[6].neu[i]->bias);
        for(int j = 0; j < 84; j++){
            fscanf(fp,"%lf",&net1->level[6].neu[i]->weights.arr[j]);
        }
    }
}


void writeLayerSeven(Cnnnet net1, FILE* fp){
    for(int i = 0; i < OUTPUTNUMBER; i++){
        fprintf(fp,"%.12f\n",net1.level[6].neu[i]->bias);
        for(int j = 0; j < 84; j++){
            fprintf(fp,"%.12f ",net1.level[6].neu[i]->weights.arr[j]);
        }
        fprintf(fp, "\n");
    }
}


void readPara(Cnnnet* net1, char* s){
    int len = 0;
    while(s[len] != 0 && len<100){
        len++;
    }
    if(len == 0 || len == 100){
        printf("Invalid filename!\n");
        exit(0);
    }
    FILE* fp = fopen(s,"r");
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


void writePara(Cnnnet net1, char* s){
    int len = 0;
    while(s[len] != 0 && len<100){
        len++;
    }
    if(len == 0 || len == 100){
        printf("Invalid filename!\n");
        exit(0);
    }
    FILE* fp = fopen(s,"w");
    writeLayerOne(net1, fp);
    writeLayerTwo(net1, fp);
    writeLayerThree(net1, fp);
    writeLayerFour(net1, fp);
    writeLayerFive(net1, fp);
    writeLayerSix(net1, fp);
    writeLayerSeven(net1, fp);
    fclose(fp);
}


void readIm(double* s, Matrix* mat){
    Matrix pic;
    matrixInit(&pic, 32, 32);
    for(int i = 2; i< 30; i++){
        for(int j = 2; j < 30; j++){
            pic.arr[i * 32 + j] = s[(i-2)*28 + (j-2)];
            // printf("%f ",pic.arr[i*32+j]);
        }
        // printf("\n");
    }
    matrixEqu(mat, &pic);
    matrixFree(&pic);
}
