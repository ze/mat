#include "tests.h"

const int TEST_TOTAL = 9;

char test_mats[][37] = {
    "[1,2,3][4,5,6][7,8,9]",
    "[5,4,1][6,9,1][7,7,7]",
    "[3.5,11.2][34.2,48.8]",
    "[9,8,1][6,8,4][3,2,3]",
    "[3,4,5,6][5,4,2,1][4,7,9,1][9,3,2,6]",
    "[1,2,3.5,5][6,7,8,10]",
    "[1,2][3,4][5,16][7,8]",
    "[5,2,3,4,1,6,7]",
    "[1][2][3][4][5][6][7]",
    "[911][4000][3][12]"
};

int dets[] = {0, 118, -212, 84, -607}; // rest are indeterminable matrices

char test_inv[][42] = {
    "[470,-176,-42][-294,235,8][-176,-58,176]",
    "[-229,52][161,-16]",
    "[190,-261,285][-71,285,-357][-142,71,285]"
};

void determinant_test() {
    for (int i = 0; i < 5; i++) {
        matrix m = parse_data(test_mats[i]);
        int det = determinant(m);
        display_matrix("matrix", m);
        printf("determinant: %d\n", det);
        free_data(m);

        assert(det == dets[i]);
    }
}

void transpose_test() {
    for (int i = 0; i < TEST_TOTAL; i++) {
        matrix m = parse_data(test_mats[i]);
        matrix t = transpose(m);

        for (int j = 0; j < m.rows; j++) {
            for (int k = 0; k < m.cols; k++) {
                assert((int) m.data[j][k] == (int) t.data[k][j]);
            }
        }

        free_data(m);
        free_data(t);
    }
}

void inverse_test() {
    for (int i = 1; i < 4; i++) {
        matrix test = parse_data(test_mats[i]);
        matrix inv = inverse(test);

        const_operation(1000, inv, multiply);

        free_data(test);
        test = parse_data(test_inv[i - 1]);

        display_matrix("inverse", inv);
        display_matrix("inverse-test", test);

        for (int j = 0; j < inv.rows; j++) {
            for (int k = 0; k < inv.cols; k++) {
                assert((int) inv.data[j][k] == (int) test.data[j][k]);
            }
        }

        free_data(inv);
        free_data(test);
    }
}

void matrix_test() {
    determinant_test();
    inverse_test();
    transpose_test();
}

int main() {
    matrix_test();
    vector_test();

    printf("All tests passed\n");
    return 0;
}
