#include "MultiNote.hpp"
#include <frc/smartdashboard/SmartDashboard.h>

namespace autonomous
{
    double start_time;
    
    MultiNote::MultiNote() {
        start_time = frc::GetTime().value();
        frc::SmartDashboard::PutNumber("start time", start_time);
    }
    
    void MultiNote::run() {
        frc::SmartDashboard::PutNumber("time", frc::GetTime().value());
        if (frc::GetTime().value() < (start_time + 1.0)) {
            subsystems::Drive::getInstance().gyro_drive(0.0, 90.0);
        } else {
            // Finally,
            subsystems::Drive::getInstance().move(0.0, 0.0);  // Stop
        }
    }
    
} // namespace autonomous
