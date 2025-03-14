#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// #include "error/error.h"
#include "matrix/matrix.h"

static int process(Matrix* left, Matrix* right, Matrix* res);
void signal_handler(int signal);

struct Ret_data {
    Matrix* left;
    Matrix* right;
} ret_data;

int main(void)
{
    Matrix left;
    Matrix right;
    MATRIX_ERROR_HANDLE(Matrix_ctor(&left));
    MATRIX_ERROR_HANDLE(Matrix_ctor(&right));
    ret_data.left = &left;
    ret_data.right = &right;

    Matrix res;
    MATRIX_ERROR_HANDLE(Matrix_ctor(&res));

    int error = process(&left, &right, &res);

    if (error) {
        fprintf(stderr, "%s\n", Matrix_strerror(error));
        return EXIT_FAILURE;
    }

    MATRIX_ERROR_HANDLE(Matrix_dtor(&left));
    MATRIX_ERROR_HANDLE(Matrix_dtor(&right));
    MATRIX_ERROR_HANDLE(Matrix_dtor(&res));

    return 0;
}

static int process(Matrix* left, Matrix* right, Matrix* res)
{
    assert(left);
    assert(right);
    assert(res);

    MATRIX_ERROR_HANDLE(Matrix_random_fill(left));
    MATRIX_ERROR_HANDLE(Matrix_random_fill(right));

    signal(SIGINT, signal_handler);

    MATRIX_ERROR_HANDLE(Matrix_multiply(res, left, right));

    return 0;
}

void signal_handler(int sig)
{
    if (sig == SIGINT) {
        printf("\nCurrent indices for left matrix: %lu, %lu\n", ret_data.left->w_col, ret_data.left->w_row);
        printf("Current indices for right matrix: %lu, %lu\n", ret_data.right->w_col, ret_data.right->w_row);
        signal(SIGINT, SIG_DFL);
    }
}
