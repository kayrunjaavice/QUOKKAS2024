#include "Basic.hpp"

namespace autonomous
{    
    Basic::Basic() {
    }
    
    void Basic::run() {
        subsystems::Drive::getInstance().timed_gyro_drive(0.25, 0.0, 30.0);
    }
    
} // namespace autonomous
