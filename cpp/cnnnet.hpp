#include "neurons.hpp"
#include "matrix.hpp"
#include "fileofconfig.hpp"
#include "funofneurons.hpp"


#ifndef _CONNET_H
    #define _CONNET_H 2
    #define FACTOROFLEARN 0.01
    struct Cnnnet{
        Matrixs mats[8];
        Neuronss level[7];
    };
    typedef struct Cnnnet Cnnnet;
    void cnnnetInit(Cnnnet* net1);
    void cnnnetFree(Cnnnet* net1);
    void writeParameter(Cnnnet net1, char* fn);//写神经网络参数
    void initFromFile(Cnnnet* net1, char* fn);//从文件读入神经网络参数
    void initRand(Cnnnet* net1);//随机数设为参数
    int runCnn(Cnnnet* net1, Matrix image);//运行神经网络
    void learnCnn(Cnnnet* net1, Matrix image, int answer);//学习过程
    #ifndef CNNERROR//允许误差
        #define CNNERROR 0.1
    #endif
    double errorCnn(Cnnnet *net1, Matrix image, int ans);
    void initFun(Cnnnet* net1);
#endif
