#include <assert.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#include "sort/sort.h"
#include "vector/vector.h"

static size_t read_size(void);
static bool cmp(const void*, const void*);
static void print_vector(Vector* vector);

int main(void)
{
    printf("enter array_size: ");
    size_t array_size = read_size();
    Vector vector;
    VECTOR_ERROR_HANDLE(Vector_ctor(&vector, array_size));

    print_vector(&vector);

    time_t begin = clock();

    merge_sort(vector.data, vector.size, sizeof(*vector.data), cmp);

    time_t end = clock();

    print_vector(&vector);

    printf("\n%f\n", (double)(end - begin) / CLOCKS_PER_SEC);

    VECTOR_ERROR_HANDLE(Vector_dtor(&vector));

    return 0;
}

static size_t read_size(void)
{
    int64_t array_size = 0;
    scanf("%lld", &array_size);

    return array_size >= 0 ? array_size : 0;
}

static bool cmp(const void* l, const void* r)
{
    return *(const int*)l < *(const int*)r;
}

static void print_vector(Vector* vector)
{
    assert(vector && "vector is not init");

    for (size_t i = 0; i < vector->size; ++i) {
        printf("%d ", vector->data[i]);
    }
    printf("\n");
    return;
}