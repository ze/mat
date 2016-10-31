#include <ctype.h>

#include "matrix.h"

void input_check(char *in);
matrix parse_data(char *mat);
double **parse_input(char *mat, double **data);

int main(int argc, char **argv) {
    if (argc == 1) USAGE("missing input field");
    /*
    char *mat = argv[1];

    input_check(mat);
    if (argc == 2) {
        matrix m = parse_data(mat);
        matrix inv = inverse(m);
        display_matrix(inv, "inverse");

        free_data(inv);
        free_data(m);
    }
    */
    return 0;
}

void input_check(char *in) {
    if (!strpbrk(in, "[]") || *in != '[') USAGE("invalid input");
    int depth = 0;

    // Input correctness check
    for (; *in; in++) {
        if (*in == '[') depth++;
        if (*in == ']') depth--;
        if (isalpha(*in) || (!isdigit(*in) && *(in + 1) == ']')) {
            USAGE("invalid input");
        }
        if (*(in + 1) == '[' && isdigit(*in)) USAGE("invalid input");
        if (*in == ',' && *(in + 1) == ',') USAGE("invalid input");
        if (*in == '[' && *(in + 1) == ']') USAGE("empty matrix inputted");
    }
    if (*(in - 1) != ']') USAGE("invalid input");

    if (depth != 0) USAGE("inequal brackets");
} 

matrix parse_data(char *mat) {
    char *temp = mat;
    matrix m;
    m.rows = m.cols = 0;

    // Get rows and columns from input
    for (; *temp; temp++) {
        if (*temp == '[') m.rows++;	
        if (*temp == ',') m.cols++;	
    }
    if (m.rows == 0) m.rows++;
    m.cols = (m.cols + m.rows) / m.rows + ((m.cols + m.rows) % m.rows != 0);

    m.data = parse_input(mat, set_data(m.rows, m.cols));
    return m;
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
