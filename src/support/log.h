#pragma once

#include <cstddef>



typedef void* HANDLE;

struct LOG {
    static bool open(const char* filename);
    static std::size_t write(const char* str);
    static std::size_t log(const char* fmt, ...);
    static std::size_t logline(const char* fmt, ...);
    static std::size_t logbinary(void* addr, std::size_t sz);
    static void close();

private:
    static HANDLE handle;
};
