#include "text.h"

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>

static TEXT_ERROR Text_set_size(Text* const text, FILE** const fd)
{
    assert(text && "Text is NULL");
    assert(*fd && "input file ptr is NULL");

    if (fseek(*fd, 0, SEEK_END)) {
        perror("can't reach end of file");
        report_error(TEXT_FAILURE);
    }

    long data_size = 0;
    if ((data_size = ftell(*fd)) < 0) {
        perror("error while telling the location");
        report_error(TEXT_FAILURE);
    }
    text->data_size = (size_t)data_size + 1;

    if (fseek(*fd, 0, SEEK_SET)) {
        perror("can't reach beginning of file");
        report_error(TEXT_FAILURE);
    }

    return TEXT_OK;
}

static TEXT_ERROR Text_set_text_data(Text* text, FILE** filename)
{
    assert(text && "ptr");
    assert(*filename && "ptr");

    text->data = calloc(text->data_size, sizeof(*text->data));
    assert(text->data && "");

    if (fread(text->data, 1, text->data_size - 1, *filename) != (text->data_size - 1)) {
        perror("Error reading from file");
        return TEXT_FAILURE;
    }

    text->data[text->data_size - 1] = '\0';

    return TEXT_OK;
}

static TEXT_ERROR Text_split_data(Text* text)
{
    assert(text && "ptr");
    assert(text->data && "ptr");

    for (size_t i = 0; i < text->data_size; ++i) {
        if (text->data[i] == '\n') {
            text->data[i] = '\0';
        }
        if (text->data[i] == '\0') {
            ++text->text_size;
        }
    }

    return TEXT_OK;
}

static TEXT_ERROR Text_set_text(Text* text)
{
    assert(text && "ptr");
    assert(text->data && "ptr");
    assert(!text->text && "already assigned ptr");

    Text_split_data(text);

    text->text = calloc(sizeof(text->text), text->text_size);
    if (text->text == NULL) {
        return TEXT_FAILURE;
    }

    size_t text_idx = 1;
    text->text[0] = text->data;
    for (size_t i = 1; (i < text->data_size) && (text_idx <= text->text_size);
         ++i) {
        if (text->data[i - 1] == '\0') {
            text->text[text_idx] = (text->data) + i;
            ++text_idx;
        }
    }

    return TEXT_OK;
}

TEXT_ERROR Text_create(Text* text, const char* const filename)
{
    assert(text && "Text is NULL");
    assert(filename && "Filename is NULL");

    FILE* fd = fopen(filename, "r");
    if (!fd) {
        perror("cant open file");
        return TEXT_FAILURE;
    }

    Text_set_size(text, &fd); // TODO: how to return error
    Text_set_text_data(text, &fd); // TODO: how to return error
    Text_set_text(text); // TODO: how to return errort

    if (!fclose(fd)) {
        perror("Error closing file");
        return TEXT_FAILURE;
    }

    return TEXT_OK;
}

TEXT_ERROR Text_fwrite(Text* text, const char* filename)
{
    assert(text);
    assert(filename);

    FILE* output = 0;
    if ((output = fopen(filename, "a+")) == NULL) {
        perror("Error opening output file");
        return TEXT_FAILURE;
    }

    for (size_t i = 0; i < text->text_size; ++i) {
        fprintf(output, "%s\n", text->text[i]);
    }

    if (fclose(output)) {
        perror("Error closing output file");
    }

    return TEXT_OK;
}

TEXT_ERROR Text_cwrite(Text* text)
{
    assert(text);
    for (size_t i = 0; i < text->text_size; ++i) {
        printf("%s\n", text->text[i]);
    }
    return TEXT_OK;
}

TEXT_ERROR Text_sort(Text* text, void (*sorting)(void* const array, const ssize_t array_size, const ssize_t size, bool (*compare)(const void* l, const void* r)))
{
    assert(text);
    sorting(text->text, text->text_size, sizeof(*text->text), Text_strcmp);
    return TEXT_OK;
}

TEXT_ERROR Text_kill(Text* text)
{
    assert(text && "Text is NULL");
    assert(text->data && "");
    free(text->data);
    text->data = NULL;

    free(text->text);
    text->text = NULL;

    text->text_size = 0;
    text->data_size = 0;

    return TEXT_OK;
}

static char* ignore_n(const char* str, char* endptr, size_t* size)
{
    endptr = (char*)str;
    for (; *endptr != '\0'; ++endptr) {
        if (isalnum(*endptr))
            ++(*size);
    }

    char* format = malloc(sizeof(char) * (*size) + 1);
    assert(format);

    size_t format_idx = 0;
    for (char* ptr = (char*)str; *ptr != '\0'; ++ptr) {
        if (isalnum(*ptr)) {
            format[format_idx++] = *ptr;
        }
    }

    format[*size] = '\0';

    return format;
}

bool Text_strcmp(const void* l_t, const void* r_t)
{
    assert(l_t);
    assert(r_t);

    const char* l = *(char**)l_t;
    const char* r = *(char**)r_t;

    size_t len_l = 0;
    char* end_l = NULL;
    char* new_l = ignore_n(l, end_l, &len_l);

    size_t len_r = 0;
    char* end_r = NULL;
    char* new_r = ignore_n(r, end_r, &len_r);

    bool flag = false;
    if (len_l == len_r) {
        for (int i = 0; i < len_l; ++i) {
            if (tolower(new_l[i]) > tolower(new_r[i])) {
                flag = false;
                break;
            }
        }
        flag = true;
    } else if (len_l < len_r) {
        flag = true;
    } else {
        flag = false;
    }

    free(new_l);
    free(new_r);
    return flag;
}
