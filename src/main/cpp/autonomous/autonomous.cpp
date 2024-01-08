#include "autonomous.hpp"

namespace autonomous
{
    void wait(double seconds)
    {
        double start_time = frc::GetTime().value();
        double end_time = start_time + seconds;

        while (frc::GetTime().value() < end_time) {}
    }
} // namespace autonomous
