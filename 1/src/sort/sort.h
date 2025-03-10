#ifndef SORT_H_
#define SORT_H_
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

typedef enum { OK,
    NULL_PTR_ERROR,
    LOGIC_ERROR } sorted_state;

typedef struct Data {
    void* array;
    ssize_t l;
    ssize_t r;
    size_t array_size;
    size_t size;
    bool (*compare)(const void*, const void*);
} Data;

// bool is_sorted(void* array, size_t array_size, size_t size, bool (*compare)(const void* l, const void* r));
void merge_sort(void* array, const ssize_t array_size, const ssize_t size, bool (*compare)(const void* l, const void* r));

#endif /* SORT_H_ */