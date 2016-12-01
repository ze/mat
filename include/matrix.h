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

// matrix creation and deletion
double **set_data(int rows, int cols);
matrix new_matrix(int rows, int cols);
void free_data(matrix m);
matrix rand_matrix(int rows, int cols, int bounds);
matrix const_matrix(int rows, int cols, int num);

// matrix displaying
void display_matrix(matrix m, char *format);

// matrix properties
matrix inverse(matrix m);

// matrix operations
double multiply(double x, double y);
double divide(double x, double y);
double add(double x, double y);
double sub(double x, double y);
matrix mult(matrix m, matrix n);
matrix operation(matrix m, matrix n, double (*op)(double, double));
matrix const_operation(int num, matrix m, double (*op)(double, double));
