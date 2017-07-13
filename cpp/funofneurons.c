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
    double tmp = *nex * LReLuDer(output);
    *pre +=   (tmp * (*w));
    *w -= minDouble(LEARNINDEX * (input * tmp), WEIGHTLIMIT);
    if(*w > 1.0) *w = 1.0;
    if(*w < -1.0) *w = -1.0;
    *bias -= LEARNBIAS * tmp;
}


void LReLuRTNoChange(double* pre, double* nex, double* w, double input,
        double output, double* bias, double* wc){
    double tmp = *nex * LReLuDer(output);
    *pre += tmp * (*w) ;
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
    Matrix tweights;
    tweights.arr = NULL;
    matrixEqu(&tweights, &neu->weights);
    int om = output->m, on = output->n, im = input->m, nm = neu->weights.m;
    matrixInit(&tmat, neu->weights.n, neu->weights.m);
    for(int i = 0; i < on; i++){
        for(int j = 0; j < output->m; j++){
            if(fabs(output->arr[i * output->m + j]) < EPS){
                continue;
            }
            double tmpp = 1.0;
            tmpp /= (double)neu->weights.n;
            tmpp /= (double)neu->weights.m;
            for(int ii = 0; ii < neu->weights.n; ii++){
                for(int jj = 0; jj < neu->weights.m; jj++){
                    p_fun(&pre->arr[(i+ii)*im+j+jj],&nex->arr[i*om+j],
                    &neu->weights.arr[ii*nm+jj],input->arr[(i+ii)*im+j+jj],
                    input->arr[(i+ii)*im+j+jj] * neu->weights.arr[ii*nm+jj] +
                    neu->bias * tmpp, &neu->bias,&tmat.arr[ii*nm+jj]);
                }
            }
        }
    }
    matrixAdd(&neu->weights, &tmat);
    weightsAdjust(&tweights, &neu->weights);
    matrixFree(&tmat);
    matrixFree(&tweights);
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


double minDouble(double a, double b){
    if(fabs(a) > fabs(b)){
        if(a>0){
            return fabs(b);
        }
        else{
            return -fabs(b);
        }
    }
    else{
        return a;
    }
}


void gradAdjust(Matrixs* mat){
    double maxd = 0.0;
    for(int i = 0; i < mat->siz; i++){
        for(int j = 0; j < mat->p_matrix[i]->n; j++){
            int m = mat->p_matrix[i]->m;
            for(int k = 0; k < m; k++){
                if(fabs(mat->p_matrix[i]->arr[j * m +k])>maxd){
                    maxd = fabs(mat->p_matrix[i]->arr[j * m +k]);
                }
            }
        }
    }
    if(maxd > GRADLIMIT){
        maxd /= GRADLIMIT;
    }
    else{
        return;
    }
    for(int i = 0; i < mat->siz; i++){
        for(int j = 0; j < mat->p_matrix[i]->n; j++){
            int m = mat->p_matrix[i]->m;
            for(int k = 0; k < m; k++){
                mat->p_matrix[i]->arr[j *m + k] /= maxd;
            }
        }
    }
}


void biasAdjust(double* tmpbias, double* bias){
    if(fabs(*tmpbias - *bias) > BIASLIMIT){
        if(*tmpbias > *bias){
            *bias = *tmpbias - BIASLIMIT;
        }
        else{
            *bias = *tmpbias + BIASLIMIT;
        }
    }
    if(fabs(*bias) > 0.5){
        if(*bias > 0.0){
            *bias = 0.5;
        }
        else{
            *bias = -0.5;
        }
    }
}


void weightsAdjust(Matrix* pre, Matrix* now){
    if(!matrixSameSize(pre, now)){
        printf("error in weightsAdjust!\n");
        exit(0);
    }
    int n = pre->n, m = pre->m;
    //printf("%d %d\n",n,m);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(fabs(pre->arr[i * m +j] - now->arr[i * m + j]) > WEIGHTLIMIT){
                if(pre->arr[i * m + j] > now->arr[i * m + j]){
                    now->arr[i * m + j] = pre->arr[i * m + j] - WEIGHTLIMIT;
                }
                else{
                    now->arr[i * m + j] = pre->arr[i * m + j] + WEIGHTLIMIT;
                }
            }
            if(fabs(now->arr[i * m + j]) > 1.0){
                if(now->arr[i * m + j] > 0.0){
                    now->arr[i * m + j] = 1.0;
                }
                else{
                    now->arr[i * m + j] = -1.0;
                }
            }
        }
    }
}
