#ifndef VECTOR_H_
#define VECTOR_H_

#include <stdlib.h>

#define VECTOR_ERROR_HANDLE(call_func, ...)                                \
    do {                                                                   \
        VECTOR_ERROR error_handler = call_func;                            \
        if (error_handler) {                                               \
            fprintf(stderr, "Error calling " #call_func ". error is %s\n", \
                Vector_strerror(error_handler));                           \
            __VA_ARGS__;                                                   \
            return error_handler;                                          \
            /*exit(EXIT_FAILURE);*/                                        \
        }                                                                  \
    } while (0)

typedef enum { VECTOR_OK,
    VECTOR_FAILURE,
    VECTOR_ALLOC_FAILURE } VECTOR_ERROR;

typedef struct Vector {
    int* data;
    size_t size;
    size_t capacity;
} Vector;

VECTOR_ERROR Vector_ctor(Vector* vector, size_t size);
VECTOR_ERROR Vector_dtor(Vector* vector);

VECTOR_ERROR Vector_print(const Vector* vector);

const char* Vector_strerror(const VECTOR_ERROR error);

#endif /* VECTOR_H_ */