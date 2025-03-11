#ifndef ERROR_H_
#define ERROR_H_

// int errx(int status, const char* fmt, ...);
// int warnx(const char* fmt, ...);

#define warnx(fmt, ...) \
    fprintf(stderr, fmt, ##__VA_ARGS__);

#define errx(status, fmt, ...) \
    warnx(fmt, ##__VA_ARGS__); \
    return status;

#endif /* ERROR_H_ */