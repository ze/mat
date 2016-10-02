#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct {
    int rows, cols;
    double **data;
} matrix;

matrix set_data(char *mat);
void free_data(matrix m);
void input_check(char *input);
void usage(char *msg);
double **parse_input(char *mat, double **data);

int main(int argc, char **argv) {
    if (argc == 1) usage("missing input field");
    /*
    char *mat = argv[1];

    input_check(mat);
    if (argc == 2) {
        matrix m;
        m = set_data(mat);
        free_data(m);
    }
    */
    return 0;
}

void input_check(char *input) {
    if (!strpbrk(input, "[]")) usage("invalid input");
    int depth = 0;

    for (; *input; input++) {
        if (*input == '[') depth++;
        if (*input == ']') depth--;
        if (isalpha(*input) || (!isdigit(*input) && *(input + 1) == ']')) usage("invalid input");
        if (*input == '[' && *(input + 1) == ']') usage("empty matrix inputted");
    }

    if (depth != 0) {
        usage("inequal brackets");
    }   
} 

void usage(char *msg) {
    printf("matrix: %s\n", msg);
    puts("example: [1,2,3][4,5,6]");
    exit(1);
}

matrix set_data(char *mat) {
    char *temp = mat;
    matrix m;
    m.rows = m.cols = 0;

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
