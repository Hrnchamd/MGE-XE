
#include "stdint.h"
#include "timing.h"
#include "winheader.h"



// Calculations use doubles, as int64 ops bring in an excessive amount of library code on a 32-bit target

static double reciprocalFreq;

void HighResolutionTimer::init() {
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    reciprocalFreq = 1.0 / frequency.QuadPart;
}

int HighResolutionTimer::getMicroseconds() {
    LARGE_INTEGER t;
    QueryPerformanceCounter(&t);

    double x = 1000000 * (double(t.QuadPart) * reciprocalFreq);
    return int(int64_t(x));
}

int HighResolutionTimer::getMilliseconds() {
    LARGE_INTEGER t;
    QueryPerformanceCounter(&t);

    double x = 1000 * (double(t.QuadPart) * reciprocalFreq);
    return int(int64_t(x));
}
