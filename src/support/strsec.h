#include <stdlib.h>

int strcpy_s(char *dest, size_t n, const char *src);
int strcat_s(char *dest, size_t n, const char *src);
int sprintf_s(char *dest, size_t n, const char *format, ...);
int _strlwr_s(char *dest, size_t sz);

int _ultoa_s(unsigned long value, char *str, size_t sz, int radix);
int _gcvt_s(char *str, size_t sz, double value, int digits);
int _itoa_s(int value, char *str, size_t sz, int radix);
