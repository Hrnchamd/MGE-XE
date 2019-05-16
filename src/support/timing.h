#pragma once

class HighResolutionTimer {
public:
    static void init();
    static int getMicroseconds();
    static int getMilliseconds();
};
