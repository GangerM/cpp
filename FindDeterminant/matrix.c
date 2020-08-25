//
// Created by Mitul Ganger on 1/27/2019. GANG GANG
//
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

void free_Matrix(double ***myMatrix, int num_rows){
    for(int i = 0; i < num_rows; ++i) free((*myMatrix)[i]);
    free(*myMatrix);
    *myMatrix = NULL; //finish getting the matrix out of da memory
}

void read_file(FILE* fp, Matrix* myMatrix){
    double bread;
    int num_rows, num_cols;
    fscanf(fp, "%d %d", &num_rows, &num_cols);
    (*myMatrix).num_rows = num_rows, (*myMatrix).num_cols = num_cols;
    double** finalcountdownmatrix = (double**) malloc(num_rows * sizeof(double*));
    for(int i = 0; i < num_rows; i++) finalcountdownmatrix[i] = (double*) malloc(num_cols * sizeof(double*));
    int rowcount = 0, colcount = 0;
    while(1){
        fscanf(fp, "%lf", &bread);
        if( bread == EOF  ) break;
        finalcountdownmatrix[rowcount][colcount] = bread, colcount ++;
        if(colcount == num_rows) rowcount++, colcount = 0;
        if(rowcount == num_rows) break;
    }
    myMatrix->matrix = finalcountdownmatrix;
}



double calc_determinate(Matrix myMatrix){
    if(myMatrix.num_rows == 2){
        double first = myMatrix.matrix[0][0] * myMatrix.matrix[1][1], second = myMatrix.matrix[0][1] * myMatrix.matrix[1][0];
        return first - second;
    }
    int SofM = myMatrix.num_rows;
    double terms[SofM];
    for(int i=0; i < SofM; i++){
        Matrix SM;
        int NSofM = SofM - 1;
        SM.num_rows = NSofM, SM.num_cols = NSofM;
        double** holdit = (double**) malloc(NSofM * sizeof(double*));
        for(int j = 0; j < NSofM; j++) holdit[j] = (double*) malloc(NSofM * sizeof(double));
        double newterm, something = myMatrix.matrix[0][i];
        double** oldmatrixholder =  myMatrix.matrix;
        NMatrix(oldmatrixholder, &holdit, SofM - 1, i);
        SM.matrix = holdit;
        newterm = something * calc_determinate(SM), terms[i] = newterm;
        free_Matrix(&holdit, NSofM);
    }
    return calculateSum(terms, SofM);
}

double calculateSum(double *terms, int arraysize){

    double tot = terms[0];
    int tf = 1;
    for(int i=1;i<arraysize;i++){
        if(tf == 0) tot += terms[i], tf = 1;
        else tot = tot - terms[i], tf = 0;
    }


    return tot;
}
void NMatrix(double **oldmatrix, double ***newmatrix, int newmatrixsize, int index){
    int oldcol = 0, oldrow = 1, x = 0;
    for(int i=0; i<newmatrixsize; i++) {
        for (int j = 0; j < newmatrixsize; j++) {
            if (oldcol == index) oldcol++;
            (*newmatrix)[i][j] = oldmatrix[oldrow][oldcol], oldcol++, x++;
        }
        oldrow++, oldcol = 0;
    }
}

