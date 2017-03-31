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
void display_matrix(char *format, matrix m);

// matrix properties
void upper_tri(matrix m);
void lower_tri(matrix m);
double determinant(matrix m);
matrix transpose(matrix m);
matrix inverse(matrix m);
matrix eye(int n);

// matrix operations
void swap_rows(matrix m, int i, int j);
double multiply(double x, double y);
double divide(double x, double y);
double addition(double x, double y);
double subtraction(double x, double y);
matrix mult(matrix m, matrix n);
matrix operation(matrix m, matrix n, double (*op)(double, double));
void const_operation(double num, matrix m, double (*op)(double, double));
void row_operation(matrix m, int i, int j, double (*op)(double ,double));
void const_row_operation(matrix m, int row, double num, double (*op)(double, double));
