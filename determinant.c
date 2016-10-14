#include "matrix.h"

double determinant(matrix m) {
    if (m.rows != m.cols) USAGE("input not NxN"); 
    if (m.rows == 1 && m.cols == 1) return m.data[0][0];
    if (m.rows == 2 && m.cols == 2) {
       return (m.data[0][0] * m.data[1][1]) - (m.data[0][1] * m.data[1][0]);
    }

    double det = 0;
    static int sign = -1;
    
    //Creation of submatrix
    matrix sub;
    sub.rows = sub.cols = m.rows - 1;

    sub.data = malloc(sizeof(double *) * sub.rows);
    for (int i = 0; i < m.rows - 1; i++) {
        *(sub.data + i) = malloc(sizeof(double) * sub.cols);
    }

    /* 
     * Construct new array from m.data.
     * Exclude current row and column and fill leftovers.
     */
    for (int i = 0; i < m.rows; i++) {
        for (int j = 1; j < m.rows; j++) {
            for (int k = 0, l = 0; k < m.rows; k++) {
                if (k == i) continue;
                sub.data[j - 1][l] = m.data[j][k];
                l++;
            }
        }
        sign *= -1; // Signs alternate between calls
        det += sign * m.data[0][i] * determinant(sub);
    }

    free_data(sub);
    return det;
}
