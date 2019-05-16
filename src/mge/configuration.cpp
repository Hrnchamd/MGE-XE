#define _CONF

#pragma setlocale("C")

#include <stdlib.h>
#include <algorithm>
#include "support/winheader.h"

#include "configuration.h"
#include "inidata.h"

ConfigurationStruct Configuration;

double getSettingValue (char* sval, iniSetting set) {
    const tdictionary* dict = set.dictionary;
    if (dict) for (unsigned int i = 0; i < dict -> length; ++i) {
            tdictent dictent = dict -> dictent [i];
            if (!_stricmp (sval, dictent.key)) {
                if (set.flags & MINMAX) {
                    if (dictent.value > set.max) {
                        return set.max;
                    }
                    if (dictent.value < set.min) {
                        return set.min;
                    }
                }
                return dictent.value;
            }
        }
    if (!(set.flags & DICTONLY)) {
        char* endptr;
        double temp = strtod(sval, &endptr);
        if (sval + strlen (sval) != endptr) {
            return atof (set.defval);
        } else {
            if (set.flags & MINMAX) {
                if (temp > set.max) {
                    return set.max;
                }
                if (temp < set.min) {
                    return set.min;
                }
            }
            return temp;
        }
    } else if (dict) for (unsigned int i = 0; i < dict -> length; ++i) {
            tdictent dictent = dict -> dictent [i];
            if (!_stricmp (set.defval, dictent.key)) {
                return dictent.value;
            }
        }
    return NAN;
}

void utf8cpyToA_s (char* _Dst, size_t _SizeInBytes, const char* _Src) {
    size_t size = MultiByteToWideChar (CP_UTF8, 0, _Src, -1, NULL, 0);
    WCHAR* buffer = new WCHAR [size];
    MultiByteToWideChar (CP_UTF8, 0, _Src, -1, buffer, size);
    WideCharToMultiByte (CP_ACP, 0, buffer, -1, _Dst, _SizeInBytes, NULL, NULL);
    delete [] buffer;
}

bool ConfigurationStruct::LoadSettings () {
    char buffer [4096];
    char* pointer;

    MGEFlags = 0;
    GetPrivateProfileSectionNames (buffer, countof (buffer), mgeini);
    pointer = buffer;
    bool initialized = false;
    while (*pointer != '\0') {
        if (_stricmp (pointer, siniRendState)) {
            initialized = true;
            break;
        }
        pointer += strlen (pointer) + 1;
    }
    if (!initialized) {
        return false;
    }
    for (int i = 0; i != countof (iniSettings); ++i) {
        iniSetting set = iniSettings [i];
        GetPrivateProfileString (set.section, set.key, set.defval, buffer, countof (buffer), mgeini);

        if (set.type == t_string) {
            utf8cpyToA_s ((char*)set.variable, set.bit_size, (char*)(&buffer));
        } else if (set.type == t_set) {
            size_t sz = std::min(set.bit_size, countof(buffer));
            GetPrivateProfileSection(set.section, buffer, sz, mgeini);
            memcpy(set.variable, buffer, sz);
        } else {
            double temp = getSettingValue (buffer, set);
            switch (set.type) {
            case t_bit:
                if (temp == 1) {
                    *(int*)set.variable |= (1 << set.bit_size);
                } else {
                    *(int*)set.variable &= ~(1 << set.bit_size);
                }
                break;
            case t_bool:
                *(bool*)set.variable = (temp == 1);
                break;
            case t_uint8:
                *(unsigned __int8*)set.variable = (unsigned __int8)temp;
                break;
            case t_int8:
                *(signed __int8*)set.variable = (signed __int8)temp;
                break;
            case t_uint16:
                *(unsigned __int16*)set.variable = (unsigned __int16)temp;
                break;
            case t_int16:
                *(signed __int16*)set.variable = (signed __int16)temp;
                break;
            case t_uint32:
                *(unsigned __int32*)set.variable = (unsigned __int32)temp;
                break;
            case t_int32:
                *(signed __int32*)set.variable = (signed __int32)temp;
                break;
            case t_float:
                *(float*)set.variable = (float)temp;
                break;
            case t_double:
                *(double*)set.variable = temp;
                break;
            }
        }
    }
    return true;
}
