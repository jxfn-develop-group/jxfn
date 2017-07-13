#include <stdio.h>
#include <stdlib.h>

#include "fileofconfig.h"


int main(){
    FILE* fp = fopen("functioninit.c", "w");
    fprintf(fp, "#include<stdio.h>\n\n\n");
    fprintf(fp,"#include \"functioninit.h\"\n\n\n");
    fprintf(fp, "void functionIni(Cnnnet* net1){\n" );
    FILE* fi = fopen("parameterini", "r");
    double tmp;
    //fprintf(fp, "printf(\"0\\n\");\n");
    fprintf(fp, "    initRand(net1);\n");
    for(int i = 0; i < 6; i++){
        fscanf(fi, "%lf", &tmp);
        fprintf(fp, "    net1->level[0].neu[%d]->bias = %.9f;\n", i, tmp);
        //fprintf(fp, "printf(\"0\\n\");\n");
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < 5; k++){
                fscanf(fi,"%lf",&tmp);
                //fprintf(fp, "printf(\"*\\n\");\n");
                fprintf(fp, "    net1->level[0].neu[%d]->weights.arr[%d * 5 + %d] = %.9f;\n",
                 i, j, k, tmp);
            }
        }
    }
    //fprintf(fp, "printf(\"1\\n\");\n");

    for(int i = 0; i < 16; i++){
        fscanf(fi,"%lf",&tmp);
        fprintf(fp, "    net1->level[2].neu[%d]->bias = %.9f;\n", i, tmp);
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < 5; k++){
                fscanf(fi,"%lf",&tmp);
                fprintf(fp, "    net1->level[2].neu[%d]->weights.arr[%d * 5 + %d] = %.9f;\n",
            i, j, k, tmp);
            }
        }
    }
    //fprintf(fp, "printf(\"3\\n\");\n");

    for(int i = 0; i < 120; i++){
        fscanf(fi,"%lf", &tmp);
        fprintf(fp, "    net1->level[4].neu[%d]->bias = %.9f;\n", i, tmp);
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < 5; k++){
                fscanf(fi,"%lf",&tmp);
                fprintf(fp, "    net1->level[4].neu[%d]->weights.arr[%d * 5 + %d] = %.9f;\n",
             i, j, k, tmp);
            }
        }
    }
    //fprintf(fp, "printf(\"5\\n\");\n");

    for(int i = 0; i < 84; i++){
        fscanf(fi,"%lf",&tmp);
        fprintf(fp, "    net1->level[5].neu[%d]->bias = %.9f;\n", i, tmp);
        for(int j=0;j<120;j++){
            fscanf(fi,"%lf",&tmp);
            fprintf(fp, "    net1->level[5].neu[%d]->weights.arr[%d] = %.9f;\n",
             i, j , tmp);
        }
    }
    //fprintf(fp, "printf(\"6\\n\");\n");

    for(int i = 0; i < OUTPUTNUMBER; i++){
        fscanf(fi,"%lf",&tmp);
        fprintf(fp, "    net1->level[6].neu[%d]->bias = %.9f;\n", i, tmp);
        for(int j = 0; j < 84; j++){
            fscanf(fi,"%lf",&tmp);
            fprintf(fp, "    net1->level[6].neu[%d]->weights.arr[%d] = %.9f;\n", i, j, tmp);
        }
    }
    //fprintf(fp, "printf(\"7\\n\");\n");

    fprintf(fp,"}\n");
}
