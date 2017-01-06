#include <assert.h>

#include "input.h"

const int TEST_TOTAL = 9;

char test_mats[][23] = {
    "[1,2,3][4,5,6][7,8,9]",
    "[5,4,1][6,9,1][7,7,7]",
    "[3.5,11.2][34.2,48.8]",
    "[9,8,1][6,8,4][3,2,3]",
    "[1,2,3.5,5][6,7,8,10]",
    "[1,2][3,4][5,16][7,8]",
    "[5,2,3,4,1,6,7]",
    "[1][2][3][4][5][6][7]",
    "[911][4000][3][12]"
};

int dets[] = {0, 119, -212, 84}; // rest are indeterminable matrices

char test_inv[][43] = {
    "[470,-176,-42][-294,235,8][-176,-58,176]",
    "[-230,52][161,-16]",
    "[190,-261,285][-71,285,-357][-142,71,285]"
};

void determinant_test() {
    for (int i = 0; i < 4; i++) {
        matrix m = parse_data(test_mats[i]);
        int det = determinant(m);
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
        matrix inv = inverse(parse_data(test_mats[i]));
        const_operation(1000, inv, multiply);
        matrix test = parse_data(test_inv[i - 1]);

        for (int j = 0; j < inv.rows; j++) {
            for (int k = 0; k < inv.cols; k++) {
                assert((int) inv.data[j][k] == (int) test.data[j][k]);
            }
        }

        free_data(inv);
        free_data(test);
    }
}


int main() {
    determinant_test();
    transpose_test();
    inverse_test();

    puts("All tests passed");
    return 0;
}
