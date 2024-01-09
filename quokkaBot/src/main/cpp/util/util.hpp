#pragma once

class util
{
    public:
        /* Note that step_start is passed by reference and incremented by `duration` seconds. */
        static bool wait(double &step_start, double duration);
};
