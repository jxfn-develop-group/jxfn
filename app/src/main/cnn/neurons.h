#include "matrix.h"


#ifndef _NEURONS_H
    #define _NEURONS_H 2
    struct Neurons{
        Matrix from, to, weights;
        double bias;
        double (*p_baseFunction)(Matrix , Matrix , double);//基函数指针
        double (*p_activateFunction)(double , double);//激活函数指针

    };
    typedef struct Neurons Neurons;
    Neurons neuronsInit(Matrix from, Matrix to, Matrix weights, double bias);
    struct Neuronss{
        int n,m;
        Neurons* neu;
    };
    typedef struct Neuronss Neuronss;
    Neuronss NeuronssInit(int n,int m);
#endif
