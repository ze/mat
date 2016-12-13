#include "matrix.h"

void clear(matrix m) {
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            m.data[i][j] = 0;
        }
    }
}

void replace(matrix m, double old, double rep) {
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            if (m.data[i][j] == old) m.data[i][j] = rep;
        }
    }
}

void resize(matrix m, int rows, int cols) {
    m.data = realloc(m.data, sizeof(double *) * rows);

    for (int i = 0; i < rows; i++) {
        m.data[i] = realloc(m.data[i], sizeof(double) * cols);
    }

    m.rows = rows;
    m.cols = cols;
}
