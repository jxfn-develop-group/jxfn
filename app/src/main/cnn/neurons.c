#include <stdio.h>
#include <stdlib.h>


#include "matrix.h"
#include "neurons.h"


Neurons neuronsInit(int n, int m, double bias){
    Neurons c;
    c.weights = matrixInit(n, m);
    c.p_activateFunction = NULL;
    c.bias = bias;
    c.p_baseFunction = NULL;
    return c;
}


Neuronss neuronssInit(int siz){
    if(siz <= 0){
        printf("Neuronss init error!\n");
        exit(0);
    }
    Neuronss c;
    c.siz = siz;
    c.neu = malloc(c.siz * sizeof(Neurons));
    if(c.neu == NULL){
        printf("The memory is not enough when the Neuronss created!\n");
    }
    return c;
}
