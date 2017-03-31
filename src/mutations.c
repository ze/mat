#include <string.h>

#include "matrix.h"

double **set_data(int rows, int cols) {
    double **data = malloc(sizeof(double *) * rows);
    for (int i = 0; i < rows; i++) {
        *(data + i) = malloc(sizeof(double) * cols);
    }

    return data;
}

matrix copy(matrix *m) {
    matrix n = new_matrix(m->rows, m->cols);

    for (int i = 0; i < n.rows; i++) {
        memcpy(n.data[i], m->data[i], sizeof(double) * n.cols);
    }

    return n;
}

matrix new_matrix(int rows, int cols) {
    matrix new;
    new.rows = rows;
    new.cols = cols;
    new.data = set_data(rows, cols);

    return new;
}

void free_data(matrix m) {
    for (int i = 0; i < m.rows; i ++) {
        free(*(m.data + i));
    }

    free(m.data);
}

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
