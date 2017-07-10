#include "matrix.h"
#include "fileofconfig.h"


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
    #ifndef LEARNINDEX
        #define LEARNINDEX 1e-3
    #endif
    #ifndef LEARNBIAS
        #define LEARNBIAS 1e-4
    #endif
    #ifndef WEIGHTLIMIT
        #define WEIGHTLIMIT 1e-1
    #endif
    #ifndef BIASLIMIT
        #define BIASLIMIT 1e-1
    #endif
    //梯度范围
    #ifndef GRADLIMIT
        #define GRADLIMIT 1e3
    #endif
    #ifndef IDEALOUTPUTPOS
        #define IDEALOUTPUTPOS 1.0
    #endif
    #ifndef IDEALOUTPUTNEG
        #define IDEALOUTPUTNEG 0.0
    #endif
#endif
