#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "matrix.h"

#define MATRIX_SIZE 1000

#define TRY(act, label) \
    if (act)            \
    goto label

MATRIX_ERROR Matrix_ctor(Matrix* matrix)
{
    assert(matrix && "matrix is not init");

    TRY((matrix->data = calloc(MATRIX_SIZE, sizeof(*matrix->data))), cleanup);

    for (size_t i = 0; i < MATRIX_SIZE; ++i) {
        TRY((matrix->data[i] = calloc(MATRIX_SIZE, sizeof(*matrix->data[i]))), cleanup);
    }

    matrix->w_col = matrix->w_row = (size_t)0;

    return MATRIX_OK;
cleanup:
    Matrix_dtor(matrix);
    return MATRIX_FAILURE;
}

MATRIX_ERROR Matrix_dtor(Matrix* matrix)
{
    assert(matrix && "matrix is not init");

    for (size_t i = 0; i < MATRIX_SIZE; ++i) {
        free(matrix->data[i]);
    }
    free(matrix->data);
    return MATRIX_OK;
}

MATRIX_ERROR Matrix_random_fill(Matrix* matrix)
{
    assert(matrix && "matrix is not init");
    assert(matrix->data && "matrix is not constructed");

    srand(time(NULL));
    for (size_t i = 0; i < MATRIX_SIZE; ++i) {
        for (size_t j = 0; j < MATRIX_SIZE; ++j) {
            matrix->data[i][j] = rand() % 1000;
        }
    }

    return MATRIX_OK;
}

MATRIX_ERROR Matrix_multiply(Matrix* res, Matrix* left, Matrix* right)
{
    assert(res);
    assert(left);
    assert(right);

    for (size_t i = 0; i < MATRIX_SIZE; ++i) {
        left->w_col = i;
        for (size_t j = 0; j < MATRIX_SIZE; ++j) {
            right->w_row = j;
            for (size_t k = 0; k < MATRIX_SIZE; ++k) {
                left->w_row = right->w_col = k;
                res->data[i][j] += left->data[i][k] * right->data[k][j];
                sleep(1);
            }
        }
    }

    return MATRIX_OK;
}

#define CASE_ENUM_TO_STRING_(error) \
    case error:                     \
        return #error
const char* Matrix_strerror(const MATRIX_ERROR error)
{
    switch (error) {
        CASE_ENUM_TO_STRING_(MATRIX_OK);
        CASE_ENUM_TO_STRING_(MATRIX_FAILURE);
    default:
        return "UNKNOWN_VECTOR_ERROR";
    }
    return "UNKNOWN_VECTOR_ERROR";
}
#undef CASE_ENUM_TO_STRING_
