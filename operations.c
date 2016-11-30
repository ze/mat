#include "matrix.h"

matrix operation(matrix m, matrix n, matrix (*op)(matrix, matrix)) {
    return op(m, n);
}

matrix mult(matrix m, matrix n) {
    if (m.cols != n.rows) USAGE("matrices not multipliable");
    matrix prod;
    prod.rows = m.rows;
    prod.cols = n.cols;
    prod.data = set_data(prod.rows, prod.cols);

    for (int i = 0; i < prod.rows; i++) {
        for (int j = 0; j < prod.cols; j++) {
            for (int k = 0; k < m.cols; k++) {
                prod.data[i][j] += m.data[i][k] * n.data[k][j];
            }
        }
    }

    return prod;
}

matrix add(matrix m, matrix n) {
    if (m.rows != n.rows && m.cols != n.cols) USAGE("matrices not same size");
    matrix sum;
    sum.rows = m.rows;
    sum.cols = m.cols;
    sum.data = set_data(m.rows, m.cols);
    
    for (int i = 0; i < sum.rows; i++) {
        for (int j = 0; j < sum.cols; j++) {
            sum.data[i][j] = m.data[i][j] + n.data[i][j];
        }
    }

    return sum;
}

matrix sub(matrix m, matrix n) {
    if (m.rows != n.rows && m.cols != n.cols) USAGE("matrices not same size");
    matrix sub;
    sub.rows = m.rows;
    sub.cols = m.cols;
    sub.data = set_data(m.rows, m.cols);
    
    for (int i = 0; i < sub.rows; i++) {
        for (int j = 0; j < sub.cols; j++) {
            sub.data[i][j] = m.data[i][j] - n.data[i][j];
        }
    }

    return sub;
}
