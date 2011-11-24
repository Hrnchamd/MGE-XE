
class QPF
{
    static LARGE_INTEGER t0, t1;
    static double freq;

public:
    static void init()
    {
        QueryPerformanceFrequency(&t0);
        freq = t0.QuadPart;
        QueryPerformanceCounter(&t0);
    }

    static double deltat()
    {
        if(freq == 0) init();
        QueryPerformanceCounter(&t1);
        double dt = (t1.QuadPart - t0.QuadPart) / freq;
        t1 = t0;
        return dt;
    }
};

LARGE_INTEGER QPF::t0, QPF::t1;
double QPF::freq;
