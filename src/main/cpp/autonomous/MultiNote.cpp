#include "MultiNote.hpp"
#include <frc/smartdashboard/SmartDashboard.h>
#include "../util/util.hpp"

namespace autonomous
{
    double st;  // start time
    
    MultiNote::MultiNote() {
        st = frc::GetTime().value();
        frc::SmartDashboard::PutNumber("start time", st);
    }
    
    void MultiNote::run() {
        frc::SmartDashboard::PutNumber("time", frc::GetTime().value());
        if (util::wait(st, 1)) {
            subsystems::Drive::getInstance().gyro_drive(0.0, 90.0);
        } else {
            // Finally,
            subsystems::Drive::getInstance().move(0.0, 0.0);  // Stop
        }
    }
    
} // namespace autonomous
