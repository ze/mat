#include "matrix.h"
#include "mutate.h"

matrix eye(int n) {
    matrix id = new_matrix(n, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            id.data[i][j] = i == j ? 1 : 0;
        }
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

void upper_tri(matrix m) {
    for (int i = 0; i < m.rows; i++) {
        for (int j = i + 1; j < m.cols; j++) {
            double ratio = m.data[j][i] / m.data[i][i];

            const_row_operation(m, i, ratio, multiply);
            row_operation(m, i, j, subtraction);
            const_row_operation(m, i, ratio, divide);
        }
    }
}

void lower_tri(matrix m) {
    for (int i = m.rows - 1; i > 0; i--) {
        for (int j = i - 1; j > -1; j--) {
            double ratio = m.data[j][i] / m.data[i][i];

            const_row_operation(m, i, ratio, multiply);
            row_operation(m, i, j, subtraction);
            const_row_operation(m, i, ratio, divide);
        }
    }
}

double determinant(matrix m) {
    double det = 1;

    matrix n = copy(&m);
    upper_tri(n);

    for (int i = 0; i < n.rows && i < n.cols; i++) {
        det *= n.data[i][i];
    }

    free_data(n);
    return det;
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

matrix inverse(matrix m) {
    matrix inv = eye(m.rows);
    matrix n = copy(&m);

    for (int i = 0; i < n.rows; i++) {
        double pivot = n.data[i][i];
        const_row_operation(n, i, pivot, divide);
        const_row_operation(inv, i, pivot, divide);

        for (int j = i + 1; j < n.cols; j++) {
            double ratio = n.data[j][i] / n.data[i][i];

            const_row_operation(n, i, ratio, multiply);
            row_operation(n, i, j, subtraction);
            const_row_operation(n, i, ratio, divide);

            const_row_operation(inv, i, ratio, multiply);
            row_operation(inv, i, j, subtraction);
            const_row_operation(inv, i, ratio, divide);
        }
    }

    for (int i = n.rows - 1; i > 0; i--) {
        double pivot = n.data[i][i];
        const_row_operation(n, i, pivot, divide);
        const_row_operation(inv, i, pivot, divide);

        for (int j = i - 1; j > -1; j--) {
            double ratio = n.data[j][i] / n.data[i][i];

            const_row_operation(n, i, ratio, multiply);
            row_operation(n, i, j, subtraction);
            const_row_operation(n, i, ratio, divide);

            const_row_operation(inv, i, ratio, multiply);
            row_operation(inv, i, j, subtraction);
            const_row_operation(inv, i, ratio, divide);
        }
    }

    free_data(n);
    return inv;
}

/*
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
*/

void display_matrix(char *format, matrix m) {
    printf("%s =\n", format);
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            printf("%12.3G", m.data[i][j]);
        }
        printf("\n");
    }
}
