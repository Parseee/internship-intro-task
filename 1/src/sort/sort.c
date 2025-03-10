#include <assert.h>
#include <pthread.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "sort.h"

// needed for pthread

bool is_sorted(void* array, size_t array_size, size_t size,
    bool (*compare)(const void*, const void*))
{
    assert(array && "");

    for (int i = 0; i < array_size - 1; ++i) {
        if (!compare(array + i * size, array + (i + 1) * size)) {
            return false;
        }
    }

    return true;
}

typedef struct MSData {
    void* array;
    const size_t l;
    const size_t r;
    const size_t width;
    bool (*compare)(const void* l, const void* r);
} MSData;

void merge(void* array, const size_t l, const size_t r, const size_t m, const size_t width, bool (*compare)(const void* l, const void* r))
{
    assert(array);

    size_t left_seg_len = m - l; // 0 ... n -> [0 ... m) [m ... r)
    size_t right_seg_len = r - m;
    // 1 2 3 4 5
    //   ^

    void* left_seg = calloc(left_seg_len, width);
    void* right_seg = calloc(right_seg_len, width);

    for (size_t i = 0; i < left_seg_len; ++i) {
        memcpy((left_seg + i * width), (array + (l + i) * width), width);
        // fprintf(stderr, "%d ", *(int*)(left_seg + i * width));
    }

    // fprintf(stderr, "\n");

    for (size_t i = 0; i < right_seg_len; ++i) {
        memcpy((right_seg + i * width), (array + (m + i) * width), width);
        // fprintf(stderr, "%d ", *(int*)(right_seg + i * width));
    }

    // fprintf(stderr, "\n");

    size_t i = 0;
    size_t j = 0;
    size_t pos = l;

    while (i < left_seg_len && j < right_seg_len) {
        if (compare((left_seg + i * width), (right_seg + j * width))) {
            memcpy((array + pos * width), (left_seg + i * width), width);
            ++i;
        } else {
            memcpy((array + pos * width), (right_seg + j * width), width);
            ++j;
        }
        // fprintf(stderr, "%d ", *(int*)(array + pos * width));
        ++pos;
    }

    while (i < left_seg_len) {
        memcpy((array + pos * width), (left_seg + i * width), width);
        // fprintf(stderr, "%d ", *(int*)(array + pos * width));
        ++pos;
        ++i;
    }

    while (j < right_seg_len) {
        memcpy((array + pos * width), (right_seg + j * width), width);
        // fprintf(stderr, "%d ", *(int*)(array + pos * width));
        ++pos;
        ++j;
    }
    // fprintf(stderr, "\n");

    free(left_seg);
    free(right_seg);
    return;
}

void* _merge_sort(void* msdata)
{
    assert(msdata);
    MSData* data = (MSData*)msdata;
    void* array = data->array;
    const size_t l = data->l;
    const size_t r = data->r;
    const size_t width = data->width;
    bool (*compare)(const void* l, const void* r) = data->compare;

    if (r - l > 1) {
        size_t m = (l + r) / 2;

        MSData ldata = { array, l, m, width, compare };
        MSData rdata = { array, m, r, width, compare };

        pthread_t lthread, rthread;
        // pthread_create(&lthread, NULL, _merge_sort, &ldata); // no need to return anything
        // pthread_create(&rthread, NULL, _merge_sort, &rdata);
        _merge_sort((void*)&ldata);
        _merge_sort((void*)&rdata);

        // pthread_join(lthread, NULL);
        // pthread_join(rthread, NULL);
        merge(array, l, r, m, width, compare);
    }

    return NULL;
}

// half segments -> [l, r)
void merge_sort(void* array, const ssize_t array_size, const ssize_t size, bool (*compare)(const void* l, const void* r))
{
    MSData data = {
        .array = array,
        .l = 0,
        .r = array_size,
        .width = size,
        .compare = compare
    };
    _merge_sort((void*)&data);
    return;
}