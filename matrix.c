#include <ctype.h>
#include <string.h>

#include "matrix.h"

void input_check(char *input);
matrix set_data(char *mat);
double **parse_input(char *mat, double **data);

int main(int argc, char **argv) {
    if (argc == 1) USAGE("missing input field");
    char *mat = argv[1];

    input_check(mat);
    if (argc == 2) {
        matrix m = set_data(mat);
        double det = determinant(m);
        printf("determinant: %.2f\n", det);
        free_data(m);
    }
    return 0;
}

void input_check(char *input) {
    if (!strpbrk(input, "[]") || *input != '[') USAGE("invalid input");
    int depth = 0;

    // Input correctness check
    for (; *input; input++) {
        if (*input == '[') depth++;
        if (*input == ']') depth--;
        if (isalpha(*input) || (!isdigit(*input) && *(input + 1) == ']')) {
            USAGE("invalid input");
        }
        if (*(input + 1) == '[' && isdigit(*input)) USAGE("invalid input");
        if (*input == '[' && *(input + 1) == ']') USAGE("empty matrix inputted");
    }
    if (*(input - 1) != ']') USAGE("invalid input");

    if (depth != 0) USAGE("inequal brackets");
} 

matrix set_data(char *mat) {
    char *temp = mat;
    matrix m;
    m.rows = m.cols = 0;

    // Get rows and columns from input
    for (; *temp; temp++) {
        if (*temp == '[') m.rows++;	
        if (*temp == ',') m.cols++;	
    }
    if (m.rows == 0) m.rows++;
    m.cols = (m.cols + m.rows) / m.rows;

    m.data = malloc(sizeof(double *) * m.rows);	
    for (int i = 0; i < m.rows; i++) {
        *(m.data + i) = malloc(sizeof(double) * m.cols);
    }

    m.data = parse_input(mat, m.data);
    return m;
}

void free_data(matrix m) {
    for (int i = 0; i < m.rows; i ++) {
        free(*(m.data + i));
    }

    free(m.data);
}

double **parse_input(char *mat, double **data) {
    int depth = -1;
    char *delimit = mat;
    double n;

    // Place contents of mat into data
    while (*delimit) {
        for (int i = 0; *delimit != ']'; i++) {
            n = strtod(mat, &delimit);
            if (*delimit == '[') {
                delimit++;
                depth++;
            }
            if (*delimit == ',') delimit++;
            (*mat != '[') ? *(*(data + depth) + i) = n : i--;
            mat = delimit;
        }
        mat = ++delimit;
    }

    return data;
}
