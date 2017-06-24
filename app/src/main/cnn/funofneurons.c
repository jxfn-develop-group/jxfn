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
    srand(time(0));
    int sig = rand() % 2;
    sig = sig > 0? 1 : -1;
    double ans = 1.0/30000.0;
    ans *= sig;
    ans *= rand() % 30000;
    return ans;
}


double funOfLevel0(double a, double b){
    double ans = 0.0;
    return ans;
}


double funOfLevel1(double a, double b){
    double ans = 0.0;
    return ans;
}


double funOfLevel2(double a, double b){
    double ans = 0.0;
    return ans;
}


double funOfLevel3(double a, double b){
    double ans = 0.0;
    return ans;
}


double funOfLevel4(double a, double b){
    double ans = 0.0;
    return ans;
}
