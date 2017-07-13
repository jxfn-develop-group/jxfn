#include "interface.hpp"


char cnnInterface(std::vector<std::vector<int> > vec){
    Cnnnet cnn;
    cnnnetInit(&cnn);
    //initRand(&cnn);
    functionIni(&cnn);
    Matrix mat;
    matrixInit(&mat, 32, 32);
    for(int i = 0; i < 28; i++){
        for(int j = 0; j < 28; j++){
            mat.arr[(2 + i) * 32 + j + 2] = vec[i][j];
        }
    }
    int ans = runCnn(&cnn, mat);
    return (char)(ans + 'a');
}
