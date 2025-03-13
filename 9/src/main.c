#include <stdint.h>
#include <stdio.h>

// #include "error/error.h"
#include "vector/vector.h"

#define MAX(a, b) a < b ? b : a

typedef struct Sub_arr {
    size_t left;
    size_t right;
    int64_t sum;
} Sub_arr;

static Sub_arr process(Vector* vector);
static size_t read_size(void);

int main(void)
{
    size_t vector_size = read_size();

    Vector vector;
    VECTOR_ERROR_HANDLE(Vector_ctor(&vector, vector_size));

    VECTOR_ERROR_HANDLE(Vector_print(&vector));

    Sub_arr res = process(&vector);

    printf("left: %lu, right: %lu, max sum: %lli", res.left, res.right, res.sum);

    VECTOR_ERROR_HANDLE(Vector_dtor(&vector));
    return 0;
}

static Sub_arr process(Vector* vector)
{
    Sub_arr res = { .left = 0ull, .right = 0ull, .sum = 0ll };

    if (vector->size == 0) {
        return res;
    }

    int64_t prev_num = 0;
    int64_t sum = 0;
    size_t l = 0;
    size_t r = 0;
    size_t max_dif = 0;

    while (r < vector->size) {
        if (vector->data[r] > prev_num) {
            sum += vector->data[r];
        } else {
            size_t dif = r - l + 1;
            if (res.sum < sum) {
                res.sum = sum;
                res.left = l + 1;
                res.right = r + 1;
                max_dif = dif;
            } else if (res.sum == sum && max_dif < dif) {
                res.left = l + 1;
                res.right = r + 1;
                max_dif = dif;
            }
            sum = 0;
            l = r;
        }
        prev_num = vector->data[r] > 0 ? vector->data[r] : 0;
        ++r;
    }

    return res;
}

static size_t read_size(void)
{
    int64_t array_size = 0;
    scanf("%lld", &array_size);

    return array_size >= 0 ? array_size : 0;
}