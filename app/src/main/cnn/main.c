#include <time.h>
#include <stdlib.h>

#include "matrix.h"


int main(){
    struct matrix a = matrixInit(2, 3);
    srand(time(0));
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            matrixSetNum(a, i, j, rand());
        }
    }
    matrixPrin(a);
}
