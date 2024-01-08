#include "OneNote.hpp"

namespace autonomous
{    
    OneNote::OneNote() {
    }
    
    void OneNote::run() {        
        subsystems::Drive::getInstance().timed_gyro_drive(0.25, 0.0, 3.0);
    }
    
} // namespace autonomous
