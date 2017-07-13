#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


#include "matrix.h"
#include "neurons.h"
#include "funofneurons.h"
#include "cnnnet.h"
#include "fileofparameter.h"
#include "fileofconfig.h"


int main(){
    srand(time(0));
    Matrix mat;
    matrixInit(&mat, 32, 32);
    Cnnnet cnn;
    cnnnetInit(&cnn);
    //initRand(&cnn);
    char fn[1111]="parameter";
    initFromFile(&cnn, fn);

    FILE* fp;

    for(int t=0;t<TESTNUM;t++){
        fp = fopen("out1","r");
        double maxval = 0.0, minval = 110.0, averval = 0.0, act = 0.0;
        for(int ii=0;ii<LEARNDATANUM;ii++){
            int ans =ii%OUTPUTNUMBER;
            for(int i = 2;i<30;i++){
                for(int j= 2; j < 30 ; j++){
                    fscanf(fp,"%lf",&mat.arr[i * 32 + j]);
                }
            }
            double tmp = errorCnn(&cnn, mat, ans);
            act+=tmp;
            maxval = maxval > tmp ? maxval : tmp;
            minval = minval < tmp ? minval : tmp;
            //if(ans)
            //printf("%d:%d %d %f\n",ans,t,ii,tmp);
            //double err;
            double tmp1=tmp;
            int maxci=5;/*
            if(tmp<0.15){
                maxci = 1;
            }
            else if(tmp<0.25){
                maxci = 5;
            }
            else if(tmp<0.35){
                maxci = 9;
            }
            else if(tmp<0.45){
                maxci = 14;
            }
            else if(tmp<0.55){
                maxci =18;
            }
            else if(tmp<0.65){
                maxci = 22;
            }
            else if(tmp<0.8){
                maxci = 26;
            }
            else if(tmp<1.0){
                maxci = 30;
            }
            else if(tmp<2.0){
                maxci = 40;
            }
            else if(tmp<5.0){
                maxci = 50;
            }
            else if(tmp<10.0){
                maxci = 60;
            }
            else{
                maxci = 70;
            }*/
            //learnCnn(&cnn, mat, ans);
            //err = tmp * 0.99;
            int ci = 0;
            //double pre = tmp;
            while(ci<1){
                ci++;
                //if(tmp<0.20)break;
                learnCnn(&cnn,mat,ans);
                tmp = errorCnn(&cnn, mat, ans);
                if(tmp>tmp1){
                    printf("\n!! %f %f\n\n",tmp,tmp1);
                    break;
                }
                //if(ci%100==0)printf("%f\n",tmp);
            }
            //if(ii%100<10)
            //printf("%d:%d %d %f %d %d\n",ans,t,ii,tmp,ci,pre>tmp);
            averval += tmp;
        }
        fclose(fp);
        printf("%d %.9f %.9f %.9f %.9f\n",t, minval, maxval,
        averval/(double)LEARNDATANUM, act/(double)LEARNDATANUM);
    }
    char s[1111];
    int sav=0;
    do{
        printf("save or not?'y' or 'n'\n");
        scanf("%s",s);
        if(s[0]=='y'){
            sav=1;break;
        }
        if(s[0]=='n'){
            sav=0;break;
        }
    }while(1);
    if(sav){
        writeParameter(cnn,fn);
    }
    cnnnetFree(&cnn);
    matrixFree(&mat);
    return 0;
}
