#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>


#include "funofneurons.h"
#include "neurons.h"
#include "matrix.h"


double maxd(double a, double b){
    return a > b? a: b;
}


double maxOfMatrix(Matrix a, Matrix b, double c){
    double ans = a.arr[0];
    for (int i = 1; i < a.n * a.m; i++){
        ans = maxd(ans, a.arr[i]);
    }
    return ans;
}



double maxnumOfMatrix(Matrix a){
    double ans = a.arr[0];
    for (int i = 1; i < a.n * a.m; i++){
        ans = maxd(ans, a.arr[i]);
    }
    return ans;
}


double getRand(){
    //srand(time(0));
    int sig = rand() % 2;
    sig = sig > 0? 1 : -1;
    double ans = 1.0/10000.0;
    ans *= sig;
    ans *= rand() % 10000;
    return ans;
    //return 1.0;
}


double getRandRange(int a){
    //srand(time(0));
    double ans = a;
    int sig = rand() % 2;
    sig = sig > 0? 1 : -1;
    ans = 1.0/ans;
    ans *= sig;
    ans *= rand() % 300;
    return ans;
}


double LReLu(double a){
    if(a < 0.0){
        return a * 0.1;
    }
    return a;
}


double LReLuDer(double a){
    if(a < -EPS){
        return 0.1;
    }
    else if(a > EPS){
        return 1.0;
    }
    else{
        return 0.55;
    }
}


void LReLuRT(double* pre, double * nex, double* w, double input,
        double output, double* bias){
    double tmp = *nex * sigmoidDer(output, 0.0);
    *pre += tmp * (*w);
    *w -= LEARNINDEX * input * tmp;
    *bias -= LEARNBIAS * tmp;
}


void LReLuRTNoChange(double* pre, double* nex, double* w, double input,
        double output, double* bias, double* wc){
    double tmp = *nex * sigmoidDer(output, 0.0);
    *pre += tmp * (*w);
    *wc = -LEARNINDEX * input * tmp;
    *bias -= LEARNBIAS * tmp;
}


void convRT(Matrix* pre, Matrix* nex, Neurons* neu, Matrix* input,
    Matrix* output, void(*p_fun)(double*, double*, double *, double,
        double, double*, double*)){
    if(!matrixSameSize(pre, input) || !matrixSameSize(nex, output) ||
    neu->weights.n + output->n != input->n + 1||
    neu->weights.m + output->m != input->m + 1){
        printf("error when convRT!!\n");
        return ;
    }
    Matrix tmat;
    int om = output->m, on = output->n, im = input->m, nm = neu->weights.m;
    matrixInit(&tmat, neu->weights.n, neu->weights.m);
    for(int i = 0; i < on; i++){
        for(int j = 0; j < output->m; j++){
            if(fabs(output->arr[i * output->m + j]) < EPS){
                continue;
            }
            for(int ii = 0; ii < neu->weights.n; ii++){
                for(int jj = 0; jj < neu->weights.m; jj++){
                    p_fun(&pre->arr[(i+ii)*im+j+jj],&nex->arr[i*om+j],
                    &neu->weights.arr[ii*nm+jj],input->arr[(i+ii)*im+j+jj],
                    output->arr[i*om+j],&neu->bias,&tmat.arr[ii*nm+jj]);
                }
            }
        }
    }
    matrixAdd(&neu->weights, &tmat);
    matrixFree(&tmat);
}


double funOfLevel0(double a, double b){
    return LReLu(a);
}


double funOfLevel1(double a, double b){
    double ans = 0.0;
    return ans;
}


double funOfLevel2(double a, double b){
    return LReLu(a);
}


double funOfLevel3(double a, double b){
    double ans = 0.0;
    return ans;
}


double funOfLevel4(double a, double b){
    return LReLu(a);
}


double sigmoid(double a, double b){
    return 1.0/(1.0 + exp(-a));
}


double sigmoidDer(double a,double b){
    return sigmoid(a, 0.0) * (1.0 - sigmoid(a, 0.0));
}


/*
pre 前一层误差，nex下一层误差，w权重，input前一层输入,output 下一层输出
*/
void sigmoidRT(double* pre, double * nex, double* w, double input,
        double output, double* bias){
    double tmp = *nex * sigmoidDer(output, 0.0);
    *pre += tmp * (*w);
    *w -= LEARNINDEX * input * tmp;
    *bias -= LEARNBIAS * tmp;
}
