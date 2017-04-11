#include <string.h>
#include <stdarg.h>

#include "tests.h"

vector *new_vector(size_t capacity) {
    vector *v = malloc(sizeof(vector *));
    v->data = malloc(sizeof(double) * capacity);
    v->capacity = capacity;
    v->size = 0;

    return v;
}

void vector_add(vector *v, double item) {
    if (v->size + 1 > v->capacity) {
        if (v->capacity != 0) {
            v->capacity *= 2;
        } else {
            v->capacity = 1;
        }

        v->data = realloc(v->data, sizeof(double) * v->capacity);
    }

    v->data[v->size++] = item;
}

void vector_clear(vector *v) {
    free(v->data);
    free(v);
}

