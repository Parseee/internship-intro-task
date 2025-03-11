#ifndef ERROR_H_
#define ERROR_H_

void err(int status, const char* fmt, ...);
void warnx(const char* fmt, ...);

#endif /* ERROR_H_ */