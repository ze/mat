#include "matrix.h"

double multiply(double x, double y) {
    return x * y;
}

double divide(double x, double y) {
    return x / y;
}

double addition(double x, double y) {
    return x + y;
}

double subtraction(double x, double y) {
    return x - y;
}

matrix operation(matrix m, matrix n, double (*op)(double, double)) {
    if (m.rows != n.rows && m.cols != n.cols) USAGE("matrices not same size");
    
    matrix modified = new_matrix(m.rows, m.cols);

    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            modified.data[i][j] = op(m.data[i][j], n.data[i][j]);
        }
    } 
    
    return modified;
}

matrix const_operation(int num, matrix m, double (*op)(double, double)) {
    matrix modified = new_matrix(m.rows, m.cols); 

    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            modified.data[i][j] = op(m.data[i][j], num);
        }
    }

    return modified;
}

matrix mult(matrix m, matrix n) {
    if (m.cols != n.rows) USAGE("matrices not multipliable");

    matrix prod = new_matrix(m.rows, n.cols);

    for (int i = 0; i < prod.rows; i++) {
        for (int j = 0; j < prod.cols; j++) {
            for (int k = 0; k < m.cols; k++) {
                prod.data[i][j] += m.data[i][k] * n.data[k][j];
            }
        }
    }

    return prod;
}
