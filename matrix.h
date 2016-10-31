#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct matrix {
    int rows, cols;
    double **data;
} matrix;

#define USAGE(msg) \
    do { \
    printf("matrix: %s\n", msg); \
    exit(1); \
    } while (0);

matrix inverse(matrix m);
void display_matrix(matrix m, char *format);
double **set_data(int rows, int cols);
void free_data(matrix m);
