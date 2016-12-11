#include "matrix.h"

double **set_data(int rows, int cols) {
    double **data = malloc(sizeof(double *) * rows);
    for (int i = 0; i < rows; i++) {
        *(data + i) = malloc(sizeof(double) * cols);
    }

    return data;
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

matrix identity(int n) {
    matrix id = new_matrix(n, n);
    for (int i = 0; i < n; i++) {
        id.data[i][i] = 1;
    }

    return id;
}

matrix const_matrix(int rows, int cols, int num) {
    matrix constants = new_matrix(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            constants.data[i][j] = num;
        }
    }

    return constants;
}

matrix rand_matrix(int rows, int cols, int bounds) {
    matrix random = new_matrix(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            random.data[i][j] = rand() % bounds;
        }
    }

    return random;
}

double det_recursive(matrix m, int sign) {
    if (m.rows != m.cols) USAGE("input not NxN");
    if (m.rows == 1 && m.cols == 1) return m.data[0][0];
    if (m.rows == 2 && m.cols == 2) {
       return (m.data[0][0] * m.data[1][1]) - (m.data[0][1] * m.data[1][0]);
    }

    // creation of submatrix
    matrix sub = new_matrix(m.rows - 1, m.rows - 1);

    double det = 0;
    /**
     *  construct new array from m.data.
     *  exclude current row and column and fill leftovers.
     */
    for (int i = 0; i < m.rows; i++) {
        for (int j = 1; j < m.rows; j++) {
            for (int k = 0, l = 0; k < m.rows; k++) {
                if (k == i) continue;
                sub.data[j - 1][l] = m.data[j][k];
                l++;
            }
        }
        det += sign * m.data[0][i] * det_recursive(sub, sign);
        sign *= -1;
    }

    free_data(sub);
    return det;
}

double determinant(matrix m) {
    return det_recursive(m, 1);
}

matrix transpose(matrix m) {
    int rows = m.rows != m.cols ? m.cols : m.rows;
    int cols = m.rows != m.cols ? m.rows : m.cols;
    matrix t = new_matrix(rows, cols);

    for (int i = 0; i < t.rows; i++) {
        for (int j = 0; j < t.cols; j++) {
            t.data[i][j] = m.data[j][i];
        }
    }

    return t;
}

matrix adjugate(matrix m) {
    matrix *sub = malloc(sizeof(matrix) * m.rows * m.cols);
    for (int i = 0; i < m.rows * m.cols; i++) {
        sub[i] = new_matrix(m.rows - 1, m.cols - 1);
    }

    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            for (int k = 0, x = 0; k < m.rows; k++) {
                if (k == i) {
                    x++;
                    continue;
                }
                for (int l = 0, y = 0; l < m.cols; l++) {
                    if (l == j)  {
                        y++;
                        continue;
                    }
                    sub[i * m.rows + j].data[k - x][l - y] = m.data[k][l];
                }
            }
        }
    }

    matrix adj = new_matrix(m.rows, m.cols);
    int sign = 1;

    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            adj.data[i][j] = sign * determinant(sub[i * m.rows + j]);
            sign *= -1;
        }
    }

    for (int i = 0; i < m.rows * m.cols; i++) {
        free_data(sub[i]);
    }
    free(sub);

    return transpose(adj);
}

matrix inverse(matrix m) {
    double det = determinant(m);
    if (det == 0) USAGE("non invertable, determinant is zero");

    matrix inv = adjugate(m);
    const_operation(det, inv, divide);

    if (inv.rows == 2 && inv.cols == 2) {
        inv.data[0][1] *= -1;
        inv.data[1][1] *= -1;
    }

    return inv;
}

void display_matrix(matrix m, char *format) {
    printf("%s =\n", format);
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            printf("%12.3G", m.data[i][j]);
        }
        puts("");
    }
}
