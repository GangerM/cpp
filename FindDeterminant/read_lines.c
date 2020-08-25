#include <stdio.h>
#include <stdlib.h>

void read_lines(FILE* fp, char*** lines, int* num_lines) {
    int i = 0; // i got help from daboi matthew da tutor
    int k = 0;// for matrix
    *lines = calloc(sizeof(char *), 9000);

    (*lines)[i] = calloc(sizeof(char), 9000); // allocates for 900 arrays

    while (!feof(fp)) {
        int c = fgetc(fp);
        if (c != '\n') {
            (*lines)[i][k++] = c;
        } else {
            (*lines)[i][k] = '\n';
            (*lines)[i][++k] = '\0';
            ++i;
            k = 0;
            (*lines)[i] = calloc(sizeof(char), 9000);
            (*num_lines)++;
        }
    }
}