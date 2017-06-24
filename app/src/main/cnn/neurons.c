#include <stdio.h>
#include <stdlib.h>


#include "matrix.h"
#include "neurons.h"


Neurons neuronsInit(Matrix from, Matrix to, Matrix weights, double bias){
    Neurons c;
    c.from = from;
    c.to = to;
    c.weights = weights;
    c.p_activateFunction = NULL;
    c.bias = bias;
    c.p_baseFunction = NULL;
    return c;
}


Neuronss NeuronssInit(int n,int m){
    if(n <= 0 || m <= 0){
        printf("Neuronss init error!\n");
        exit(0);
    }
    Neuronss c;
    c.n = n;
    c.m = m;
    c.neu = malloc(c.n * c.m * sizeof(Neurons));
    if(c.neu == NULL){
        printf("The memory is not enough when the Neuronss created!\n");
    }
    return c;
}
