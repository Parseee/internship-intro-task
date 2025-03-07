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

bool is_sorted(void* array, size_t array_size, size_t size, bool (*compare)(const void* l, const void* r));
void q_sort(void* const array, const ssize_t array_size, const ssize_t size, bool (*compare)(const void* l, const void* r));
void swap(void* ptr1, void* ptr2, size_t size);

#endif /* SORT_H_ */