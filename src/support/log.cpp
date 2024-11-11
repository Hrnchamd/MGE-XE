
#include "winheader.h"
#include "log.h"

#include <cstdarg>
#include <cctype>
#include <cstring>
#include <cstdio>


namespace LOG {

    static HANDLE handle = INVALID_HANDLE_VALUE;


    bool open(const char* filename) {
        close();
        handle = CreateFile(filename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

        if (handle == INVALID_HANDLE_VALUE) {
            char errormsg[512] = "\0";
            FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), 0, errormsg, sizeof(errormsg), NULL);
            std::printf("LOG: cannot open log file %s: %s\n", filename, errormsg);
            fflush(stdout);
        }

        return handle != INVALID_HANDLE_VALUE;
    }

    std::size_t write(const char* str) {
        std::size_t sz = 0;
        DWORD written;

        if (handle != INVALID_HANDLE_VALUE) {
            if (str) {
                sz = std::strlen(str);
                BOOL result = WriteFile(handle, str, (DWORD)sz, &written, NULL);

                if (!result) {
                    char errormsg[512] = "\0";
                    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 0, GetLastError(), 0, errormsg, sizeof(errormsg), 0);
                    std::printf("LOG: write error: %s\n", errormsg);
                }
            }
        }

        return sz;
    }

    std::size_t log(const char* fmt, ...) {
        char buf[4096] = "\0";
        std::size_t result = 0;

        va_list args;
        va_start(args, fmt);

        if (fmt) {
            result = std::vsnprintf(buf, sizeof(buf), fmt, args);
        } else {
            result = 4;
            std::strcpy(buf, "LOG::log(null)\r\n");
        }

        LOG::write(buf);

        va_end(args);
        return result;
    }

    std::size_t logline(const char* fmt, ...) {
        char buf[4096] = "\0";
        std::size_t result = 0;

        va_list args;
        va_start(args, fmt);

        if (fmt) {
            result = std::vsnprintf(buf, sizeof(buf) - 4, fmt, args);
            std::strcat(buf + result, "\r\n");
        } else {
            result = 4;
            std::strcpy(buf, "LOG::log(null)\r\n");
        }

        write(buf);

        va_end(args);
        return result;
    }

    std::size_t winerror(const char* fmt, ...) {
        char buf[4096] = "\0";
        std::size_t result = 0;
        auto errorCode = GetLastError();

        va_list args;
        va_start(args, fmt);

        if (fmt) {
            result = std::vsnprintf(buf, sizeof(buf) - 4, fmt, args);
        } else {
            result = 4;
            std::strcpy(buf, "LOG::winerror(null)");
        }

        std::strcat(buf + std::strlen(buf), ": ");
        auto bufUsed = std::strlen(buf);
        FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 0, errorCode, 0, buf + bufUsed, static_cast<DWORD>(sizeof(buf) - (bufUsed + 2)), 0);
        std::strcat(buf + std::strlen(buf), "\r\n");

        write(buf);

        va_end(args);
        return result;
    }

    std::size_t logbinary(void* addr, std::size_t sz) {
        char buf[128];
        BYTE* ptr = (BYTE*)addr;

        for (std::size_t y = 0; y < sz; y += 16, ptr += 16) {
            std::size_t n = (sz - y < 16) ? (sz - y) : 16;
            char* s = buf;

            s += std::sprintf(s, "  ");
            for (std::size_t x = 0; x < n; ++x) {
                s += std::sprintf(s, "%02X ", (unsigned int)ptr[n]);
            }

            s += std::sprintf(s, "    ");
            for (std::size_t x = 0; x < n; ++x) {
                if (std::isprint(ptr[n])) {
                    *s++ = (char)ptr[n];
                } else {
                    *s++ = '.';
                }
            }

            s += std::sprintf(s, "\r\n");
            write(buf);
        }

        return sz;
    }

    void flush() {
        FlushFileBuffers(handle);
    }

    void close() {
        if (handle != INVALID_HANDLE_VALUE) {
            CloseHandle(handle);
        }

        handle = INVALID_HANDLE_VALUE;
    }

}
