#include "matrix.h"


#ifndef _NEURONS_H
    #define _NEURONS_H 2
    struct Neurons{
        Matrix weights;
        double bias;
        double (*p_baseFunction)(Matrix , Matrix , double);//基函数指针
        double (*p_activateFunction)(double , double);//激活函数指针
    };
    typedef struct Neurons Neurons;
    void neuronsInit(Neurons* a, int n, int m, double bias);
    void neuronsFree(Neurons* a);
    struct Neuronss{
        int siz;
        Neurons** neu;
    };
    typedef struct Neuronss Neuronss;
    void neuronssInit(Neuronss* a, int siz);
    void neuronssFree(Neuronss* a);
#endif
