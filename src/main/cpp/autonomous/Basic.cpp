#include "Basic.hpp"

namespace autonomous
{
    static bool run() {
        subsystems::Drive::routine_timed_gyro_drive(0.25, 0.0, 3.0);
    }
    
} // namespace autonomous
