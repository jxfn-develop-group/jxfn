#include <stdio.h>
#include <stdlib.h>


#include "matrix.h"
#include "neurons.h"


void neuronsInit(Neurons* a, int n, int m, double bias){
    matrixInit(&a->weights, n, m);
    a->p_activateFunction = NULL;
    a->bias = bias;
    a->p_baseFunction = NULL;
}


void neuronsFree(Neurons* a){
    matrixFree(&a->weights);
}


void neuronssInit(Neuronss* a, int siz){
    if(siz <= 0){
        printf("Neuronss init error!\n");
        exit(0);
    }
    a->siz = siz;
    a->neu = calloc(a->siz, sizeof(Neurons*));
    if(a->neu == NULL){
        printf("The memory is not enough when the Neuronss created!\n");
    }
    for(int i = 0; i < siz; i++){
        a->neu[i] = calloc(1, sizeof(Neurons));
    }
}


void neuronssFree(Neuronss* a){
    if(a->neu != NULL){
        for(int i = 0; i < a->siz; i++){
            neuronsFree(a->neu[i]);
            if(a->neu[i] != NULL){
                free(a->neu[i]);
            }
        }
        free(a->neu);
    }
    a->siz = 0;
}
