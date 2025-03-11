#include <ctype.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error/error.h"

#define ELBRUS 5642
#define MAX_OPT_LEN 4 // 1c+, 2c+, 2c3, 4c, 8c, 16c

const char* good_elbrus_opts[];

static void print_usage(const char* prog_name);
static int validate_elbrus(const char* optarg);

int main(int argc, char** argv)
{
    int m_flag = 0;
    int c_flag = 0;
    int s_flag = 0;
    int t_flag = 0;
    int elbrus_flag = 0;
    char elbrus_agr[MAX_OPT_LEN];

    struct option long_options[] = {
        { "m-opt", no_argument, NULL, 'm' },
        { "c-opt", no_argument, NULL, 'c' },
        { "s-opt", no_argument, NULL, 's' },
        { "t-opt", no_argument, NULL, 't' },
        { "elbrus", required_argument, &elbrus_flag, ELBRUS },
        { NULL, 0, NULL, 0 } // End of options
    };

    int opt = 1;
    while ((opt = getopt_long(argc, argv, "mcst", long_options, NULL)) != -1) {
        switch (opt) {
        case ('m'):
            m_flag = 1;
            break;

        case ('c'):
            c_flag = 1;
            break;

        case ('s'):
            s_flag = 1;
            break;

        case ('t'):
            t_flag = 1;
            break;

        case (0):
            if (elbrus_flag == ELBRUS) {
                if (!validate_elbrus(optarg)) {
                    errx(EXIT_FAILURE, "Bad option \"%s\" for elbrus", optarg);
                }
                strncpy(elbrus_agr, optarg, MAX_OPT_LEN);
            }
            break;

        case ('?'):
            if (isprint(optopt)) {
                warnx("unknown option -%c\n", optopt);
            } else {
                warnx("unknown option character -%x\n", (unsigned)optopt);
            }
            break;

        default:
            print_usage(argv[0]);
            exit(0);
        }
    }

    printf("Correct options: ");
    m_flag ? (printf("m ")) : 0;
    c_flag ? (printf("c ")) : 0;
    s_flag ? (printf("s ")) : 0;
    t_flag ? (printf("t ")) : 0;
    elbrus_flag ? (printf("elbrus=%s", elbrus_agr)) : 0;
    printf("\n");

    if (optind < argc) {
        printf("Non-option arguments: ");
        for (int i = optind; i < argc; i++) {
            printf("%s ", argv[i]);
        }
    }
    return 0;
}

static void print_usage(const char* prog_name)
{
    fprintf(stderr, "Usage: %s [-mcst] [-b <arg>] [file]\n", prog_name);
    return;
}

static int validate_elbrus(const char* optarg)
{
    if (optarg == NULL)
        return 0;
    for (int i = 0; good_elbrus_opts[i] != NULL; i++) {
        if (strcmp(optarg, good_elbrus_opts[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

const char* good_elbrus_opts[] = {
    "1c+",
    "2c+",
    "2c3",
    "4c",
    "8c",
    "16c",
    NULL
};