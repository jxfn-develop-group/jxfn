#include "neurons.h"
#include "matrix.h"


#ifndef _CONNET_H
    #define _CONNET_H 2
    struct Cnnnet{
        Matrixs mats[8];
        Neuronss level[7];
    };
    typedef struct Cnnnet Cnnnet;
    void cnnnetInit(Cnnnet* net1);
    void cnnnetFree(Cnnnet* net1);
    void writeParameter(Cnnnet net1);//写神经网络参数
    void initFromFile(Cnnnet* net1);//从文件读入神经网络参数
    void initRand(Cnnnet* net1);//随机数设为参数
    int runCnn(Cnnnet* net1, Matrix image);//运行神经网络
    void learn(Cnnnet* net1, Matrix image, double answer);//学习过程
#endif
