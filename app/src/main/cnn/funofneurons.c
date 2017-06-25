#include <time.h>
#include <stdlib.h>


#include "funofneurons.h"


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
