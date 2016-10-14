#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct matrix {
    int rows, cols;
    double **data;
} matrix;

#define USAGE(msg) \
    do { \
    printf("matrix: %s\n", msg); \
    exit(1); \
    } while (0);

double determinant(matrix m);
void free_data(matrix m);
