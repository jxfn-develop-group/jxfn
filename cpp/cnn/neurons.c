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
    a->neu = (Neurons**)(calloc(a->siz, sizeof(Neurons*)));
    if(a->neu == NULL){
        printf("The memory is not enough when the Neuronss created!\n");
        exit(0);
    }
    for(int i = 0; i < siz; i++){
        a->neu[i] = (Neurons*)(calloc(1, sizeof(Neurons)));
        if(a->neu[i] == NULL){
            printf("neuronss neu init error!\n");
            exit(0);
        }
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
