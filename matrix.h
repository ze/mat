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

double **set_data(int rows, int cols);
matrix new_matrix(int rows, int cols);
void free_data(matrix m);
void display_matrix(matrix m, char *format);
matrix inverse(matrix m);
matrix mult(matrix m, matrix n);
double add(double x, double y);
double sub(double x, double y);
matrix operation(matrix m, matrix n, double (*op)(double, double));
