#include "OneNote.hpp"

namespace autonomous
{    
    OneNote::OneNote() {
    }
    
    void OneNote::run() {        
        subsystems::Drive::getInstance().gyro_drive(0.25, 0.0);
    }
    
} // namespace autonomous
