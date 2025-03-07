#include <pthread.h>
#include <stdio.h>

#include "vector/vector.h"

static size_t read_size(void);


int main(void)
{
    printf("enter array_size: ");
    size_t array_size = read_size();
    Vector vector;
    VECTOR_ERROR_HANDLE(Vector_ctor(&vector, array_size));

    VECTOR_ERROR_HANDLE(Vector_dtor(&vector));

    return 0;
}

static size_t read_size(void)
{
    int64_t array_size = 0;
    scanf("%lld", &array_size);

    return array_size >= 0 ? array_size : 0;
}