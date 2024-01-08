#include "MultiNote.hpp"

namespace autonomous
{
    double start_time;
    
    MultiNote::MultiNote() {
        start_time = frc::GetTime().value();
    }
    
    void MultiNote::run() {
        if (frc::GetTime().value() < start_time + 10.0) {
            subsystems::Drive::getInstance().timed_gyro_drive(0.0, 90.0, 10.0);
        }

        subsystems::Drive::getInstance().move(0.0, 0.0);  // Stop
    }
    
} // namespace autonomous
