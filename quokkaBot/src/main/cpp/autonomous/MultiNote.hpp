#pragma once

#include "../subsystems/subsystems.hpp"

namespace autonomous
{
    class MultiNote
    {
    private:
        double st;  // start time
    public:
        MultiNote(/* args */);
        void run();
    };
} // namespace autonomous
