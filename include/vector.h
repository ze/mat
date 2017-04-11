#pragma once

typedef struct vector {
    double *data;
    size_t capacity;
    size_t size;
} vector;

vector *new_vector();
void vector_add(vector *v, double item);
void vector_clear(vector *v);
