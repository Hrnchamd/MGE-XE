
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "strsec.h"

// Secure string functions are Microsoft-specific library functions
// These are not intended to be secure, but to allow compilation with other targets

int strcpy_s(char *dest, size_t n, const char *src) { strcpy(dest, src); return 0; }

int strcat_s(char *dest, size_t n, const char *src) { strcat(dest, src); return 0; }

int sprintf_s(char *dest, size_t n, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vsnprintf(dest, n, format, args);
    va_end(args);
    return 0;
}

int _strlwr_s(char *dest, size_t sz) { _strlwr(dest); return 0; }

int _ultoa_s(unsigned long value, char *str, size_t sz, int radix) { _ultoa(value, str, radix); return 0; }

int _gcvt_s(char *str, size_t sz, double value, int digits) { _gcvt(value, digits, str); return 0; }

int _itoa_s(int value, char *str, size_t sz, int radix) { _itoa(value, str, radix); return 0; }
