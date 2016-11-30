#include "matrix.h"

double add(double x, double y) {
    return x + y;
}

double sub(double x, double y) {
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
