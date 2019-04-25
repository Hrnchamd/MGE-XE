
#include "timing.h"
#include "winheader.h"

static LARGE_INTEGER frequency;

void HighResolutionTimer::init()
{
    QueryPerformanceFrequency(&frequency);
}

int HighResolutionTimer::getMicroseconds()
{
    LARGE_INTEGER t;
    QueryPerformanceCounter(&t);

    return int(t.QuadPart * 1000000 / frequency.QuadPart);
}

int HighResolutionTimer::getMilliseconds()
{
    LARGE_INTEGER t;
    QueryPerformanceCounter(&t);

    return int(t.QuadPart * 1000 / frequency.QuadPart);
}
