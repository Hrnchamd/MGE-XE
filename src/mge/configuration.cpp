#define _CONF

#pragma setlocale("C")

#include <stdlib.h>
#include <algorithm>
#include "support/winheader.h"

#include "configuration.h"
#include "inidata.h"


ConfigurationStruct Configuration;

double getSettingValue(char* sval, const iniSetting& set) {
    const tdictionary* dict = set.dictionary;

    if (dict) {
        for (unsigned int i = 0; i < dict->length; ++i) {
            tdictent dictent = dict->dictent[i];
            if (!_stricmp(sval, dictent.key)) {
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
    }
    if (!(set.flags & DICTONLY)) {
        char* endptr;
        double temp = strtod(sval, &endptr);
        if (sval + strlen(sval) != endptr) {
            return atof(set.defval);
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
    } else if (dict) {
        for (unsigned int i = 0; i < dict->length; ++i) {
            tdictent dictent = dict->dictent[i];
            if (!_stricmp(set.defval, dictent.key)) {
                return dictent.value;
            }
        }
    }
    return NAN;
}

const char* dictValueToString(double value, const iniSetting& set) {
    const tdictionary* dict = set.dictionary;

    for (unsigned int i = 0; i < dict->length; ++i) {
        tdictent dictent = dict->dictent[i];
        if (value == dictent.value) {
            return dictent.key;
        }
    }

    return nullptr;
}

void utf8cpyToA_s(char* _Dst, size_t _SizeInBytes, const char* _Src) {
    size_t size = MultiByteToWideChar(CP_UTF8, 0, _Src, -1, NULL, 0);
    WCHAR* buffer = new WCHAR[size];
    MultiByteToWideChar(CP_UTF8, 0, _Src, -1, buffer, static_cast<int>(size));
    WideCharToMultiByte(CP_ACP, 0, buffer, -1, _Dst, static_cast<int>(_SizeInBytes), NULL, NULL);
    delete [] buffer;
}

bool ConfigurationStruct::LoadSettings() {
    char buffer[4096];

    MGEFlags = 0;
    GetPrivateProfileSectionNames(buffer, countof(buffer), mgeini);

    char* pointer = buffer;
    bool initialized = false;
    while (*pointer != '\0') {
        if (_stricmp(pointer, siniRendState)) {
            initialized = true;
            break;
        }
        pointer += strlen(pointer) + 1;
    }
    if (!initialized) {
        return false;
    }

    for (int i = 0; i != countof(iniSettings); ++i) {
        const iniSetting& set = iniSettings[i];
        GetPrivateProfileString(set.section, set.key, set.defval, buffer, countof(buffer), mgeini);

        if (set.type == t_string) {
            utf8cpyToA_s((char*)set.variable, set.bit_size, buffer);
        } else if (set.type == t_set) {
            size_t sz = std::min(set.bit_size, countof(buffer));
            GetPrivateProfileSection(set.section, buffer, static_cast<int>(sz), mgeini);
            memcpy(set.variable, buffer, sz);
        } else {
            double value = getSettingValue(buffer, set);
            switch (set.type) {
            case t_bit:
                if (value == 1) {
                    *(int*)set.variable |= (1 << set.bit_size);
                } else {
                    *(int*)set.variable &= ~(1 << set.bit_size);
                }
                break;
            case t_bool:
                *(bool*)set.variable = (value == 1);
                break;
            case t_uint8:
                *(unsigned __int8*)set.variable = (unsigned __int8)value;
                break;
            case t_int8:
                *(signed __int8*)set.variable = (signed __int8)value;
                break;
            case t_uint16:
                *(unsigned __int16*)set.variable = (unsigned __int16)value;
                break;
            case t_int16:
                *(signed __int16*)set.variable = (signed __int16)value;
                break;
            case t_uint32:
                *(unsigned __int32*)set.variable = (unsigned __int32)value;
                break;
            case t_int32:
                *(signed __int32*)set.variable = (signed __int32)value;
                break;
            case t_float:
                *(float*)set.variable = (float)value;
                break;
            case t_double:
                *(double*)set.variable = value;
                break;
            }
        }
    }
    return true;
}

bool ConfigurationStruct::SaveSettings() {
    char buffer[4096];

    for (int i = 0; i != countof(iniSettings); ++i) {
        const iniSetting& set = iniSettings[i];
        int strSize = 0;
        double value;

        if (set.flags & DONT_SAVE) {
            continue;
        }

        switch (set.type) {
        case t_bit:
            value = (((*(int*)set.variable) >> set.bit_size) & 1) ? 1 : 0;
            break;
        case t_bool:
            value = *(bool*)set.variable;
            break;
        case t_uint8:
            value = *(unsigned __int8*)set.variable;
            break;
        case t_int8:
            value = *(signed __int8*)set.variable;
            break;
        case t_uint16:
            value = *(unsigned __int16*)set.variable;
            break;
        case t_int16:
            value = *(signed __int16*)set.variable;
            break;
        case t_uint32:
            value = *(unsigned __int32*)set.variable;
            break;
        case t_int32:
            value = *(signed __int32*)set.variable;
            break;
        case t_float:
            value = *(float*)set.variable;
            break;
        case t_double:
            value = *(double*)set.variable;
            break;
        case t_set:
        case t_string:
            // Do not save these types
            break;
        }

        if (set.flags & DICTONLY) {
            // Use dictionary mapping for output
            const char* sval = dictValueToString(value, set);
            if (sval) {
                strSize = std::snprintf(buffer, sizeof(buffer), "%s", sval);
            }
        }
        else {
            switch (set.type) {
            case t_bit:
            case t_bool:
                // Should be covered by the DICTONLY branch
                break;
            case t_uint8:
            case t_int8:
            case t_uint16:
            case t_int16:
            case t_uint32:
            case t_int32:
                strSize = std::snprintf(buffer, sizeof(buffer), "%.0f", value);
                break;
            case t_float:
            case t_double:
                strSize = std::snprintf(buffer, sizeof(buffer), "%.2f", value);
                break;
            case t_set:
            case t_string:
                // Do not save these types
                break;
            }
        }

        // Only write if a valid output string was produced
        if (strSize > 0) {
            if (WritePrivateProfileString(set.section, set.key, buffer, mgeini) == 0) {
                return false;
            }
        }
    }
    return true;
}
