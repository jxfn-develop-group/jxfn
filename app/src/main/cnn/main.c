#include <time.h>
#include <stdlib.h>

#include "matrix.h"


int main(){
    struct Matrix a = matrixInit(2, 3);
    srand(time(0));
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            //a.arr[i * a.m + j] = i+j;
            matrixSetNum(&a,i,j,i+j);
            //printf("%d %d %d\n",i,j,i*a.m+j);
        }
    }
    matrixPrin(a);
}
