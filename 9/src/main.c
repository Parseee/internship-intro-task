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

typedef struct Sub {
    int64_t val;
    size_t l_idx;
} Sub;

static Sub_arr process(Vector* vector)
{
    Sub_arr res = { .left = 0ull, .right = 0ull, .sum = 0ll };

    if (vector->size == 0) {
        return res;
    }

    size_t l = 0, r = 0;
    int64_t prev = -1;
    int64_t sum = 0;
    while (r < vector->size) {
        if (vector->data[r] > prev) {
            sum += vector->data[r];
            prev = vector->data[r];
        } else {
            if (res.sum < sum || (res.sum == sum && res.right - res.left + 1 > r - l + 1)) {
                res.left = l + 1;
                res.right = r;
                res.sum = sum;
                l = r;
                prev = -1;
                sum = 0;
            }
        }
        ++r;
    } 

    return res;
}

static size_t read_size(void)
{
    int64_t read_size = 0ll;
    scanf("%lld", &read_size);
    return read_size > 0ll ? (size_t)read_size : 0ull;
}