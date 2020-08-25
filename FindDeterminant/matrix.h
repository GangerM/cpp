//
// Created by Mitul Ganger on 1/27/2019.
//
#ifndef FINDDETERMINANT_MATRIX_H
#define FINDDETERMINANT_MATRIX_H
#include <stdio.h>

#endif //FINDDETERMINANT_MATRIX_H
typedef struct matrix_Struct{
    int num_cols, num_rows;
    double** matrix;
}Matrix;
double calculateSum(double *terms, int arraysize);

void NMatrix(double **oldMatrix, double ***newMatrix, int newMatrixSize, int index);

void read_file(FILE* fp, Matrix* myMatrix);

double calc_determinate(Matrix myMatrix);

void free_Matrix(double ***myMatrix, int num_rows);




