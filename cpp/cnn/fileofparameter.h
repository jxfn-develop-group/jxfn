#include "cnnnet.h"
#include "fileofconfig.h"


#ifndef _FILEOFPARAMETER_H
    #define _FILEOFPARAMETER_H 2
    void readPara(Cnnnet* net1, char* s);
    void writePara(Cnnnet net1, char* s);
    void readIm(double* s, Matrix* mat);
#endif
