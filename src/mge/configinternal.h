#pragma once
#ifdef _CONF
#ifndef _CONFIGINTERNAL_H_
#define _CONFIGINTERNAL_H_


#ifndef NAN
static const unsigned __int64 nan = 0x7fffffffffffffff;
#define NAN (*(const double*)nan)
#endif

#ifndef countof
template <typename T, size_t N>
char (&_ArraySizeHelper(T (&array)[N]))[N];
#define countof(array) (sizeof(_ArraySizeHelper(array)))
#endif

#define False "0"
#define True "1"

#define DICTONLY_BIT    0
#define DICTONLY        MASK(DICTONLY_BIT)
#define MINMAX_BIT      1
#define MINMAX          MASK(MINMAX_BIT)
#define MODULO_BIT      2
#define MODULO          MASK(MODULO_BIT)

enum vtype { t_bit, t_bool, t_uint8, t_int8, t_uint16, t_int16, t_uint32, t_int32, t_float, t_double, t_string, t_set };

struct tdictent {
    const char* key;
    double value;
};

struct tdictionary {
    unsigned int length;
    const tdictent* dictent;
};

struct iniSetting {
    void* variable;
    vtype type;
    int bit_size;
    const char* section;
    const char* key;
    const char* defval;
    const tdictionary* dictionary;
    DWORD flags;
    double min;
    double max;
};

#endif /* _CONFIGINTERNAL_H_ */
#endif /* _CONF */
