#include "Basic.hpp"

namespace autonomous
{    
    Basic::Basic() {
    }
    
    void Basic::run() {
        subsystems::Drive::getInstance().gyro_drive(0.25, 0.0);
    }
    
} // namespace autonomous
