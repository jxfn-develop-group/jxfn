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
    initRand(&cnn);
    char fn[1111]="parameter";
    initFromFile(&cnn, fn);

    FILE* fp;

    for(int t=0;t<TESTNUM;t++){
        fp = fopen("out1","r");
        double maxval = 0.0, minval = 110.0, averval = 0.0, act = 0.0;
        for(int ii=0;ii<LEARNDATANUM;ii++){
            int ans =ii%26;
            for(int i = 2;i<30;i++){
                for(int j= 2; j < 30 ; j++){
                    fscanf(fp,"%lf",&mat.arr[i * 32 + j]);
                }
            }
            double tmp = errorCnn(&cnn, mat, ans);
            act+=tmp;
            //if(ans)
            //printf("%d:%d %d %f\n",ans,t,ii,tmp);
            double err;
            double tmp1=tmp;
            if(tmp<0.5){
                err = tmp * 0.99;
                tmp1 = tmp*1.01;
            }
            else if(tmp < 1.0){
                err = tmp * 0.95;
                tmp1=tmp*1.02;
            }
            else if(tmp < 2.0){
                err = tmp * 0.80;
                tmp1= tmp* 1.04;
            }
            else if(tmp < 10.0){
                err = tmp * 0.90;
                tmp1= tmp*1.08;
            }
            else if(tmp < 100.0){
                err = tmp * 0.80;
                tmp1= tmp*1.18;
            }
            else{
                err = tmp - 50.0;
                tmp1= tmp + 20.0;
            }
            learnCnn(&cnn, mat, ans);
            //err = tmp * 0.99;
            int ci = 0;
            double pre = tmp;
            while(tmp>0.25&&ci<100){
                ci++;
                //if(tmp<0.20)break;
                learnCnn(&cnn,mat,ans);
                tmp = errorCnn(&cnn, mat, ans);
                if(tmp>tmp1){
                    printf("\n!! %f %f %f\n\n",tmp,tmp1,err);
                    break;
                }
                //if(ci%100==0)printf("%f\n",tmp);
            }
            //if(ii%100<10)
            printf("%d:%d %d %f %d %d\n",ans,t,ii,tmp,ci,pre>tmp);
            averval += tmp;
            maxval = maxval > tmp ? maxval : tmp;
            minval = minval < tmp ? minval : tmp;
        }
        fclose(fp);
        printf("%.9f %.9f %.9f %.9f\n",minval, maxval, averval/1000.0, act/1000.0);
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
