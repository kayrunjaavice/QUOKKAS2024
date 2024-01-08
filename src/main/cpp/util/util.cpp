#include "util.hpp"
#include <frc/Timer.h>

bool util::wait(double start_time, double duration)
{
    return start_time + duration > frc::GetTime().value();
}
