#ifndef __libced_util_log_h__
#define __libced_util_log_h__

#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

/** Logs a line of text */
void _ced_log(FILE *file, const char *fmt, ...);

#define ced_logf(f, ...) _ced_log(f   , __VA_ARGS__)
#define ced_log(...)     _ced_log(NULL, __VA_ARGS__)

#endif /* __libced_util_log_h__ */