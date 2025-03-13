#ifndef ERROR_H_
#define ERROR_H_

// int errx(int status, const char* fmt, ...);
// int warnx(const char* fmt, ...);

#define warnx(fmt, ...) \
    fprintf(stderr, fmt, ##__VA_ARGS__);

#define errx(status, fmt, ...)     \
    do {                           \
        warnx(fmt, ##__VA_ARGS__); \
        exit(status);              \
    } while (0)

#endif /* ERROR_H_ */