#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include <ctype.h>
#include "matrix.h"

// helped by trevor the tutor (3 t's wow) in kemper basement what a god 1/28 gang gang

int main(int argc, char* argv[]){
    Matrix myMatrix; //create my matrix struct
    FILE *fp = NULL; //to make it null
    fp =   fopen(argv[1], "r"); //read only
    read_file(fp, &myMatrix);
    printf("The determinant is %.2f.", calc_determinate(myMatrix)); //prints the determinant, no bs
    free_Matrix(&myMatrix.matrix, myMatrix.num_rows); //delete it cuz case 10 bs
    fclose(fp); //get that shjt out of there bitch
    return 0; //cuz ints are lame
}









/*
int main(int argc, char *argv[]){
    //fp = fopen(argv[1],"r");
    printf("%d", 6);
    FILE* fp = NULL;
    fp = fopen("5X5TestMatrix.txt", "r"); //replace name of file with argv[1] when done testing

    double number;
    int num_rows, num_cols;

    fscanf(fp, "%d %d", &num_rows, &num_cols);
    int total = num_cols* num_rows;
    int i = 0, j = 0, x = 0;

    double *buf = (double*)malloc(total * sizeof(double));

    double** matrix = (double**)malloc(total * sizeof(double*));

    while(fscanf(fp, "%lf", &number) != EOF){
        buf[i] = number;
        i++;
    }
    i = 0;
    while (i < num_rows){
        j = 0;
        while(j < num_cols) {
            matrix[i][j] = buf[x];
            x++;
            j++;
        }
        i++;
        x++;
    }

    printf("%lf", matrix[2][3]);

    fclose(fp);
    return 0;
}
*/