#include "util.hpp"
#include <frc/Timer.h>

bool util::wait(double &step_start, double duration)
{
    return frc::GetTime().value() < step_start + duration;
}
