#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "vector.h"

#define TRY(act, label) \
    if (act)            \
        goto label;

VECTOR_ERROR Vector_ctor(Vector* vector, size_t capacity)
{
    assert(vector && "vector is not init");

    vector->capacity = capacity;
    vector->size = capacity;
    TRY((vector->data = calloc(capacity, sizeof(*vector))) == NULL, cleanup);

    srand(time(NULL));
    for (size_t i = 0; i < vector->size; ++i) {
        // vector->data[i] = rand() % 100 * (rand() % 100 > 50 ? -1 : 1);
        scanf("%d", &vector->data[i]);
    }

    return VECTOR_OK;

cleanup:
    free(vector);
    return VECTOR_ALLOC_FAILURE;
}

VECTOR_ERROR Vector_dtor(Vector* vector)
{
    assert(vector && "vector is not init");

    free(vector->data);
    vector->data = NULL;

    return VECTOR_OK;
}

VECTOR_ERROR Vector_print(const Vector* vector)
{
    assert(vector);

    for (size_t i = 0; i < vector->size; ++i) {
        printf("%d ", vector->data[i]);
    }
    printf("\n");

    return VECTOR_OK;
}

#define CASE_ENUM_TO_STRING_(error) \
    case error:                     \
        return #error
const char* Vector_strerror(const VECTOR_ERROR error)
{
    switch (error) {
        CASE_ENUM_TO_STRING_(VECTOR_OK);
        CASE_ENUM_TO_STRING_(VECTOR_FAILURE);
        CASE_ENUM_TO_STRING_(VECTOR_ALLOC_FAILURE);
    default:
        return "UNKNOWN_VECTOR_ERROR";
    }
    return "UNKNOWN_VECTOR_ERROR";
}
#undef CASE_ENUM_TO_STRING_
