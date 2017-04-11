#include "tests.h"

void vector_test() {
    vector *v = new_vector(2);
    vector_add(v, 10);
    vector_add(v, 15.3);
    vector_add(v, 1000);
    vector_add(v, 0.913);
    vector_add(v, 23.459);

    for (int i = 0; i < v->size; i++) {
        printf("vector[%d]: %.2f\n", i, v->data[i]);
    }

    vector_clear(v);
}

