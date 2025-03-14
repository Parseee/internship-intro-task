#ifndef MATRIX_H_
#define MATRIX_H_

#include <stdlib.h>

#define MATRIX_ERROR_HANDLE(call_func, ...)                                \
    do {                                                                   \
        MATRIX_ERROR error_handler = call_func;                            \
        if (error_handler) {                                               \
            fprintf(stderr, "Error calling " #call_func ". error is %s\n", \
                Matrix_strerror(error_handler));                           \
            __VA_ARGS__;                                                   \
            return error_handler;                                          \
        }                                                                  \
    } while (0)

typedef struct Matrix {
    int** data;
    size_t w_row;
    size_t w_col;
} Matrix;

typedef enum { MATRIX_OK,
    MATRIX_FAILURE } MATRIX_ERROR;

MATRIX_ERROR Matrix_ctor(Matrix* matrix);
MATRIX_ERROR Matrix_dtor(Matrix* matrix);

MATRIX_ERROR Matrix_random_fill(Matrix* matrix);
MATRIX_ERROR Matrix_multiply(Matrix* res, Matrix* left, Matrix* right);

const char* Matrix_strerror(const MATRIX_ERROR error);

#endif /* MATRIX_H_ */