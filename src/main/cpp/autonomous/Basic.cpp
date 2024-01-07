#include "Basic.hpp"

namespace autonomous
{
    Basic::Basic() {
    }
    
    void Basic::run() {
        subsystems::Drive chassis;
        chassis.routine_timed_gyro_drive(0.25, 0.0, 3.0);
    }
    
} // namespace autonomous
