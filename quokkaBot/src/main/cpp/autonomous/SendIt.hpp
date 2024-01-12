#pragma once

#include "../subsystems/subsystems.hpp"

namespace autonomous
{
    class SendIt
    {
    private:
        double st;  // start time
    public:
        SendIt(/* args */);
        void run();
    };
} // namespace autonomous
