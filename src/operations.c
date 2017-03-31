#include "matrix.h"

void swap_rows(matrix m, int i, int j) {
    double *temp = m.data[i];
    m.data[i] = m.data[j];
    m.data[j] = temp;
}

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

void const_operation(double num, matrix m, double (*op)(double, double)) {
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            m.data[i][j] = op(m.data[i][j], num);
        }
    }
}

void row_operation(matrix m, int row, int apply, double (*op)(double, double)) {
    for (int i = 0; i < m.cols; i++) {
        m.data[apply][i] = op(m.data[apply][i], m.data[row][i]);
    }
}

void const_row_operation(matrix m, int row, double num, double (*op)(double, double)) {
    for (int i = 0; i < m.cols; i++) {
        m.data[row][i] = op(m.data[row][i], num);
    }
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
