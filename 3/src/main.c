#include <ctype.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sort/sort.h"
#include "text/text.h"

int main(int argc, char** argv)
{
    Text tx = (Text) { .data = NULL, .text = NULL, .data_size = 0 };

    char* input_filename = NULL;
    char* output_filename = NULL;
    void (*sorting)(void* const array, const ssize_t array_size, const ssize_t size, bool (*compare)(const void*, const void*)) = q_sort;

    int c = 0;
    while ((c = getopt(argc, argv, "i:o:s:")) != -1) {
        switch (c) {
        case ('i'):
            input_filename = strdup(optarg);
            break;

        case ('o'):
            output_filename = strdup(optarg);
            break;

        case ('s'):
            if (strcmp(optarg, "bubble") == 0) {
                sorting = bubble_sort;
            } else if (strcmp(optarg, "shaker") == 0) {
                sorting = shaker_sort;
            } else if (strcmp(optarg, "shell") == 0) {
                sorting = shell_sort;
            } else if (strcmp(optarg, "qsort") == 0) {
                sorting = q_sort;
            } else {
                fprintf(stderr, "sorting provided is bad\n");
            }

            break;

        case ('?'):
            if (optopt == 's')
                fprintf(stderr, "option -%c requires an argument\n", optopt);
            else if (isprint(optopt)) {
                fprintf(stderr, "unknown option -%c\n", optopt);
            } else {
                fprintf(stderr, "unknown option character -%x\n", optopt);
            }

        default:
            printf("durachok\n");
            exit(0);
        }
    }

    if (!input_filename) {
        fprintf(stderr, "Input filename is required\n");
        return EXIT_FAILURE;
    }
    Text_create(&tx, input_filename);

    Text_sort(&tx, sorting);

    if (!output_filename) {
        fprintf(stderr, "Output filename is required\n");
        return EXIT_FAILURE;
    }

    Text_fwrite(&tx, output_filename);
    Text_cwrite(&tx);

    Text_kill(&tx);

    free(output_filename);
    output_filename = NULL;
    free(input_filename);
    input_filename = NULL;

    return EXIT_SUCCESS;
}
