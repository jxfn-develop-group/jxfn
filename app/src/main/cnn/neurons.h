#include "matrix.h"


#ifndef _NEURONS_H
    #define _NEURONS_H 2
    struct Neurons{
        Matrixs weights;
        double bias;
        double (*p_baseFunction)(Matrix , Matrix , double);//基函数指针
        double (*p_activateFunction)(double , double);//激活函数指针
    };
    typedef struct Neurons Neurons;
    Neurons neuronsInit(int n, int m, double bias);
    struct Neuronss{
        int siz;
        Neurons* neu;
    };
    typedef struct Neuronss Neuronss;
    Neuronss neuronssInit(int siz);
#endif
