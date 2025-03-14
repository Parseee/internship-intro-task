#pragma once
#ifndef TEXT_H
#define TEXT_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG

typedef enum { TEXT_OK,
    TEXT_FAILURE } TEXT_ERROR;

#define report_error(error)                                             \
    do {                                                                \
        fprintf(stderr, #error " in file: %s, on line: %d\n", __FILE__, \
            __LINE__);                                                  \
        return error;                                                   \
    } while (0)

typedef struct {
    char* data;
    char** text;
    size_t data_size;
    size_t text_size;
} Text;

TEXT_ERROR Text_create(Text* text, const char* const filename);
TEXT_ERROR Text_kill(Text* text);
TEXT_ERROR Text_sort(Text* text, void (*sorting)(void* const array, const ssize_t array_size, const ssize_t size, bool (*compare)(const void* l, const void* r)));

TEXT_ERROR Text_cwrite(Text* text);
TEXT_ERROR Text_fwrite(Text* text, const char* filename);

bool Text_strcmp(const void* l, const void* r);

#endif /* TEXT_H */